#include "Stack.h"
#include <assert.h>
Stack_TYPE Stack[Stack_SIZE];
static int top_element = -1;
void push(Stack_TYPE value)
{
	assert(!is_full()); /* ѹ���ջ֮ǰ���ж��Ƿ��ջ����*/
	top_element += 1;
	Stack[top_element] = value;
}
void pop(Stack_TYPE *Out)
{
	assert(!is_empty()); /* ������ջ֮ǰ���ж��Ƿ��ջ�ѿ� */
	*Out = Stack[top_element];
	top_element -= 1;
}

Stack_TYPE top(void)
{
	assert(!is_empty());
	return Stack[top_element];
}

char is_empty()
{
	return top_element == -1;
}

char is_full()
{
	return top_element == Stack_SIZE - 1;
}
