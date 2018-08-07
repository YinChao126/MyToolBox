# -*- coding: utf-8 -*-
"""
Created on Sat May 12 12:53:29 2018

@author: YinChao
"""

import re

def dos2linux(file):
    '''
    description: input a windows type file, convert to a linux type file
    tips:replace '\r\n' to '\n' at the end of each line
    @input: filename
    @output:create a file named 'filename_linux' in the current directory    
    '''
    pattern = '[^.]+'
    reobj = re.compile(pattern)
    match = reobj.findall(file)
    result = list()
    with open(file,'rb') as fh:
        content = fh.readlines()
    
    for s in content:
        if s[-2:] == bytes('\r\n', encoding = 'gbk'): #prevent linux type file input
            y = s[:-2] + bytes('\n', encoding = 'gbk')
        else:
            return
        result.append(y)
    file_out = match[0] + '_linux.' + match[1]
    with open(file_out, 'wb') as fh:
        fh.writelines(result)
        
        
def linux2dos(file):
    '''
    description: input a linux type file, convert to a dos type file
    tips:replace '\n' to '\r\n' at the end of each line
    @input: filename
    @output:create a file named 'filename_dos' in the current directory    
    '''
    pattern = '[^.]+'
    reobj = re.compile(pattern)
    match = reobj.findall(file)
    result = list()
    with open(file,'rb') as fh:
        content = fh.readlines()
    
    for s in content:
        if s[-1:] == bytes('\n', encoding = 'gbk'): #prevent dos type file input
            y = s[:-1] + bytes('\r\n', encoding = 'gbk')
        else:
            return
        result.append(y)
    file_out = match[0] + '_dos.' + match[1]
    with open(file_out, 'wb') as fh:
        fh.writelines(result)
        
if __name__ == '__main__':
    dos2linux('example_dos.txt') 
    linux2dos('example_dos_linux.txt')
    #please compare the 'example_dos.txt' and 'example_dos_linux_dos.txt'       