import threading
import requests
import json
import time
import csv
import bol
import pandas as pd
import datetime
 
def tele_req(url):
	telegram = 'https://api.telegram.org/'
	token = 'bot491123571:AAGweUA3uohsv5hQg28MylOn_3s2DYYd6Ec'
	request_url = telegram+token
	
	response = (requests.get(request_url+url))
	#print(response.text)
	json_data = json.loads(response.content)
	if (response.ok):
		return json_data['result']
	else:
		return json_data['error_code']

def broad_cast(msg):
	chat_id_list = []
	get_updates ='/getUpdates'
	updates_data = tele_req(get_updates)
	for d in updates_data:
		#print(d['message']['from']['id'])
		chat_id = d['message']['from']['id']
		if chat_id not in chat_id_list:
			print('send msg to : '+ str(chat_id))
			chat_id_list.append(chat_id)
			sendmsg_url = '/sendMessage?chat_id='+str(chat_id)+'&text="'+msg+'"'
			tele_req(sendmsg_url)

#get_me_url = request_url+'/getMe'
#get_url = '/getMe'
#tele_req(get_url)

upbit_minute_candle_url = 'https://crix-api-endpoint.upbit.com/v1/crix/candles/minutes/'
#broad_cast(msg)

def upbit_req(method, url, body=''):
	headers = {'Host': 'crix-api-endpoint.upbit.com',
'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:57.0) Gecko/20100101 Firefox/57.0',
'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
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

gemini_url = 'https://exchange.gemini.com/sell/ethbtc?_='
def gemini_req(method, url, body=''):
	headers = {'Host': 'exchange.gemini.com',
'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:57.0) Gecko/20100101 Firefox/57.0',
'Accept': 'application/json, text/javascript, */*; q=0.01',
'Accept-Language': 'ko-KR,ko;q=0.8,en-US;q=0.5,en;q=0.3',
'Accept-Encoding': 'gzip, deflate, br',
'Referer': 'https://exchange.gemini.com/sell/ethbtc?_=15166675344501516668803',
'Refresh-Only': 'refresh',
'X-Requested-With': 'XMLHttpRequest',
'Cookie': 'GEMINI_SESSION=acac795305467918106a39999c98ccd66f63659c-csrfToken=6964771729a70d1f43f12b7681df1a158d25ccc9-1516668825387-739b2b0d69305e80e09ea53f&authproof=WmaWSysQZ%2F%2B76JXHPG0Vo%2BZ1Cuyxl5sxfSfZvkp3cpgLQt%2BCzj6G1VLjAQ5wh%2FDkvswKgGy667yyEfd67B1kkfNPeSwVNYAxuS7dsROfB%2Fk11fptIttuiYny5%2F3NQXklBeKpcBaWSVykPn2Kj3ujOTLuv03p%2BQgaPQaM5Wjmmyuh2Sb7gpzgo%2B0VmrD7xwX82Tjl3xiGjGt0f8PqDxnNY%2ByW9RyjoUdT%2F1bJdu348BRc9AE88HmJ%2FnhpNr2ZOiJK6FY2TiL%2F0fexNdpl5FG8VjwV5g2kosxZVG1u%2BTHnWqFepNNK%2FM3TPt3YzNFvwRQlXiXWosVbvVpuJZ6vwz6l96KQSEqoTxJla72WmdtjiePrz5J0XNTdfDb7TgdkvqkmVbkGgDb28HyXhGPrOaILijjzu%2BnRbgxf65J6tU75%2FSBxDLg%2FCWWXzp8EsNyYmE2%2Bx6c8RFea4Ph%2Byq%2B%2FFecelWUhei00KLnpTXEr8HFKL6h40o7YweQmTTWr1DDmuxZns2IhTH5ArixJfwQ%3D; _ga=GA1.2.1001604067.1516668827; _gid=GA1.2.244101228.1516668827; RememberDevice=proof=WmaHyK3V8%2BZcCpMcSUgMRmHD4%2FE%2Bd6m8PtAEoLN0T%2BGI3cPso592s84MvlqGNhjKBEylBF07AdQdhSE4KV3fJw4izNKsGE19xip2rVG4XktHZrCP3ijBm9sPi18HlQs%2BIdWzG7%2BPEY9aqxtOJtgjlodP6vmwAlN9014FBxvs4db%2B5QCDhwsc%2FexysSRj36D8xw1jP85eE3aLbD2RjCIDIoDPLRj7%2Fw99UCi2%2FthSyfugRSgZWlmo2Il3AnFjS2nWHp9%2FuIYw3BNZnbOLgnIjTy9jOq8tJzH2GLRUh2xFO16Ih8qFXJ0Bj9ygOOtq0BNzOvOV3i8i%2FZR2kv%2Bstw%3D%3D; RememberAuthy=proof=WmaH2drGQwSRRwDRr8ShcpvOIKPfs%2B19agz4KzjWiO4m8Lq5XWtrYJ4lmgR8U4vVYwmZRUGEf%2FftaY1GwdZl5VCpF5ktMD1gO4zOABmko9TOLPGlSzTez7tZoXGZropi%2BfHsv5RvFU3O8Y%2Fs5Sred2SxFKMBi2%2FHIYlvoOFl4DK7tYGerikMajLQNekH%2FzBuM4vbwJLmQ7xhZ1C2b2%2B9hySaIVPi13nZ10DLNCH1Bnu01IW%2Fet3DOah41X3k9kE8N3iBBI84xmVYp2nkTceYKq5PrPfMu7UY8wauGYeTubitAenwykaTWp7Q5nGuBv902npKw95NZfRIJKT%2Bqw9qifDUVBDEHF1%2BQzw3; _gat=1',
'Connection': 'keep-alive'}
	print(url)
	if method == 'get':
		response = (requests.get(url, headers=headers))
	else :
		print('not support yet : ' +  method)
	return response 

def upbit_check_bol_req(minute, market_code):
	candle_count = 20
	req_url = (upbit_minute_candle_url+str(minute)+'?code='+market_code+'&count='+str(candle_count))
	#print(req_url)
	response = upbit_req('get', req_url)
	json_data = json.loads(response.content)
	
	f = open('./upbit_check_bol_req.csv', 'w')
	writer = csv.writer(f)

	writer.writerow(['Date','Close'])
	for d in json_data:
		#writer.writerow([datetime.datetime.fromtimestamp(d['timestamp']).strftime(), d['tradePrice']]);	
		writer.writerow([d['timestamp'], d['tradePrice']]);	

	f.close()
	
	upper_band, lower_band = bol.Bollinger().bollinger(get_stock_data())
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

def get_stock_data():
	prices = pd.read_csv('./upbit_check_bol_req.csv')
	df = (prices[::-1])
	df = df.dropna()
	return df

def check_upbit_gemini_gap(code):
	code_dict = {
	'btc_eth':
		{
		'upbit':'CRIX.UPBIT.BTC-ETH',
		'gemini':'ethbtc'
		}
	}
				
	req_url = (upbit_minute_candle_url+'10?code='+code_dict[code]['upbit'])
	response = upbit_req('get', req_url)
	#print(response.text)
	json_data = json.loads(response.content)
	upbit_current_price = json_data[0]['tradePrice']
	#print('upbit:'+str(upbit_current_price))
	
	req_url = (gemini_url+str(int(time.time())))
	response = gemini_req('get', req_url)
	#print(response.text)
	json_data = json.loads(response.content)
	gemini_current_price = float(json_data['pageProps']['marketData']['stats']['lastPrice'])
	#print('gemini:'+str(gemini_current_price))
	if (upbit_current_price*1.01 < gemini_current_price or 
		 upbit_current_price > gemini_current_price*1.01):
		return (code+' gap : upbit('+str(upbit_current_price)+'),gemini('+str(gemini_current_price)+')')
	return 'boring'

krw_btc_code = 'CRIX.UPBIT.KRW-BTC'
krw_eth_code = 'CRIX.UPBIT.KRW-ETH'
krw_xrp_code = 'CRIX.UPBIT.KRW-XRP'
krw_neo_code = 'CRIX.UPBIT.KRW-NEO'
krw_ada_code = 'CRIX.UPBIT.KRW-ADA'
krw_snt_code = 'CRIX.UPBIT.KRW-SNT'
krw_xlm_code = 'CRIX.UPBIT.KRW-XLM'
krw_qtum_code = 'CRIX.UPBIT.KRW-QTUM'
krw_pivx_code = 'CRIX.UPBIT.KRW-PIVX'
btc_neo_code = 'CRIX.UPBIT.BTC-NEO'
btc_eth_code = 'CRIX.UPBIT.BTC-ETH'
btc_etc_code = 'CRIX.UPBIT.BTC-ETC'
btc_ltc_code = 'CRIX.UPBIT.BTC-LTC'
btc_bcc_code = 'CRIX.UPBIT.BTC-BCC'
btc_mtl_code = 'CRIX.UPBIT.BTC-MTL'
btc_omg_code = 'CRIX.UPBIT.BTC-OMG'
btc_qtum_code = 'CRIX.UPBIT.BTC-QTUM'
btc_xrp_code = 'CRIX.UPBIT.BTC-XRP'
btc_snt_code = 'CRIX.UPBIT.BTC-SNT'
btc_storj_code = 'CRIX.UPBIT.BTC-STORJ'
btc_tix_code = 'CRIX.UPBIT.BTC-TIX'
btc_powr_code = 'CRIX.UPBIT.BTC-POWR'

code_list = [
krw_btc_code ,
krw_eth_code ,
btc_neo_code ,
btc_eth_code ,
btc_etc_code ,
btc_ltc_code ,
btc_bcc_code ,
btc_mtl_code ,
btc_omg_code ,
btc_qtum_code ,
btc_xrp_code ,
btc_snt_code ,
btc_storj_code ,
btc_tix_code ,
btc_powr_code 
]

bol_code_list = [(30,krw_btc_code), 
(30,krw_xrp_code), 
(30,krw_eth_code), 
(30,krw_neo_code), 
(30,krw_ada_code), 
(30,krw_snt_code), 
(30,krw_xlm_code), 
(30,krw_qtum_code), 
(30,krw_pivx_code), 
#(15,btc_neo_code), 
#(15,btc_eth_code),
#(15,btc_ltc_code) ,
#(15,btc_bcc_code) ,
#(15,btc_mtl_code) ,
#(15,btc_omg_code) ,
#(15,btc_qtum_code) ,
#(15,btc_xrp_code) ,
#(15,btc_snt_code) ,
#(15,btc_storj_code),
#(15,btc_tix_code) ,
#(15,btc_powr_code) 
]

gap_code_list = [
btc_neo_code ,
btc_eth_code ,
btc_etc_code ,
btc_ltc_code ,
btc_bcc_code ,
btc_mtl_code ,
btc_omg_code ,
btc_qtum_code ,
btc_xrp_code ,
btc_snt_code ,
btc_storj_code ,
btc_tix_code ,
btc_powr_code ]



def bol_check():
	for minute, market_code in bol_code_list:
		msg = upbit_check_bol_req(minute, market_code)
		print('bollinger:'+msg)
		if msg != 'boring':
			broad_cast(msg)

def gap_check():
	#for market_code in gap_code_list:
		msg = check_upbit_gemini_gap('btc_eth')
		print('gap:'+msg)
		if msg != 'boring':
			broad_cast(msg)

print(upbit_check_bol_req(10, krw_btc_code))
#print(gap_check())
broad_cast('tracking started with : ' + str(bol_code_list))
try:
	sleep_time = 60
	while 1:
		t1 = threading.Thread(target=bol_check)
		t1.start()
		#t2 = threading.Thread(target=gap_check)
		#t2.start()
		time.sleep(sleep_time)
except Exception as e:
	print(e)
	print('exit')
	exit()

