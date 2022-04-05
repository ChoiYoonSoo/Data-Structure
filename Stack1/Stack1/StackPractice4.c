#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
typedef int element;

typedef struct {
	element* data;
	int top;
	int size;
}StackType;

void init_Stack(StackType* s) {
	s->top = -1;
	s->size = 1;
	s->data = (element*)malloc(sizeof(element) * s->size);
	if (s->data == NULL) {
		fprintf(stderr, "Memory Error");
		exit(1);
	}
}

int is_empty(StackType* s) {
	if (s->top == -1) {
		return 1;
	}
	return 0;
}

int is_full(StackType* s) {
	if (s->top == (s->size - 1)) {
		return 1;
	}
	return 0;
}

void push(StackType* s,element value) {
	if (is_full(s)) {
		s->size *= 2;
		s->data = (element*)realloc(s->data,sizeof(element) * s->size);
	}
	s->data[++(s->top)] = value;

	printf("pushed: %d\n", value);
}

element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[s->top];
}

int main(void) {
	StackType s;
	init_Stack(&s);

	push(&s, 3);
	push(&s, 2);
	push(&s, 1);

	printf("%d\n", peek(&s)); 
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));

	free(s.data);
	return 0;
}
