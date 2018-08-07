#include "FIFO.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static enum BOOL
{
	FALSE,
	TRUE
};
static enum STATUS
{
	ERROR = -1,
	OK
};

char CreateFifo(pFIFO pBuff, const int Type, const int BuffSize)
{
	if (Type == 1) //复数模式
	{
		pBuff->Type = 1;
		pBuff->MaxSize = (BuffSize << 1);
		pBuff->BaseDataAddr = (FIFO_TYPE *)malloc(sizeof(FIFO_TYPE)*(pBuff->MaxSize + 2));
		if (pBuff->BaseDataAddr == NULL)
		{
#ifdef ASSERT
			assert(NULL);
#endif

#ifdef MESSAGE
			printf("fail to create FIFO!\n");
#endif
			return ERROR;
		}
	}
	else if (Type == 0) //普通模式
	{
		pBuff->Type = 0;
		pBuff->MaxSize = BuffSize;
		pBuff->BaseDataAddr = (FIFO_TYPE *)malloc(sizeof(FIFO_TYPE)*(pBuff->MaxSize + 1));
		if (pBuff->BaseDataAddr == NULL)
		{
#ifdef ASSERT
			assert(NULL);
#endif

#ifdef MESSAGE
			printf("fail to create FIFO!\n");
#endif
			return ERROR;
		}
	}
	else //忘记设置模式
	{
#ifdef ASSERT
		assert(NULL);
#endif

#ifdef MESSAGE
		printf("forget to set Type!\n");
#endif
		return ERROR; //
	}
	pBuff->front = 0;
	pBuff->rear = 0;
	return OK;
}

void DestoryFifo(pFIFO pBuff)
{
	if (pBuff->BaseDataAddr != NULL)
	{
		free(pBuff->BaseDataAddr);
		pBuff->BaseDataAddr = NULL;
	}
}

