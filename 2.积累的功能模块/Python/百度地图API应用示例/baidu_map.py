# -*- coding: utf-8 -*-
"""
Created on Tue Jun  5 08:26:15 2018

@author: yinchao
"""

import json
import sys
from urllib.request import urlopen, quote
import requests,csv
import pandas as pd #导入这些库后边都要用到
import random
import re
import webbrowser

#准备工作：获取深圳的经纬度
def getlnglat(address):
    url = 'http://api.map.baidu.com/geocoder/v2/'
    output = 'json'
    ak = 'AK密钥' #此处的密钥请自行输入
    add = quote(address) #由于本文城市变量为中文，为防止乱码，先用quote进行编码
    uri = url + '?' + 'address=' + add  + '&output=' + output + '&ak=' + ak
    req = urlopen(uri)
    res = req.read().decode() #将其他编码的字符串解码成unicode
    temp = json.loads(res) #对json数据进行解析
    return temp
s = getlnglat('深圳')





# 1. 获取数据（暂时通过random来获得）,提取出经纬度/SNR。之后通过读文件的方式获取read_data
# 输出：str格式的read_data数据
lng_base = 114.0259736573215
lat_base = 22.546053546205247
delta = 0.1
snr_base = 10
delta_snr = 15

data = []
read_data = "["
for s in range(100):
    lng = random.uniform(lng_base-delta,lng_base+delta)
    lat = random.uniform(lat_base-delta,lat_base+delta)
    snr = random.uniform(snr_base-delta_snr,snr_base+delta_snr)
    a = {"lng":lng,"lat":lat,"count":snr}
    data.append(a)
    read_data = read_data + str(a) + ','
read_data = read_data[:-1] + ']'    #必须转换成str才能用替换功能

#with open('data.txt','r') as fh:
#    a = fh.read()
#    read_data = a[:-1]
    
# 2. 替换test.html中的数据,通过正则表达式自动替换points的值
# 输出：result.html
    
#with open('test.html','r', encoding='UTF-8') as fh:
#    content = fh.read()
#
#pattern = '(?<=var points =)([^;]+)'
#obj = re.compile(pattern)
#match = obj.findall(content)
#s = re.sub(pattern,read_data,content)
##print(s)
#with open('result.html','w',encoding='UTF-8') as fh:
#    fh.write(s)
#    
##try:
##    print(match[0])    
##except:
##    pass
## 3.渲染地图，打开热力图进行显示
##webbrowser.open("file:///C:/YinChao/WorkSpace/Python/badu_map/test.html")
#webbrowser.open("file:///C:/YinChao/WorkSpace/Python/badu_map/result.html")

def PlotThermodynamicChart(str_data):
    with open('result.html','r', encoding='UTF-8') as fh:
        content = fh.read()
    pattern = '(?<=var points =)([^;]+)'
    s = re.sub(pattern,read_data,content)
    with open('result.html','w',encoding='UTF-8') as fh:
        fh.write(s)
    webbrowser.open("file:///C:/YinChao/WorkSpace/Python/badu_map/result.html")#此处的文件路径要重新设置

if __name__ == '__main__':
     PlotThermodynamicChart(read_data)   
