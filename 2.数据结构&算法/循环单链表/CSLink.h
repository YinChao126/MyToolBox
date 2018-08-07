/************************************************************************/
/* 名称：循环单链表ADT
** 作者：尹超
** 日期：2016-12-5
** 描述：实现循环单链表的抽象数据类型，包括了创建、删除、添加节点等常用功能
** 备注：从http://www.cnblogs.com/cpoint/p/3479515.html修改而来，有许多高级
**       功能可以根据实际需要来添加
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
typedef struct TaskList *LinkList; /* 另一种定义LinkList的方法 */

struct ListData
{
	int FormCode;
	int LdpcRate;
	int IntvSize;
	int MapBits;
	int ToneNum;
};


Status CreateList(LinkList *L); //创建一个只有头结点的循环单链表
Status DestroyList(LinkList *L); //删除一个链表
Status ClearList(LinkList *L); //将链表重置为初始化状态
Status IsListEmpty(LinkList L); //判断链表是否只有一个元素（为空）
int GetListLength(LinkList L); //返回链表长度（有多少个节点）
Status InsertList(LinkList *L, struct ListData Data); //在L之后增加一个节点
void Display(LinkList L); //Debug，打印所有的FormCode，可以打印头结点，也可以不打印
#endif