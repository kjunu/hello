#-*- coding: utf-8 -*-
import time
import calendar
import requests
import json
from merge_string_list import merge_string_list
from bs4 import BeautifulSoup
from lxml import html

import pandas as pd
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

class Stock:
        daysec = 86400 
        businesshours_min_count = 390 #6.5 * 60	
       
        #it's only working well for minite interval
        def get_bong_by_yahoo(self, interval, stockno, fromdate=0):
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

            if fromdate == 0:
                get_bong_url += ('&period1='+str(curr_time - self.daysec*7))
            else:
                get_bong_url += ('&period1='+str(fromdate))

            get_bong_url += ('&period2='+str(curr_time))
            get_bong_url += ('&interval='+interval)
            get_bong_url += ('&includePrePost=true')
            get_bong_url += ('&events=div%7Csplit%7Cearn')
            get_bong_url += ('&lang=en-US')
            get_bong_url += ('&region=US')
            get_bong_url += ('&crumb=0Xfk4srpv2w')
            get_bong_url += ('&corsDomain=finance.yahoo.com')

            headers = {'Connection': 'keep-alive',}
            #debug
            with open('logic_error','a') as the_file:
                the_file.write(get_bong_url+'\n')
                #print(get_bong_url)
            
            response = (requests.get(get_bong_url, headers=headers))
	    json_data = json.loads(response.content)
            
            #debug
            #for timestamp, data in \
            #zip((json_data['chart']['result'][0]['timestamp']), \
            #(json_data['chart']['result'][0]['indicators']['quote'][0]['close'])):
            #    print('timestamp:'+ str(timestamp) +',data:' + str(data))
            #    
            #print(stockno + ' timestamp size:'+str(len(json_data['chart']['result'][0]['timestamp'])))
            #print(stockno + ' open size:'+str(len(json_data['chart']['result'][0]['indicators']['quote'][0]['open'])))
            #print(json_data['chart']['result'][0])
            return (json_data['chart']['result'][0])
        
        def get_il_bong_by_naver(self, stockno):
            get_il_bong_url = 'http://finance.naver.com/item/sise_day.nhn?code='+stockno 
            headers = {'Connection': 'keep-alive',}
            response = (requests.get(get_il_bong_url, headers=headers))
            soup = BeautifulSoup(response.text, "html.parser")
            #close_price = soup.select('body > table.type2 > tbody > tr:nth-child(4) > td:nth-child(2)')
            #close_price = soup.select('body > table.type2 > tr:nth-child(4) > td > span')
            #open_price = soup.select('body > table.type2 > tbody > tr > td:nth-child(4) > span')
            #high_price = soup.select('body > table.type2 > tbody > tr > td:nth-child(5) > span')
            #low_price = soup.select('body > table.type2 > tbody > tr > td:nth-child(6) > span')
            #volume_price = soup.select('body > table.type2 > tbody > tr > td:nth-child(7) > span')
            
            tree = html.fromstring(response.text)
            
            result = {"date":[], "close":[], "open":[], "high":[], "low":[], "volume":[]}

            for date in tree.xpath('/html/body/table[1]/tr/td[1]/span'):
                result['date'].append(date.text.replace(',','').strip())
                #print(html.tostring(date, method='html', with_tail=False))

            for cp in tree.xpath('/html/body/table[1]/tr/td[2]/span'):
                result['close'].append(cp.text.replace(',','').strip())
                #print(html.tostring(cp, method='html', with_tail=False))
            
            for op in tree.xpath('/html/body/table[1]/tr/td[4]/span'):
                result['open'].append(op.text.replace(',','').strip())
                #print(html.tostring(op, method='html', with_tail=False))
            
            for hp in tree.xpath('/html/body/table[1]/tr/td[5]/span'):
                result['high'].append(hp.text.replace(',','').strip())
                #print(html.tostring(hp, method='html', with_tail=False))
           
            for lp in tree.xpath('/html/body/table[1]/tr/td[6]/span'):
                result['low'].append(hp.text.replace(',','').strip())
                #print(html.tostring(lp, method='html', with_tail=False))

            for volume in tree.xpath('/html/body/table[1]/tr/td[7]/span'):
                result['volume'].append(volume.text.replace(',','').strip())
                #print(html.tostring(volume, method='html', with_tail=False))
            #debug
            #print(result)

            return result 
            

        market_dict = {"kosdaq":{"yahoo":".KQ", "krx":"kosdaqMkt", "naver":""}}
        def get_list(self, market_name='kosdaq', source_site='naver'):
            krx_url = 'http://kind.krx.co.kr/corpgeneral/corpList.do?method=download'
            krx_url = krx_url+'&searchType=13&marketType='+self.market_dict[market_name]['krx']
            #debug
            #print(krx_url) 
            df = pd.read_html(krx_url, header=0)[0]

            code_list = []
            for index, row in df.iterrows():
                code_list.append(str(row['종목코드']).zfill(6) + self.market_dict[market_name][source_site])
            
            #debug
            #print(len(code_list))
            
            return code_list
        def convert_code(self, code, market_name, source_site, target_site):
            return code.replace(self.market_dict[market_name][source_site],'') + \
                    self.market_dict[market_name][target_site]


#start_time = time.time()
#for code in Stock().get_list('kosdaq', 'yahoo'):
#    with open('stock_data_' + code,'a') as the_file:
#        json.dump(Stock().get_bong_by_yahoo('1m', code), the_file)
#        the_file.write('\n')

#for code in Stock().get_list('kosdaq', 'naver'):
#    Stock().get_il_bong_by_naver(code)
#print(stock.get_il_bong_by_naver('041190'))
#elapsed_time = time.time() - start_time
#print(elapsed_time)


