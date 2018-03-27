#-*- coding: utf-8 -*-
import time
import calendar
import requests
import json
from merge_string_list import merge_string_list

import pandas as pd
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

class Stock:
        daysec = 86400 
	
        def get_bong(self, interval, stockno):
            get_bong_url = 'https://query1.finance.yahoo.com/v8/finance/chart/'
            #'207940.KS
            #?symbol=207940.KS
            #&period1=1520614800
            #&period2=1520812800
            #&interval=5m
            #&includePrePost=true
            #&events=div%7Csplit%7Cearn
            #&lang=en-US
            #&region=US
            #&crumb=0Xfk4srpv2w
            #&corsDomain=finance.yahoo.com'
            get_bong_url += (stockno)
            get_bong_url += ('?symbol='+stockno)
            curr_time = calendar.timegm(time.gmtime())
            get_bong_url += ('&period1='+str(curr_time - self.daysec*7))
            get_bong_url += ('&period2='+str(curr_time))
            get_bong_url += ('&interval='+interval)
            get_bong_url += ('&includePrePost=true')
            get_bong_url += ('&events=div%7Csplit%7Cearn')
            get_bong_url += ('&lang=en-US')
            get_bong_url += ('&region=US')
            get_bong_url += ('&crumb=0Xfk4srpv2w')
            get_bong_url += ('&corsDomain=finance.yahoo.com')

            headers = {'Connection': 'keep-alive',}
            response = (requests.get(get_bong_url, headers=headers))
	    json_data = json.loads(response.content)
            
            #debug
            
            #for timestamp, data in \
            #zip((json_data['chart']['result'][0]['timestamp']), \
            #(json_data['chart']['result'][0]['indicators']['quote'][0]['close'])):
            #    print('timestamp:'+ str(timestamp) +',data:' + str(data))
            #    
            #print('timestamp size:'+str(len(json_data['chart']['result'][0]['timestamp'])))
            #print('open size:'+str(len(json_data['chart']['result'][0]['indicators']['quote'][0]['open'])))
            
            return (json_data['chart']['result'][0])

        def get_list(self, market_name='kosdaq'):
            market_dict = {"kosdaq":{"yahoo_code":".KS", "krx_code":"kosdaqMkt"}}
            krx_url = 'http://kind.krx.co.kr/corpgeneral/corpList.do?method=download'
            krx_url = krx_url+'&searchType=13&marketType='+market_dict[market_name]['krx_code']
            #print(krx_url) 
            df = pd.read_html(krx_url, header=0)[0]

            code_list = []
            for index, row in df.iterrows():
                code_list.append(str(row['종목코드']).zfill(6) + market_dict[market_name]['yahoo_code'])

            return code_list



print(Stock().get_list('kosdaq'))
#Stock().get_bong('5m', '207940.KS')


