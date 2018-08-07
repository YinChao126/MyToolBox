#ifndef _KMP_H_
#define _KMP_H_

//#define Cplusplus		//开启此处，启用C++代码，否则使用C


#ifdef Cplusplus
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int KmpFind(const string& target, const string& pattern);
#else
#include <string.h>
#include <stdlib.h>
/*
** 原型:int KmpFind(const char *target, const char *pattern)
** 作者：尹超
** 日期：2017-4-2
** 描述：KMP算法——字符串快速匹配
** 输入：target -> 收到的指令字符串
**       pattern ->
** 输出：无
** 返回值：	-1 -> 字符串不匹配
**			>=0 -> 匹配上的首地址
** 备注：该函数是标准库函数，请勿修改
*/
int KmpFind(const char *target, const char *pattern);
#endif
#endif