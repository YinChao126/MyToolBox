#include "pcre.h"


int file_filter(char *reg_pattern, char *target_str)
{
	pcre *cstr;
	int erroroffset;
	int num;
	const char * error;
	char result[30];
	int ovector[OVECCOUNT];
	cstr = pcre_compile(reg_pattern, 0, &error, &erroroffset, NULL);
	num = pcre_exec(cstr, NULL, target_str, strlen(target_str), 0, 0, ovector, (10) * 3);
	return num;
}