#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileHandle.h"

int main()
{
	int file_num = 0; //检测该文件夹下有多少个文件
	char *pattern = ".\\out\\*.txt"; //查找./out文件夹下所有txt格式的文件，此处可以用通配符
	char file_result[5][MAX_FILE_NAME_LEN];  //查找结果：以列表显示，第一个字节代表该文件名的长度
	char (*p)[MAX_FILE_NAME_LEN] = file_result;


	SearchDir(pattern, p, &file_num);
	int i;
	for (i = 0; i < file_num; i++)
	{
		char name[50] = ".\\out\\";
		strcat(name, file_result[i]); //获取完整文件名
		remove(name); //删除./out/目录下所有txt文件
	}

	return 0; 
}