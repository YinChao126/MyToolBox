/************************************************************************/
/* ���ƣ�ѭ��������ADT
** ���ߣ�����
** ���ڣ�2016-12-5
** ������ʵ��ѭ��������ĳ����������ͣ������˴�����ɾ������ӽڵ�ȳ��ù���
** ��ע����http://www.cnblogs.com/cpoint/p/3479515.html�޸Ķ����������߼�
**       ���ܿ��Ը���ʵ����Ҫ�����
/************************************************************************/
#ifndef __CSLINK_H
#define __CSLINK_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef int Status;
enum MyEnum
{
	OK,
	ERROR
};
enum MyEnum2
{
	TRUE,
	FALSE
};
struct TaskList
{
	int FormCode;
	int LdpcRate;
	int IntvSize;
	int MapBits;
	int ToneNum;
	struct TaskList *next;
};
typedef struct TaskList *LinkList; /* ��һ�ֶ���LinkList�ķ��� */

struct ListData
{
	int FormCode;
	int LdpcRate;
	int IntvSize;
	int MapBits;
	int ToneNum;
};


Status CreateList(LinkList *L); //����һ��ֻ��ͷ����ѭ��������
Status DestroyList(LinkList *L); //ɾ��һ������
Status ClearList(LinkList *L); //����������Ϊ��ʼ��״̬
Status IsListEmpty(LinkList L); //�ж������Ƿ�ֻ��һ��Ԫ�أ�Ϊ�գ�
int GetListLength(LinkList L); //���������ȣ��ж��ٸ��ڵ㣩
Status InsertList(LinkList *L, struct ListData Data); //��L֮������һ���ڵ�
void Display(LinkList L); //Debug����ӡ���е�FormCode�����Դ�ӡͷ��㣬Ҳ���Բ���ӡ
#endif