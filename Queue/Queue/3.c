// 9번문제
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10
typedef int element;

typedef struct
{
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void error(char* massage)
{
	fprintf(stderr, "%s\n", massage);
	exit(1);
}

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
	return s->top == MAX_STACK_SIZE - 1;
}

void push(StackType* s, element item)
{
	if (is_full(s))
		error("Stack is full");
	else s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
	if (is_empty(s))
		error("Stack is empty");
	else return s->data[(s->top)--];
}

element peek(StackType* s)
{
	if (is_empty(s))
		error("Stack is empty");
	else return s->data[s->top];
}

int main(void)
{
	StackType s1;
	StackType s2;
	init_stack(&s1);
	init_stack(&s2);

	int n, nn, asd = 0;;
	printf("횟수 입력:");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("%d번째 입력값: ", i + 1);
		scanf("%d", &nn);
		push(&s1, nn);
	}

	for (int i = 0; i < n; i++) {
		if (!is_empty(&s1)) {
			asd = pop(&s1);
			push(&s2, asd);
		}
	}

	for (int i = 0; i < n; i++) {
		if(!is_empty(&s2))
			printf("%d ", pop(&s2));
	}
	return 0;
}