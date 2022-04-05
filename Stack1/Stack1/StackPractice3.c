#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
typedef int element;

typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}


int is_full(StackType* s) {
	return (s->top == MAX_STACK_SIZE-1);
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	else {
		s->stack[++(s->top)] = item;
	}
	printf("\npushed: %d\n", item);
}

element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else {
		return s->stack[(s->top)--];
	}
	
}

element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else {
		return s->stack[s->top];
	}
}

int main(void) {
	StackType s;

	init_stack(&s);
	push(&s, 3);
	push(&s, 2);
	push(&s, 1);
	
	printf("\n%d\n", pop(&s));
	printf("\n%d\n", pop(&s));
	printf("\n%d\n", pop(&s));
	printf("\n%d\n", pop(&s));
	return 0;
}