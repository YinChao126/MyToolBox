#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/* 原型: char GetValueFromStr(const char *SrcStr, const char *StrFind, const char separator, void *RetValue)                                                                   
** 作者：尹超
** 时间：2016-12-14
** 描述：从一个字符串中查找特征字符串，如果匹配，则将分隔符后面的内容解析
** 成数值，遇到“，”等分隔符或换行符，自动停止.可以自动判断数据类型
** 输入：SrcStr->源字符串	StrFind->待查找的特征值	    separator->分隔符
** 输出：RetValue->获得的浮点型或整型的配置参数
** 返回值：找到的数据。如果没找到，返回NULL
** 备注：如果使用了不匹配的类型来接收返回值，会得到错误的结果
** Bug:数据类型判断只是用了很粗糙的数据位数判断，不准确，有待日后改进	*/
/************************************************************************/
static char GetValueFromStr(const char *SrcStr, const char *StrFind, const char separator, void *RetValue)
{
	char *p;
	char Buff[100];
	int i = 0;
	int TypeFlag = 0; //自动识别数据类型	0->16位短整型	1->32位长整型	2->64位长整型	3->浮点型
	int SignFlag = 0; //自动识别正负数		0->正数			1->负数
	int Len = strlen(StrFind);
	p = strstr(SrcStr, StrFind);
	if (p == NULL)
	{
		//字符串不匹配，字符串不包含特征值
		return -1;
	}
	p += Len;
	while (*p != separator)
	{
		p++;
		if (*p == '\n')
		{
			//printf("分隔符搞错了！\n");
			return -1;
		}
	}
	p++;
	while ((*p != '\n') && (*p != '\r') && (i < 100) && (*p != separator) && (*p != ','))//此处可以修改以提前停止读入数据
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
		if (*p == '-') //暂未实现任何功能，根据具体需要添加之，如不需要，可删除该功能
		{
			SignFlag = 1;
		}
		Buff[i] = *p;
		i++;
		p++;
	}

	/*类型判断*/
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

	if (TypeFlag == 0) //16位整型
	{
		*(int *)RetValue = atoi(Buff);
	}
	else if (TypeFlag == 1) //32位整型
	{
		*(long *)RetValue = atol(Buff);
	}
	else if (TypeFlag == 2) //64位整型
	{
		*(long long *)RetValue = atoll(Buff);
	}
	else if (TypeFlag == 3) //浮点
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

//读取配置文件，并将数据存入全局变量中
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