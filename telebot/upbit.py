import requests
import csv
import json
import bol
import pandas as pd
import numpy as np
from bs4 import BeautifulSoup
from merge_string_list import merge_string_list
class Upbit:
	upbit_minute_candle_url = 'https://crix-api-endpoint.upbit.com/v1/crix/candles/minutes/'
	upbit_all_status = []
	upbit_notice_title= []
	
	def upbit_req(self, method, url, body=''):
		headers = {'Host': 'crix-api-endpoint.upbit.com',
	'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:57.0) Gecko/20100101 Firefox/57.0',
	#'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
	'Accept': '*/*',
	'Accept-Language': 'ko-KR,ko;q=0.8,en-US;q=0.5,en;q=0.3',
	'Accept-Encoding': 'gzip, deflate, br',
	'Referer': 'https://steemkr.com/kr/@segyepark/api',
	'Connection': 'keep-alive',
	'Upgrade-Insecure-Requests': '1',
	'Cache-Control': 'max-age=0'}
		if method == 'get':
			response = (requests.get(url, headers=headers))
		else :
			print('not support yet : ' +  method)
		return response 

	def check_notice_req(self):
		upbit_notice_url = 'https://api-manager.upbit.com/api/v1/notices?page=1&per_page=10'
		response = self.upbit_req('get', upbit_notice_url)
		json_data = json.loads(response.content)
		msg_list = []
		for d in json_data['data']['list']:
			title = d['title']
			if title not in self.upbit_notice_title:
				self.upbit_notice_title.append(title)
				msg_list.append(title + ", " + 'https://upbit.com/service_center/notice?id='+ str(d['id']))
		#print(merge_string_list(self.upbit_notice_title))
		if not msg_list:
			return 'boring'
		else :
			return merge_string_list(msg_list)

	def all_status_check(self, init=False):
		upbit_all_status_url = 'https://ccx.upbit.com/api/v1/market_status/all'
		response = self.upbit_req('get', upbit_all_status_url)
		json_data = json.loads(response.content)
		msg_list = []
		for d in json_data:
			if d['id'] not in self.upbit_all_status:
		        	self.upbit_all_status.append(d['id'])
		        	msg = 'new coin market '+ d['id'] +' detected in upbit'
		        	if not init:
					msg_list.append(msg)
		
		if not msg_list:
			return 'boring'
		else :
			return merge_string_list(msg_list)
	
	def check_bol_req(self, minute, market_code):
		candle_count = 20
		req_url = (self.upbit_minute_candle_url+str(minute)+'?code='+market_code+'&count='+str(candle_count))
		#print(req_url)
		response = self.upbit_req('get', req_url)
		try:
			json_data = json.loads(response.content)
		except Exception as e:
			print("check_bol_req raise exception!")
			print(response.text)
			print(e)
			
		f = open('./upbit_check_bol_req.csv', 'w')
		writer = csv.writer(f)
	
		writer.writerow(['Date','Close'])
		for d in json_data:
			#writer.writerow([datetime.datetime.fromtimestamp(d['timestamp']).strftime(), d['tradePrice']]);	
			writer.writerow([d['timestamp'], d['tradePrice']]);	
	
		f.close()
		
		upper_band, lower_band = bol.Bollinger().bollinger(self.get_stock_data())
		high = (upper_band.dropna())
		low = (lower_band.dropna())
		#print(high[0])
		current_price = json_data[0]['tradePrice']
		#print(low[0])
		if high[0] < current_price :
			return str(market_code) +' price ('+str(current_price)+') overvalued'
		elif low[0] > current_price :
			return str(market_code) +' price ('+str(current_price)+') undervalued'
		else :
			return 'boring'
	
	def check_vol_req(self, minute, market_code):
		candle_count = 52
		req_url = (self.upbit_minute_candle_url+str(minute)+'?code='+market_code+'&count='+str(candle_count))
		#print(req_url)
		response = self.upbit_req('get', req_url)
		json_data = json.loads(response.content)
	
		current_volume = json_data[1]['candleAccTradeVolume']
		current_volume_price = json_data[1]['candleAccTradePrice']
		current_price = json_data[0]['tradePrice']
		i = 0
		volume_list = []
		for d in json_data:
			if i != 0 :
				volume_list.append(d['candleAccTradeVolume'])
			i += 1
		
		volume_mean = np.mean(volume_list)
		#print( "vol_mean:" + str(volume_mean) + ", cur_vol:" + str(current_volume))
		if volume_mean * 3 < current_volume	and current_volume_price > 300000000:
			return str(market_code) +' price ('+str(current_price)+') volume boosted. check what happend'
		else :	
			return 'boring'
	
	def get_stock_data(self):
		prices = pd.read_csv('./upbit_check_bol_req.csv')
		df = (prices[::-1])
		df = df.dropna()
		return df
