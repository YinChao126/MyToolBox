#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileHandle.h"

int main()
{
	int file_num = 0; //�����ļ������ж��ٸ��ļ�
	char *pattern = ".\\out\\*.txt"; //����./out�ļ���������txt��ʽ���ļ����˴�������ͨ���
	char file_result[5][MAX_FILE_NAME_LEN];  //���ҽ�������б���ʾ����һ���ֽڴ�����ļ����ĳ���
	char (*p)[MAX_FILE_NAME_LEN] = file_result;


	SearchDir(pattern, p, &file_num);

	return 0; 
}