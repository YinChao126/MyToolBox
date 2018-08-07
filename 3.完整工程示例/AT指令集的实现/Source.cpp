#include "AT_Codec.h"
#include <stdio.h>
#include <Windows.h>


int main()
{
	char *RecStr = "AT+SVER=98.176\r\n";
	int id;
	double value;
	AtDecoder(RecStr, &id, &value);
	system("pause");

	return 0;
}