import requests
import json
import time


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

#broad_cast(msg)

krw_btc_code = 'CRIX.UPBIT.KRW-BTC'
def upbit_check_gap_req(minute, market_code):
	headers = {'Host': 'crix-api-endpoint.upbit.com',
'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:57.0) Gecko/20100101 Firefox/57.0',
'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
'Accept-Language': 'ko-KR,ko;q=0.8,en-US;q=0.5,en;q=0.3',
'Accept-Encoding': 'gzip, deflate, br',
'Referer': 'https://steemkr.com/kr/@segyepark/api',
'Connection': 'keep-alive',
'Upgrade-Insecure-Requests': '1',
'Cache-Control': 'max-age=0'}
	upbit_minute_candle_url = 'https://crix-api-endpoint.upbit.com/v1/crix/candles/minutes/'
	candle_count = 2
	req_url = (upbit_minute_candle_url+str(minute)+'?code='+market_code+'&count='+str(candle_count))
	print(req_url)
	response = (requests.get(req_url, headers=headers))
	#print(response.text)
	#return (response.text)
	json_data = json.loads(response.content)
	current_data = json_data[0]	
	past_data = json_data[1]	
	print(current_data['lowPrice'])
	print(past_data['lowPrice'])
	#if (response.ok):
	#	return json_data['result']
	#else:
	#	return json_data['error_code']

#upbit_check_gap_req(10, krw_btc_code)

try:
	while 1:
		msg = upbit_check_gap_req(10, krw_btc_code)
		#msg = 'GAZUA'
		print(msg)
		#broad_cast(msg)
		time.sleep(10)
except:
	print('exit')
	exit()