char IsQueueEmpty(const pFIFO pBuff)
{
	if (pBuff->front == pBuff->rear)
	{
#ifdef MESSAGE
		printf("fifo is empty!\n");
#endif
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

char IsQueueFull(const pFIFO pBuff)
{
	if (pBuff->Type)
	{
		if (pBuff->front == (pBuff->rear + 2) % (2 + pBuff->MaxSize))
		{
#ifdef MESSAGE
			printf("fifo is full!\n");
			return TRUE;
#endif
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if (pBuff->front == (pBuff->rear + 1) % (1 + pBuff->MaxSize))
		{
#ifdef MESSAGE
			printf("fifo is full!\n");
			return TRUE;
#endif
		}
		else
		{
			return FALSE;
		}
	}
}

char InQueue(pFIFO pBuff, const FIFO_TYPE *DataIn)
{
	if (pBuff->Type)
	{
		if (IsQueueFull(pBuff))
		{
			return ERROR;
		}
		else
		{
			pBuff->BaseDataAddr[pBuff->rear] = DataIn[0];
			pBuff->BaseDataAddr[pBuff->rear + 1] = DataIn[1];
			pBuff->rear = (pBuff->rear + 2) % (2 + pBuff->MaxSize);
			return OK;
		}
	}
	else
	{
		if (IsQueueFull(pBuff))
		{
			return ERROR;
		}
		else
		{
			pBuff->BaseDataAddr[pBuff->rear] = DataIn[0];
			pBuff->rear = (pBuff->rear + 1) % (1 + pBuff->MaxSize);
			return OK;
		}
	}
}

char OutQueue(pFIFO pBuff, FIFO_TYPE *DataOut)
{
	if (pBuff->Type)
	{
		if (IsQueueEmpty(pBuff))
		{
			return ERROR;
		}
		else
		{
			*(DataOut) = pBuff->BaseDataAddr[pBuff->front];
			*(DataOut + 1) = pBuff->BaseDataAddr[pBuff->front];
			pBuff->front = (pBuff->front + 2) % (2 + pBuff->MaxSize);
			return OK;
		}
	}
	else
	{
		if (IsQueueEmpty(pBuff))
		{
			return ERROR;
		}
		else
		{
			*(DataOut) = pBuff->BaseDataAddr[pBuff->front];
			pBuff->front = (pBuff->front + 1) % (1 + pBuff->MaxSize);
			return OK;
		}
	}
}

int GetBuffSize(const pFIFO pBuff)
{
	if (pBuff->rear >= pBuff->front)
	{
		if (pBuff->Type)
		{
			return (pBuff->rear - pBuff->front) >> 1;
		}
		else
		{
			return (pBuff->rear - pBuff->front);
		}

	}
	else
	{
		if (pBuff->Type)
		{
			return (pBuff->rear - pBuff->front + (pBuff->MaxSize + 2)) >> 1; //个数除以2
		}
		else
		{
			return (pBuff->rear - pBuff->front + (pBuff->MaxSize + 1));
		}
	}
}

int GetBuffSpace(const pFIFO pBuff)
{
	if (pBuff->Type)
	{
		return ((pBuff->MaxSize >> 1)- GetBuffSize(pBuff));
	}
	else
	{
		return (pBuff->MaxSize - GetBuffSize(pBuff));
	}

}

char WriteBlockFifo(pFIFO pBuff, const FIFO_TYPE *SrcData, int DataInLen)
{
	int i;

	if (GetBuffSpace(pBuff) < DataInLen)
	{
#ifdef MESSAGE
		printf("not enough space to write.\n");
		return ERROR;
#endif
	}
	else
	{
		if (pBuff->Type)
		{
			DataInLen <<= 1;
			for (i = 0; i < DataInLen; i += 2)
			{
				InQueue(pBuff, &(SrcData[i]));
			}
		}
		else
		{
			for (i = 0; i < DataInLen; i++)
			{
				InQueue(pBuff, &(SrcData[i]));
			}
		}
	}
	return OK;
}

char ReadBlockFifo(pFIFO pBuff, FIFO_TYPE *DstBuff, int DataOutLen)
{
	int i;

	if (GetBuffSize(pBuff) < DataOutLen)
	{
#ifdef MESSAGE
		printf("not enough data to read.\n");
#endif
		return ERROR;
	}
	else
	{
		if (pBuff->Type)
		{
			DataOutLen <<= 1;
			for (i = 0; i < DataOutLen; i += 2)
			{
				OutQueue(pBuff, &(DstBuff[i]));
			}
		}
		else
		{
			for (i = 0; i < DataOutLen; i++)
			{
				OutQueue(pBuff, &(DstBuff[i]));
			}
		}
	}
	return OK;
}

void ForceWriteBlockFifo(pFIFO pBuff, const FIFO_TYPE *SrcData, int DataInLen)
{
	int i, j;
	int MoreDataLen;
	int CurDataLen = GetBuffSpace(pBuff);
	
	MoreDataLen = DataInLen - CurDataLen;
	if (pBuff->Type)
	{
		DataInLen <<= 1;
		MoreDataLen <<= 1;
	}

	if (MoreDataLen <= 0) //可以安全写入
	{
		if (pBuff->Type)
		{
			for (i = 0; i < DataInLen; i += 2)
			{
				InQueue(pBuff, &(SrcData[i]));
			}
		}
		else
		{
			for (i = 0; i < DataInLen; i++)
			{
				InQueue(pBuff, &(SrcData[i]));
			}
		}
	}
	else //覆盖写入
	{
		if (pBuff->Type)
		{
			for (i = 0; i < CurDataLen; i += 2)
			{
				InQueue(pBuff, &(SrcData[i]));
			}
			for (j = 0; j < MoreDataLen; j += 2)
			{
				pBuff->BaseDataAddr[pBuff->rear] = SrcData[i + j];
				pBuff->BaseDataAddr[pBuff->rear+1] = SrcData[i + j + 1];
				pBuff->rear = (pBuff->rear + 2) % (pBuff->MaxSize + 2);
				pBuff->front = (pBuff->front + 2) % (pBuff->MaxSize + 2);
				//队列会一直处于满的状态
			}
		}
		else
		{
			for (i = 0; i < CurDataLen; i++)
			{
				InQueue(pBuff, &(SrcData[i]));
			}
			for (j = 0; j < MoreDataLen; j++)
			{
				pBuff->BaseDataAddr[pBuff->rear] = SrcData[i + j];
				pBuff->rear = (pBuff->rear + 1) % (pBuff->MaxSize + 1);
				pBuff->front = (pBuff->front + 1) % (pBuff->MaxSize + 1);
				//队列会一直处于满的状态
			}
		}
	}
}

void ForceReadBlockFifo(pFIFO pBuff, FIFO_TYPE *DstBuff, int DataOutLen)
{
	int i, j;
	int MoreDataLen;
	int CurDataLen = GetBuffSpace(pBuff);
	
	MoreDataLen = DataOutLen - CurDataLen;
	if (pBuff->Type)
	{
		DataOutLen <<= 1;
		MoreDataLen <<= 1;
	}

	if (pBuff->Type)
	{
		if (MoreDataLen <= 0) //可以安全读出
		{
			for (i = 0; i < DataOutLen; i += 2)
			{
				OutQueue(pBuff, &(DstBuff[i]));
			}
		}
		else
		{
			for (i = 0; i < CurDataLen; i += 2)
			{
				OutQueue(pBuff, &(DstBuff[i]));
			}
			for (j = 0; j < MoreDataLen; j += 2)
			{
				DstBuff[i + j] = DEFALT_VALUE;
				DstBuff[i + j + 1] = DEFALT_VALUE;
				pBuff->rear = (pBuff->rear + 2) % (2 + pBuff->MaxSize);
				pBuff->front = (pBuff->front + 2) % (2 + pBuff->MaxSize);
				//队列一直处于空的状态
			}
		}
	}
	else
	{
		if (MoreDataLen <= 0) //可以安全读出
		{
			for (i = 0; i < DataOutLen; i++)
			{
				OutQueue(pBuff, &(DstBuff[i]));
			}
		}
		else
		{
			for (i = 0; i < CurDataLen; i++)
			{
				OutQueue(pBuff, &(DstBuff[i]));
			}
			for (j = 0; j < MoreDataLen; j++)
			{
				DstBuff[i + j] = DEFALT_VALUE;
				DstBuff[i + j + 1] = DEFALT_VALUE;
				pBuff->rear = (pBuff->rear + 1) % (1 + pBuff->MaxSize);
				pBuff->front = (pBuff->front + 1) % (1 + pBuff->MaxSize);
				//队列一直处于空的状态
			}
		}
	}
}

void FastDiscardData(pFIFO pBuff, int DiscardLen)
{
	int CurDataLen = GetBuffSize(pBuff);
	if (DiscardLen < 0) //如果输入数据小于0，直接返回
	{
		return;
	}


	if (DiscardLen > CurDataLen) //如果想要丢弃的数大于实际FIFO中已存的数，直接设置为空
	{
		pBuff->front = pBuff->rear;
#ifdef MESSAGE
		printf("warnings, DiscardLen is more than FIFO's size\n");
#endif
	}
	else
	{
		if (pBuff->Type)
		{
			DiscardLen <<= 1;
			pBuff->front = (pBuff->front + DiscardLen) % (2 + pBuff->MaxSize);
		}
		else
		{
			pBuff->front = (pBuff->front + DiscardLen) % (1 + pBuff->MaxSize);
		}
	}
}