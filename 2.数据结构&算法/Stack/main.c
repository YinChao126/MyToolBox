#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

int main(void)
{
	int val;
	push(10); push(9); push(7); push(6); push(5);
	push(4);  push(3); push(2); push(1); push(0);
	printf("push压入数值后：\n");

	printf("\n");
	pop(&val);
	pop(&val);
	printf("经过pop弹出几个元素后的堆栈元素:\n");

	printf("\n");
	printf("top()调用出来的值: %d\n", top());
	return 1;
}
