# -*- coding: utf-8 -*-
"""
Created on Fri May 11 10:44:19 2018

@author: PD
"""
import os  
import struct
  
#for root, dirs, files in os.walk('./'):  
#    print(root) #当前目录路径  
#    print(dirs) #当前路径下所有子目录  
#    print(files) #当前路径下所有非目录子文件  
#with open('zzz.txt','rb') as fh:
#    data = fh.read()

def hex2num(file):
    '''
    作者：尹超
    日期：2018-5-11
    解析十六进制文件，用于固件串口传输数据解码
    输入：文件名
    输出：解析后当前文件夹下生成result.txt
    返回值：解析的数据长度
    
    输入数据格式说明：
    输入：53 FF 1A 00 字符串形式的十六进制文件
    数据输出为： -173 26
    格式说明： 前两字节代表第一个数（16进制），低位在前，实际值为FF53（-173）
              后两字节代表第二个数，实际值为001A(26)  
    '''
    with open(file,'rb') as fh:
        data = fh.read()
    r = data.decode('gbk') #转成str
    import re
    pattern = '\w\w'
    reobj = re.compile(pattern)
    result = reobj.findall(r)    
    print(len(result))
    d = []
    for i in range(0, len(result), 4):
        d.append(result[i:i+4])
    f=open('hex_dec_out.txt', "w")
    for i in d[:-4]:
        re = i[1] + i[0]
        im = i[3] + i[2]
        re = int(re,16) #16进制str转整数
        if re > 32767:
            re -= 65536
        im = int(im,16)
        if im > 32767:
            im -= 65536
        s = str(re) + ' ' + str(im)
        f.write(s + '\n')
    f.close()    
    return len(d)

def bin2num(file):
    '''
    作者：尹超
    日期：2018-5-11
    解析二进制文件，用于固件串口传输数据解码
    输入：文件名
    输出：解析后当前文件夹下生成result.txt
    返回值：解析的数据长度
    
    输入数据格式说明：
    输入：53 FF 1A 00 字符串形式的十六进制文件
    数据输出为： -173 26
    格式说明： 前两字节代表第一个数（16进制），低位在前，实际值为FF53（-173）
              后两字节代表第二个数，实际值为001A(26)  
    '''
    file_object=open(file,'rb')  
    aa=file_object.read()  
    bt_array=struct.unpack(len(aa)*'B',aa)  
    file_object.close()   
    
    d = []
    for i in range(0, len(bt_array), 4):
        d.append(bt_array[i:i+4])
    
    f=open('bin_dec_out.txt', "w")
    for i in d[:-4]:
        re = i[1]*256 + i[0]
        im = i[3]*256 + i[2]
        if re > 32767:
            re -= 65536
        if im > 32767:
            im -= 65536
        s = str(re) + ' ' + str(im)
        f.write(s + '\n')
    f.close()     
    return len(d)


if __name__ == '__main__':
    l_bin = bin2num('RxIn.bin')
#    l_hex = hex2num('zzz_hex.txt')