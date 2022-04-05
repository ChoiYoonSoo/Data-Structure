#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct {
	char data[MAX_STACK_SIZE];
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

void push(StackType* s,char ch) {
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = ch;
}

char pop(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

char peek(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)];
}

int prec(char ch) {
	switch (ch){
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}

void change_num(char str[]) {
	StackType s;
	init_stack(&s);

	int len = strlen(str);
	char ch, top;

	for (int i = 0; i < len; i++) {
		ch = str[i];
		switch (ch){
		case'+': case'-': case'*': case'/': {
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				printf("%c", pop(&s));
			push(&s, ch);
			break;
		}
		case'(': {
			push(&s, ch);
			break;
		}
		case')': {
			top = pop(&s);
			while (top != '(') {
				printf("%c", top);
				top = pop(&s);
			}
			break;
		}
		default:
			printf("%c", ch);
			break;
		}
	}
	while (!is_empty(&s))
		printf("%c", pop(&s));
}
int main(void) {
	char* str = "(2+3)*4+9";
	printf("중위표기식: %s\n", str);
	printf("후위표기식 변환: ");
	change_num(str);
	return 0;
}