#include "Stack.h"
#include <assert.h>
Stack_TYPE Stack[Stack_SIZE];
static int top_element = -1;
void push(Stack_TYPE value)
{
	assert(!is_full()); /* 压入堆栈之前先判断是否堆栈已满*/
	top_element += 1;
	Stack[top_element] = value;
}
void pop(Stack_TYPE *Out)
{
	assert(!is_empty()); /* 弹出堆栈之前先判断是否堆栈已空 */
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
