# -*- coding: utf-8 -*-
"""
Created on Tue May 22 21:29:51 2018

@author: Administrator
"""
# 串口号自动检测（失败）
#import serial.tools.list_ports
#
#plist = list(serial.tools.list_ports.comports())
#
#if len(plist) <= 0:
#    print("没有发现端口!")
#else:
#    plist_0 = list(plist[0])
#    serialName = plist_0[0]
#    serialFd = serial.Serial(serialName, 9600, timeout=60)
#    print("可用端口名>>>", serialFd.name)

#串口发送（成功）
#import time
#import serial  
#ser=serial.Serial("COM2",9600,timeout=0.5)  
#for i in range(0,1):  
#    ser.write('hello\r\n'.encode())  
#    time.sleep(0.1)
#print(ser.readline());  
#ser.close()      


#串口接收并回传
import time
import serial  
try:
    ser=serial.Serial("COM2",9600,timeout=None) #此处的timeout默认值0.5
    print('com2 opened!')
    rec_num = 0
    fo = open("data.txt", "w")
        
except:
    print('error, com2 has already opened!')
    ser.close()

while 1:
    a = ser.in_waiting
    if a > 0:
        content = ser.read_all()
        a = str(content, encoding = "utf-8") #bytes to string
        fo.write(a)
        rec_num = rec_num + len(content)
        print(rec_num)
    if rec_num > 100:
        fo.close()
        break
#        ser.write(content) #回写

if ser.is_open == True: #关闭逻辑
    ser.close()    