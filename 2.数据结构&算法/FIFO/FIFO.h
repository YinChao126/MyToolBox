#ifndef __FIFO_H
#define __FIFO_H


/************************************************************************/
/* �û�������                                                           */
/************************************************************************/

#define MESSAGE
#define ASSERT
typedef int FIFO_TYPE; //�������ͣ�����������޸Ĵ˴�

/************************************************************************/
/* �����������κ��޸�                                                   */
/************************************************************************/
struct FIFO
{
	FIFO_TYPE *BaseDataAddr;
	int front;
	int rear;
	int MaxSize;
	int Type; //0->��ͨģʽ		1->����ģʽ��һ�β�����������
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

char IsQueueEmpty(const pFIFO pBuff); //�Ƿ�Ϊ�գ�

char IsQueueFull(const pFIFO pBuff); //�Ƿ�������

int GetBuffSpace(const pFIFO pBuff); //�����Դ����

int GetBuffSize(const pFIFO pBuff); //�Ѿ����˶���

char WriteBlockFifo(pFIFO pBuff, const FIFO_TYPE *SrcData, int DataInLen);

char ReadBlockFifo(pFIFO pBuff, FIFO_TYPE *DstBuff, int DataOutLen);

//ǿ��д�룬���˾͸���ԭ����ֵ
void ForceWriteBlockFifo(pFIFO pBuff, const FIFO_TYPE *SrcData, int DataInLen);

#define DEFALT_VALUE 0xFF //�˴����޸�
//tips:�˺�����������λһ��FIFO
//ǿ�ж�����Ϊ�վ���DEFALT_VALUE�����
void ForceReadBlockFifo(pFIFO pBuff, FIFO_TYPE *DstBuff, int DataOutLen);

void FastDiscardData(pFIFO pBuff, int DiscardLen); //���ٶ������ݣ�ֱ�Ӳ���front���ɡ�
#endif
