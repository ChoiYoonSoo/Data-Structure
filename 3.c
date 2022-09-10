#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_STACK_SIZE 1000

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

void push(StackType* s, int item) {
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = item;
}

int pop(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

int peek(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)];
}

int main(void) {
	int board[5][5] = { {0,} };
	int pad[1000] = { 0, };
	int z = 0, cnt = 0;

	StackType a;
	init_stack(&a);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			scanf("%d ", &board[i][j]);
		}
	}
	for (int i = 0; i < 8; i++) {
		scanf("%d", &pad[i]);
	}

	for (int i = 0; i < 8; i++) {
		while (z < 5) {
			if (board[z][pad[i]-1] != 0) {
				if (!is_empty(&a) && board[z][pad[i] - 1] == peek(&a)) {
					cnt += 2;
					pop(&a);
					break;
				}
				push(&a, board[z][pad[i] - 1]);
				board[z][pad[i] - 1] = 0;
				z = 0;
				break;
			}
			z++;
		}
	}

	printf("%d", cnt);
	return 0;
}