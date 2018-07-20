/************************************************************************/
/* 模块名：csv_io
** 作者：尹超
** 描述：该模块用以实现C环境下的csv文件读写操作，并带有示例程序
** 更新时间：2018-5-30													*/
/************************************************************************/
#ifndef CSV_IO_H
#define CSV_IO_H
#include <stdio.h>

extern FILE *csv_out_file; //统一的csv写入句柄

void CsvCreateFile(char *file_name);
void CsvCloseFile(void);
void CsvWriteRecord(char *sub_file_name, int para1, float para2); //写入范例，实际应用需修改
int CsvReadExample(char *file_name); // 读出范例，实际应用需修改

#endif
