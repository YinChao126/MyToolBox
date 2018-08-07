# -*- coding: utf-8 -*-
"""
Created on Wed Jul  4 14:20:17 2018

@author: yinchao
"""
#import random

#1.查找文件名
'''
格式解析
0 'CDRadio'
1 时间：HHMMSS
2 snr值
3 'SNR'
4 LDPC_PASS
5 LDPC_FAIL
6 STATE (1,2,3)
7 '$GNGGA'
8 UTC时间(时分秒)
9 latitude维度(要除以100)
10 'N'北半球
11 longitude经度(要除以100)
12 'E'东经
13 GPS状态（0-6）
14 卫星数量（个）
15 HDOP水平精度因子（0.5~99.9）
16 高程
17 'M'高程单位
18 大地水准面和WGS椭球之间的关系
19 'M'椭球单位
20 差分延迟
21 差分站ID号*校验值
'''
file_name = 'PathFinder06.txt'

def GetData(file_name):
    data = []
    with open(file_name, 'r') as fh:
        content = fh.readlines()
        for s in content:  
            if s != '\n':
                data.append(s.split(','))
    
    data_str = []
    read_data = "["
    for s in data:
        lng = float(s[11]) / 100
        lat = float(s[9]) / 100
        snr = float(s[2])
        a = {"lng":lng,"lat":lat,"count":snr}
        data_str.append(a)
        read_data = read_data + str(a) + ','
    read_data = read_data[:-1] + ']'    #必须转换成str才能用替换功能
    return read_data

if __name__ == '__main__':
    s = GetData(file_name)