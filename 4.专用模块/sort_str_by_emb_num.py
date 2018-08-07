# -*- coding: utf-8 -*-
"""
Created on Mon Jun  4 17:34:56 2018

@author: YinChao
"""

import re

re_digits = re.compile(r'(\d+)')
def emb_numbers(s):
    pieces = re_digits.split(s)
    pieces[1::2] = map(int, pieces[1::2])
    return pieces
    
def sort_str_by_emb_num(str_list):
    '''
    实现一个根据字符串中的数字来排序的函数，用于给大量数据集排序
    输入：文件名list
    输出：对该list进行重新排序（以文件名中的数字为参考）
    '''
    aux = [(emb_numbers(s),s) for s in str_list]
    aux.sort()
    return [s for __, s in aux]

###############################################################################
if __name__ == '__main__':
    ex_list = ['10.txt','11,txt','2.txt','89.txt']
    print(ex_list)    
    after_sort = sort_str_by_emb_num(ex_list)
    print(after_sort)