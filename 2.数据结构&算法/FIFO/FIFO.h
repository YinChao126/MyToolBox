#ifndef __FIFO_H
#define __FIFO_H


/************************************************************************/
/* 用户控制区                                                           */
/************************************************************************/

#define MESSAGE
#define ASSERT
typedef int FIFO_TYPE; //数据类型，请根据需求修改此处

/************************************************************************/
/* 以下请勿作任何修改                                                   */
/************************************************************************/
struct FIFO
{
	FIFO_TYPE *BaseDataAddr;
	int front;
	int rear;
	int MaxSize;
	int Type; //0->普通模式		1->复数模式（一次操作两个数）
};
typedef struct FIFO* pFIFO;
/************************************************************************/
/* Function Declaration
*/
/************************************************************************/
char CreateFifo(pFIFO pBuff, const int Type, const int BuffSize);

void DestoryFifo(pFIFO pBuff);

char InQueue(pFIFO pBuff, const FIFO_TYPE *DataIn);

char OutQueue(pFIFO pBuff, FIFO_TYPE *DataOut);

char IsQueueEmpty(const pFIFO pBuff); //是否为空？

char IsQueueFull(const pFIFO pBuff); //是否已满？

int GetBuffSpace(const pFIFO pBuff); //还可以存多少

int GetBuffSize(const pFIFO pBuff); //已经存了多少

char WriteBlockFifo(pFIFO pBuff, const FIFO_TYPE *SrcData, int DataInLen);

char ReadBlockFifo(pFIFO pBuff, FIFO_TYPE *DstBuff, int DataOutLen);

//强行写入，满了就覆盖原来的值
void ForceWriteBlockFifo(pFIFO pBuff, const FIFO_TYPE *SrcData, int DataInLen);

#define DEFALT_VALUE 0xFF //此处可修改
//tips:此函数可用来复位一个FIFO
//强行读出，为空就用DEFALT_VALUE来填充
void ForceReadBlockFifo(pFIFO pBuff, FIFO_TYPE *DstBuff, int DataOutLen);

void FastDiscardData(pFIFO pBuff, int DiscardLen); //快速丢弃数据，直接操作front即可。
#endif
