#ifndef _KMP_H_
#define _KMP_H_

//#define Cplusplus		//�����˴�������C++���룬����ʹ��C


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
** ԭ��:int KmpFind(const char *target, const char *pattern)
** ���ߣ�����
** ���ڣ�2017-4-2
** ������KMP�㷨�����ַ�������ƥ��
** ���룺target -> �յ���ָ���ַ���
**       pattern ->
** �������
** ����ֵ��	-1 -> �ַ�����ƥ��
**			>=0 -> ƥ���ϵ��׵�ַ
** ��ע���ú����Ǳ�׼�⺯���������޸�
*/
int KmpFind(const char *target, const char *pattern);
#endif
#endif