#ifndef _AT_CODEC_H_
#define _AT_CODEC_H_
#include "KMP.h"

/*
** 原型:int AtDecoder(char *Command, int *CmdId, double *RcvPara)
** 作者：尹超
** 日期：2017-4-2
** 描述：一个AT指令集的示例程序
** 输入：Command -> 收到的指令字符串
** 输出：CmdId -> 解析出该字符串属于命令列表的第几行（第几号命令）
**		RcvPara -> 解析出的命令参数（如果有的话）
** 返回值：	0  -> 工作正常，输入命令得到解析并正确处理
**			-1 -> 命令不匹配
**			-2 -> 解析出正确的命令，但没有找到对应的处理过程（一般不会出现）
** 备注：	1. 该函数只是测试程序，仅供演示如何解析命令并得到参数
**			2. 输出参数如果有多个，则必须改成数组输出。如果类型各不一样，则需要
**			改成结构体输出
*/
int AtDecoder(char *Command, int *CmdId, double *RcvPara);

#endif