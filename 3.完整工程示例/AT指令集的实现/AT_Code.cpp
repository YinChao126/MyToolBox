#include "AT_Codec.h"
#include <string.h>
#include <stdlib.h>

//�û����޸Ĵ˴��������б�����ö�ٵĸ���һ���޸�
char const *AtCommand[] = {
	"HBNT",
	"RECVOP",
	"SVER",
	"ID",
	"SNR",
	"STAT",
	"SFO",
	"CFO",
	"TUNER",
	"QSRV",
	"TIME",
	"CKFO",
	"BDRT",
	"FREQ",
	"RMODE",
	"PPS1",
	"SERV",
	"STUD",
	"UDDA",
	"NULL"
};

enum CmdDefine
{
	HBNT, //����
	RECVOP,	//���ջ�����
	SVER,	//��ѯ����汾
	ID,	//��ѯ��ƷID
	SNR, //��ѯ�����
	STAT, //��ѯ״̬
	SFO,	//��ѯʱƫ
	CFO,	//��ѯƵƫ
	TUNER,	//��ѯtuner״̬
	QSRV,	//���յ�����Щҵ��
	TIME,	//����ʱ��
	CKFO,	//����У��ʧ���Ƿ����
	BDRT,	//���ò�����
	FREQ,	//����Ƶ��
	RMODE,	//���ý���ģʽ
	PPS1,	//����1PPS����
	SERV,	//�������ҵ����ض�ҵ��
	STUD,	//��������
	UDDA,	//������������
	TEST	//����
};

#define N_AtCommand (sizeof(AtCommand) / sizeof(AtCommand[0]))

int AtDecoder(char *Command, int *CmdId, double *RcvPara)
{
	int BiosAddr = -1;
	int index;
	for (index = 0; index < N_AtCommand; index++)
	{
		BiosAddr = KmpFind(Command, AtCommand[index]);
		if (BiosAddr >= 0)
		{
			break;
		}
	}
	if (BiosAddr < 0)
	{
		return -1; // no command matched.
	}

	*CmdId = index;

	if (BiosAddr != 3)
	{
		return -3; //ָ��û����.
	}

	int len;
	char *p;
	char value[10];
	int ValueLen;
	switch (index)
	{
	case HBNT:
		break;
	case RECVOP:
		break;
	case SVER: //get the cmd's parameter.
		len = strlen(Command); // total len
		BiosAddr += 5; // �˴���10���������� "SVER+"
		p = Command + BiosAddr;
		ValueLen = len - BiosAddr - 2;
		for (size_t i = 0; i < ValueLen; i++)
		{
			value[i] = *p++;
		}
		*RcvPara = atof(value);
		break;
	case ID:
		break;
	case SNR:
		break;
	case STAT:
		break;
	case SFO:
		break;
	case CFO:
		break;
	case TUNER:
		break;
	case QSRV:
		break;
	case TIME:
		break;
	case CKFO:
		break;
	case BDRT:
		break;
	case FREQ:
		break;
	case RMODE:
		break;
	case PPS1:
		break;
	case SERV:
		break;
	case STUD:
		break;
	case UDDA:
		break;
	case TEST: //ͨ�����ڻ�һ��"+OK\r\n"��Ϣ
		break;
	default:
		return -2; // decode the command, but cannot handled it.
	}
	return 0;
}