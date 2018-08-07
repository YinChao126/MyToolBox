#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/* ԭ��: char GetValueFromStr(const char *SrcStr, const char *StrFind, const char separator, void *RetValue)                                                                   
** ���ߣ�����
** ʱ�䣺2016-12-14
** ��������һ���ַ����в��������ַ��������ƥ�䣬�򽫷ָ�����������ݽ���
** ����ֵ�������������ȷָ������з����Զ�ֹͣ.�����Զ��ж���������
** ���룺SrcStr->Դ�ַ���	StrFind->�����ҵ�����ֵ	    separator->�ָ���
** �����RetValue->��õĸ����ͻ����͵����ò���
** ����ֵ���ҵ������ݡ����û�ҵ�������NULL
** ��ע�����ʹ���˲�ƥ������������շ���ֵ����õ�����Ľ��
** Bug:���������ж�ֻ�����˺ֲܴڵ�����λ���жϣ���׼ȷ���д��պ�Ľ�	*/
/************************************************************************/
static char GetValueFromStr(const char *SrcStr, const char *StrFind, const char separator, void *RetValue)
{
	char *p;
	char Buff[100];
	int i = 0;
	int TypeFlag = 0; //�Զ�ʶ����������	0->16λ������	1->32λ������	2->64λ������	3->������
	int SignFlag = 0; //�Զ�ʶ��������		0->����			1->����
	int Len = strlen(StrFind);
	p = strstr(SrcStr, StrFind);
	if (p == NULL)
	{
		//�ַ�����ƥ�䣬�ַ�������������ֵ
		return -1;
	}
	p += Len;
	while (*p != separator)
	{
		p++;
		if (*p == '\n')
		{
			//printf("�ָ�������ˣ�\n");
			return -1;
		}
	}
	p++;
	while ((*p != '\n') && (*p != '\r') && (i < 100) && (*p != separator) && (*p != ','))//�˴������޸�����ǰֹͣ��������
	{
		if (*p == ' ')
		{
			p++;
			continue;
		}
		if (*p == '.')
		{
			TypeFlag = 3;
		}
		if (*p == '-') //��δʵ���κι��ܣ����ݾ�����Ҫ���֮���粻��Ҫ����ɾ���ù���
		{
			SignFlag = 1;
		}
		Buff[i] = *p;
		i++;
		p++;
	}

	/*�����ж�*/
	if (TypeFlag != 3) 
	{
		if (i < 5)
		{
			TypeFlag = 0;
		}
		else if (i < 10)
		{
			TypeFlag = 1;
		}
		else
		{
			TypeFlag = 2;
		}
	}

	if (TypeFlag == 0) //16λ����
	{
		*(int *)RetValue = atoi(Buff);
	}
	else if (TypeFlag == 1) //32λ����
	{
		*(long *)RetValue = atol(Buff);
	}
	else if (TypeFlag == 2) //64λ����
	{
		*(long long *)RetValue = atoll(Buff);
	}
	else if (TypeFlag == 3) //����
	{
		*(double *)RetValue = atof(Buff);
	}
	else
	{
		//error
	}
	return 0;
}

double center_freq = 0;
int tone_index_left = 0;
int tone_index_right = 0;
int daq_time = 0;
int run_time = 0;
int form_code = 0;


int sub_frame_number = 0;
struct ServPara
{
	int sid;
	int form_code;
	int ldpc_num;
	int ldpc_rate;
	int intv_size;
	int qam_type;
};
struct ServPara test[10];

//��ȡ�����ļ����������ݴ���ȫ�ֱ�����
char ReadRxPara(char *FilePath)
{
	FILE *FileIn;
	char tmp[100];
	int i = 0;

	double fvalue;
	int ivalue;

	FileIn = fopen(FilePath, "rb");
	if (FileIn == NULL)
	{
		return -1;
	}

	while (NULL != fgets(tmp, 100, FileIn))
	{
		i++;
		if (GetValueFromStr(tmp, "center_freq", '=', &fvalue) == 0)
		{
			center_freq = fvalue;
			continue;
		}
		if (GetValueFromStr(tmp, "tone_index_left", '=', &ivalue) == 0)
		{
			tone_index_left = ivalue;
			continue;
		}
		if (GetValueFromStr(tmp, "tone_index_right", '=', &ivalue) == 0)
		{
			tone_index_right = ivalue;
			continue;
		}
		if (GetValueFromStr(tmp, "daq_time", '=', &ivalue) == 0)
		{
			daq_time = ivalue;
			continue;
		}
		if (GetValueFromStr(tmp, "run_time", '=', &ivalue) == 0)
		{
			run_time = ivalue;
			continue;
		}
		if (GetValueFromStr(tmp, "form_code", '=', &ivalue) == 0)
		{
			form_code = ivalue;
			continue;
		}
	}
	fclose(FileIn);
	return 0;
}

char ReadTxPara(char *FilePath)
{
	FILE *FileIn;
	char tmp[100];
	int i = 0;
	int j = 0;
	double fvalue;
	int ivalue;

	FileIn = fopen(FilePath, "rb");
	if (FileIn == NULL)
	{
		return -1;
	}

	while (NULL != fgets(tmp, 100, FileIn))
	{
		i++;
		if (GetValueFromStr(tmp, "center_freq", '=', &fvalue) == 0)
		{
			center_freq = fvalue;
			continue;
		}
		if (GetValueFromStr(tmp, "tone_index_left", '=', &ivalue) == 0)
		{
			tone_index_left = ivalue;
			continue;
		}
		if (GetValueFromStr(tmp, "tone_index_right", '=', &ivalue) == 0)
		{
			tone_index_right = ivalue;
			continue;
		}
		if (GetValueFromStr(tmp, "daq_time", '=', &ivalue) == 0)
		{
			daq_time = ivalue;
			continue;
		}
		if (GetValueFromStr(tmp, "run_time", '=', &ivalue) == 0)
		{
			run_time = ivalue;
			continue;
		}
		if (GetValueFromStr(tmp, "sub_frame_number", '=', &ivalue) == 0)
		{
			sub_frame_number = ivalue;
			continue;
		}
		if (GetValueFromStr(tmp, "sid", '=', &ivalue) == 0)
		{
			test[j].sid = ivalue;
			GetValueFromStr(tmp, "form_code", '=', &ivalue);
			test[j].form_code = ivalue;
			GetValueFromStr(tmp, "ldpc_num", '=', &ivalue);
			test[j].ldpc_num = ivalue;
			GetValueFromStr(tmp, "ldpc_rate", '=', &ivalue);
			test[j].ldpc_rate = ivalue;
			GetValueFromStr(tmp, "intv_size", '=', &ivalue);
			test[j].intv_size = ivalue;
			GetValueFromStr(tmp, "qam_type", '=', &ivalue);
			test[j].qam_type = ivalue;
			j++;
		}
	}
	fclose(FileIn);
	return 0;
}

int main()
{

	ReadRxPara("RxSettings.cfg");
	ReadTxPara("TxSettings.cfg");
	return 0;
}