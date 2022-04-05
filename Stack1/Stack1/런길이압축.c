#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef char element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return s->top == -1;
}

int is_full(StackType* s) {
	return s->top == (MAX_STACK_SIZE -1);
}

void push(StackType* s, char ch) {
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = ch;
}

element pop(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)];
}

void runLength(char str[]) {
	StackType s;
	init_stack(&s);

	int i = 0, n = 0;
	int cnt = 1;
	int len = strlen(str);
	char ch;

	while (str[len-i] >= 0) {
		ch = str[len-i];
		if (ch < 97) {
			ch = ch + 32;
		}
		push(&s, ch);
		i++;
	}

	while (n < len) {
		ch = pop(&s);
		if (ch == peek(&s)) {
			cnt++;
		}
		else {
			printf("%d%c", cnt, ch);
			cnt = 1;
		}
		n++;
	}
	
}

int main(void) {
	char str[100];
	printf("문자열을 입력하시오: ");
	scanf("%s", str);
	runLength(str);

	return 0;
}