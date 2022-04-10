#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
typedef int element;

typedef struct
{
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return s->top == -1;
}

int is_full(StackType* s)
{
	return s->top == (MAX_STACK_SIZE - 1);
}

void push(StackType* s, element item)
{
	if (is_full(&s))
	{
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
	if (is_empty(&s))
	{
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s)
{
	if (is_empty(&s))
	{
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[s->top];
}

void delnum(char str[])
{
	StackType s;
	init_stack(&s);
	StackType b;
	init_stack(&b);
	
	int len = strlen(str);
	char n[100];
	char ch;
	int cnt = 0;

	for (int i = 0; i < len; i++)
	{
		push(&s, str[i]);
	}

	for (int i = 0; i < len; i++)
	{
		ch = pop(&s);
		if (ch != peek(&s))
		{
			push(&b, ch);
			cnt++;
		}
	}

	printf("출력: ");
	for (int i = 0; i < cnt; i++)
	{
		printf("%c", pop(&b));
	}
}

int main(void)
{
	char* str = (char*)malloc(sizeof(char) * MAX_STACK_SIZE);

	printf("정수를입력하시오: ");
	scanf("%s", str);

	delnum(str);

	free(str);
	return 0;
}