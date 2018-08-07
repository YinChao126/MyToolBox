#include "AT_Codec.h"
#include <string.h>
#include <stdlib.h>

//用户请修改此处的命令列表，后面枚举的跟随一起修改
char const *AtCommand[] = {
	"open",
	"connect",
	"parameter",
	"tras",
	"close",
	"NULL"
};

enum CmdDefine
{
	OPEN,
	CONNECT,
	PARAMETER,
	TRANS,
	CLOSE
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

	int len;
	char *p;
	char value[10];
	int ValueLen;
	switch (index)
	{
	case OPEN:
		break;
	case CONNECT:
		break;
	case PARAMETER: //get the cmd's parameter.
		len = strlen(Command); // total len
		BiosAddr += 10; // 此处的10是数出来的 "parameter+"
		p = Command + BiosAddr;
		ValueLen = len - BiosAddr - 2;
		for (size_t i = 0; i < ValueLen; i++)
		{
			value[i] = *p++;
		}
		*RcvPara = atof(value);
		break;
	case TRANS:
		break;
	case CLOSE:
		break;
	case 5:
		break;
	default:
		return -2; // decode the command, but cannot handled it.
	}
	return 0;
}