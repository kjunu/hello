# -*- coding: utf-8 -*-
import threading
import requests
import json
import time
import csv
import bol
import pandas as pd
import datetime
import numpy as np
from merge_string_list import merge_string_list
import urllib
 
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
			#sendmsg_url = '/sendMessage?chat_id='+str(chat_id)+'&text="'+urllib.quote_plus(msg)+'"'
			sendmsg_url = '/sendMessage?chat_id='+str(chat_id)+'&text="'+(msg)+'"'
			tele_req(sendmsg_url)

def msg_to_channel(msg):
	sendmsg_url = '/sendMessage?chat_id=@goxkf&text="'+(msg)+'"'
	tele_req(sendmsg_url)

def edaily_req(method, url, body=''):
	headers = {'Host': 'www.edaily.co.kr',
'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:57.0) Gecko/20100101 Firefox/57.0',
'Accept': 'application/json, text/javascript, */*; q=0.01',
'Accept-Language': 'ko-KR,ko;q=0.8,en-US;q=0.5,en;q=0.3',
'Accept-Encoding': 'gzip, deflate, br',
'Referer': 'http://www.edaily.co.kr/stock/E01_05.html',
'Refresh-Only': 'refresh',
'X-Requested-With': 'XMLHttpRequest',
'Cookie': '_ga=GA1.3.97484524.1517381291; OAX=e40CQlpxZqgAAqIO; interworks_ctorta=; ttx_bnrs_e=; ttx_t_r={"1109157171":{"criteo":"1"},"1855483143":{"criteo":"1"}}; dable_uid=56765654.1470191643092; __gads=ID=e4426cd69e3f1152:T=1517381290:S=ALNI_MYqn1qAfbXK5pjzbtqTIsHHAb7J4w; trc_cookie_storage=taboola%2520global%253Auser-id%3De32b2af8-b04c-40bf-93be-7d352ac601d6; ASPSESSIONIDQQRDRSBC=CHGOFMFCDOGLENCPOBLFLKCB; _gid=GA1.3.1791363322.1518136509; ASPSESSIONIDSQSCRQCC=PFEGGMFCHMIDIABNJBKHOPBD; ASPSESSIONIDSQQDSTCC=GCMLFMFCLLHFLGKLPEPFFFOJ',
'Connection': 'keep-alive'}
	#print(url)
	if method == 'get':
		response = (requests.get(url, headers=headers))
	else :
		print('not support yet : ' +  method)
	return response 

news_id_list = []
def edaily_check_news():
	edaily_url = 'http://http://www.edaily.co.kr/stock/E01_05.html'
	edaily_req_url = 'http://www.edaily.co.kr/inc/common/ajaxcrossdomain_json.asp?Url=http%3A%2F%2F10.101.33.201%3A9000%2FNewsMgnt%2Fnewslist%3FPageSize%3D20%26categoryNo%3D16105%26regDT%3D%26Page%3D1&Index=0&divId=N50_10&classid=component_template_id_N50_10_HgOIh9fXFBVLim1&_=1518136747268'
	
	response = edaily_req('get', edaily_req_url)
 
	msg_list = []
	json_data = json.loads(response.content.decode('euc-kr'))
	journal_url = 'http://www.edaily.co.kr/news/news_detail.asp?newsId='	
	for d in json_data:
		print(d['Journalist'])
		print(d['NEWS_ID'])
		#print(test_list)
		#if d['Journalist'] == u'박형수' and d['NEWS_ID'] not in news_id_list:
		if d['NEWS_ID'] not in news_id_list:
			#print(test_list)
			news_id_list.append(d['NEWS_ID'])
			#msg_list.append(d['HEADLINE'] + "/" + d['Journalist'] + "/" + d['ConfirmDate'])
			msg_list.append(d['ConfirmDate']+", "+d['Journalist']+", "+ journal_url + d['NEWS_ID'])
	
	print(merge_string_list(news_id_list))
	if not msg_list:
		print('boring')
	else :
		print(merge_string_list(msg_list))
		broad_cast(merge_string_list(msg_list))


try:
	sleep_time = 60
	#msg_to_channel('msg to channel test')
	print('msg to channel test')
	#broad_cast("start news tracking...")
	#while 1:
	#	t1 = threading.Thread(target=edaily_check_news)
	#	t1.start()
	#	time.sleep(sleep_time)
except Exception as e:
	print(e)
	print('exit')
	exit()
#edaily_check_news()

