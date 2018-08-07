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
import GetData

#准备工作：获取深圳的经纬度
def getlnglat(address):
    url = 'http://api.map.baidu.com/geocoder/v2/'
    output = 'json'
    ak = '1r0YqRkKaOrrwM6yRjDodYna1Y7G9Maw'
    add = quote(address) #由于本文城市变量为中文，为防止乱码，先用quote进行编码
    uri = url + '?' + 'address=' + add  + '&output=' + output + '&ak=' + ak
    req = urlopen(uri)
    res = req.read().decode() #将其他编码的字符串解码成unicode
    temp = json.loads(res) #对json数据进行解析
    return temp
#s = getlnglat('深圳')


def PlotThermodynamicChart(str_data):
    web_name = 'result.html'
    with open(web_name,'r', encoding='UTF-8') as fh:
        content = fh.read()
    pattern = '(?<=var points =)([^;]+)'
    s = re.sub(pattern,str_data,content)
    with open(web_name,'w',encoding='UTF-8') as fh:
        fh.write(s)
    webbrowser.open(web_name)

if __name__ == '__main__':    
    file_name = 'PathFinder06.txt'
    read_data = GetData.GetData(file_name)
    PlotThermodynamicChart(read_data)
    
#http://api.map.baidu.com/location/ip?ip=183.16.87.27&ak=fj2PqYGGB4MaYUGEWiUHmgW8YLQl4glj&coor=bd09ll    