#ifndef __Stack_H
#define __Stack_H
#define Stack_TYPE int /* ��ջ���洢��ֵ���������� */
#define Stack_SIZE 100

void create_Stack(int size);
void destroy_Stack(void);
void push(Stack_TYPE value);
void pop(void);
Stack_TYPE top(void);
char is_empty(void);
char is_full(void);
#endif
