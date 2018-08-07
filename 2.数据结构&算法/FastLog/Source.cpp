#include <stdio.h>
#include <math.h>
/*
** log��������
** ����ʱ�䣺2017-3-3
** ���ߣ�����
** �汾�ţ�V1.1
** �������������ټ�����2Ϊ�׵Ķ���
** ���룺x->����
** �������
** ����ֵ��log2x�ļ���ֵ
** ��ע�� x�������1
** �޸�ʱ�䣺2017-7-19
** �޸ļ�¼��������m/k����ֵ��ʽ��ȡ���˳������㣬���������ٶ�
*/
#if 1
double FastLog(double x)
{
#if 1
	double m;
	int k = 0;
	int op = 0xFFFFFFFE;
	int tmp = 1;
	if (x <= 1)		return 0;
	while ((int)x & op)
	{
		op <<= 1;
		tmp <<= 1;
		k++;
	}
	m = x / tmp - 1;
#else	
	double m;
	int k = 1, op = 2;
	if (x <= 1)		return 0;
	while ((x / op) >= 2)
	{
		op <<= 1;
		k++;
	}
	m = x / op - 1;
#endif
	if (m <= 0.25)		return 1.3125 * m + k;
	else if (m <= 0.5)	return 1.078125 * m + 0.00015625 + k;
	else if (m <= 0.75)	return 1.015625 * m + 0.0625 + k;
	else if (m <= 1)	return 0.75 * m + 0.25 + k;
	else				return 0; 
}
#else
double FastLog(double x)
{
	double m;
	int k = 1, op = 2;
	int i;
	while ((x / op) >= 2)
	{
		op <<= 1;
		k++;
	}
	m = x / op - 1;
	double logtemp;
	if (m <= 0.25)
	{
		logtemp = 1.3125 * m;
	}
	else if (m <= 0.5)
	{
		logtemp = 1.078125 * m + 0.00015625;
	}
	else if (m <= 0.75)
	{
		logtemp = 1.015625 * m + 0.0625;
	}
	else if (m <= 1)
	{
		logtemp = 0.75 * m + 0.25;
	}
	else
	{
		printf("error\n");
		return 0;
	}
	return (logtemp + k);
}
#endif

int FastLog2(int x) //̫�ֲ�
{
	float fx;
	unsigned long ix, exp;

	fx = (float)x;
	ix = *(unsigned long*)&fx;
	exp = (ix >> 23) & 0xFF;

	return exp - 127;
}
//#define Val 1.5

int main()
{
	double x, y, z;
	double Val = 1.5;
#if 0
	FILE *Fout;
	Fout = fopen("Result.txt", "w");
	for (size_t i = 1; i < 10000; i++)
	{
		y = log2((double)i);
		z = FastLog(i);
		x = (z - y) / z * 100;
		fprintf(Fout, "%f\n", x);
	}
	fclose(Fout);
#else 
	//x = log2(2.0);
	x = FastLog2(Val);
	y = log2((double)Val);
	z = FastLog(Val);
#endif
	return 0;
}
