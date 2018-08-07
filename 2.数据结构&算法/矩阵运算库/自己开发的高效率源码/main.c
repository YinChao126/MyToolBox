#include "MatrixCalc.h"
#include <stdio.h>

int main()
{
	MATRIX_TYPE a[12] = { 1, 3, 6, 2, 8, 7, 6, 5, 0, 9, 7, 6 };
	MATRIX_TYPE b[12] = { 3, 74, 2, 8, 4, 0, 1, 5, 7, 5, 0, 0 };
	MATRIX_TYPE c[16] = { 0 };
	MATRIX_TYPE *p;
	//p = MatMulti(a, 4, 3, b, 3, 4);
	p = MatAdd(a, b, 2, 6);
	for (int i = 0; i < 12; i++)
	{
		printf("%f\n ", p[i]);
	}
	free(p);
	return 0;
}