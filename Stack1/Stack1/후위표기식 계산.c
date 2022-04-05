#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100

typedef struct {
	int data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return s->top == -1;
}

int is_full(StackType* s) {
	return s->top == (MAX_STACK_SIZE - 1);
}

void push(StackType* s,int value) {
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = value;
}

int pop(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

int peek(StackType* s) {
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	else return s->data[s->top];
}

int result_stack(char str[]) {
	StackType s;
	init_stack(&s);
	char ch;
	int len = strlen(str);
	int n1, n2,result;
	for (int i = 0; i < len; i++) {
		ch = str[i];
		if (ch != '+' && ch != '-' && ch != '/' && ch != '*') {
			result = ch - '0';
			push(&s, result);
		}
		else {
			n2 = pop(&s);
			n1 = pop(&s);
			if (ch == '+') push(&s, n1 + n2);
			else if (ch == '-') push(&s, n1 - n2);
			else if (ch == '/') push(&s, n1 / n2);
			else push(&s, n1 * n2);
		}

			
	}
	return pop(&s);
}

int main(void) {
	int result;
	printf("852/3-32*+\n");
	result = result_stack("852/3-32*+*");
	printf("°á°ú °ª: %d\n", result);
	return 0;
}