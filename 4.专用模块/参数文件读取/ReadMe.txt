创建时间：2016-12-14
创建人：尹超
文档说明：该文档主要实现了一个函数，该函数用来读取一个字符串中数据并可自动判断数据类型
背景：CDRadio的DSP实现过程中，Debug模式下所有的参数只能通过写文件的方式进行配置。需要一个
能够随意读取并解析配置文件信息的函数。
注意：一定要#include <stdlib.h>否则会出bug
 原型：char GetValueFromStr(const char *SrcStr, const char *StrFind, const char separator, void *RetValue)
 
 bug修复：
 GetValueFromStr函数中存在一个问题，如果最后一个参数没有空行（找不到\n标识符），会出错
 
 现在的源码里已经修复。但是示例程序没有修复！！！