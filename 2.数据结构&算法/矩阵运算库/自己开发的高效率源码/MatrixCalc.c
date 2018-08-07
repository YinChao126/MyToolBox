#include "MatrixCalc.h"
#include <memory.h>
#include <stdio.h>
MATRIX_TYPE *MatAdd(MATRIX_TYPE *A, MATRIX_TYPE *B, int Row, int Column) //return: A+B
{
	MATRIX_TYPE *pResult, *pTemp;
	int i, j;
	if (Row <= 0 || Column <= 0)
	{
		return NULL;
	}
	pResult = (MATRIX_TYPE *)malloc(Row * Column * sizeof(MATRIX_TYPE));
	if (pResult == NULL)
	{
		return NULL;
	}
	pTemp = pResult;
	memset(pResult, 0, Row * Column * sizeof(MATRIX_TYPE));

	for (i = 0; i < Row; i++)
	{
		for (j = 0; j < Column; j++)
		{
			*pResult++ = A[i*Column + j] + B[i*Column + j];
		}
	}
	pResult = pTemp;
	return pResult;
}

MATRIX_TYPE *MatSub(MATRIX_TYPE *A, MATRIX_TYPE *B, int Row, int Column) //return: A-B
{
	MATRIX_TYPE *pResult, *pTemp;
	int i, j;
	if (Row <= 0 || Column <= 0)
	{
		return 0;
	}
	pResult = (MATRIX_TYPE *)malloc(Row * Column * sizeof(MATRIX_TYPE));
	if (pResult == NULL)
	{
		return NULL;
	}
	pTemp = pResult;
	memset(pResult, 0, Row * Column * sizeof(MATRIX_TYPE));

	for (i = 0; i < Row; i++)
	{
		for (j = 0; j < Column; j++)
		{
			*pResult++ = A[i*Column + j] - B[i*Column + j];
		}
	}
	pResult = pTemp;
	return pResult;
}

MATRIX_TYPE *MatMulti(MATRIX_TYPE *A, int Ra, int Ca, MATRIX_TYPE *B, int Rb, int Cb)//return: A*B
{
	MATRIX_TYPE *pResult, *pTemp;
	int i, j, k;
	if (Ca != Rb || Ra <= 0 || Ca <= 0 || Cb <= 0)
	{
		return 0;
	}
	pResult = (MATRIX_TYPE *)malloc(Ra * Cb * sizeof(MATRIX_TYPE));
	if (pResult == NULL)
	{
		return NULL;
	}
	pTemp = pResult;
	memset(pResult, 0, Ra * Cb * sizeof(MATRIX_TYPE));

	for (i = 0; i < Ra; i++) 
	{
		for (j = 0; j < Cb; j++)
		{
			for (k = 0; k < Ca; k++) 
			{
				*pResult += A[i*Ca + k] * B[j + k * Cb];
			}
			pResult++;
		}
	}
	pResult = pTemp;
	return pResult;
}