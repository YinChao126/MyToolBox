#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

int main(void)
{
	int val;
	push(10); push(9); push(7); push(6); push(5);
	push(4);  push(3); push(2); push(1); push(0);
	printf("pushѹ����ֵ��\n");

	printf("\n");
	pop(&val);
	pop(&val);
	printf("����pop��������Ԫ�غ�Ķ�ջԪ��:\n");

	printf("\n");
	printf("top()���ó�����ֵ: %d\n", top());
	return 1;
}
