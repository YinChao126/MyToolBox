#include "FIFO.h"


#define FIFO_LEN 100
int main()
{
	int i;
	int buff[FIFO_LEN * 2];
	struct FIFO MyBuffer;
	int t[2] = { 0 };
	pFIFO pBuff = &MyBuffer;
	CreateFifo(pBuff, 1, FIFO_LEN);
	for (i = 0; i < FIFO_LEN; i++)
	{
		t[0] = i;
		t[1] = i;
		InQueue(pBuff, t);
	}
	i = GetBuffSize(pBuff);
	FastDiscardData(pBuff, 24);
	InQueue(pBuff, t);
	i = GetBuffSize(pBuff);
	ReadBlockFifo(pBuff, buff, GetBuffSize(pBuff));
	i = GetBuffSize(pBuff);
	DestoryFifo(pBuff);

	return 0;
}