// 중위표기식을 문자열 형태로 후위표기식으로 변경하기 예시 2
// 스택안에 연산자를 넣어 다음 연산자가 나올시 꺼내서 쓰는데 a+b*c와 같이 먼저 나오는 연산자의 우선순위가
// 후에 나오는 연산자보다 낮을경우 식이 성립이 안됨. ex) ab+c* -> X, abc*+ -> O
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
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

void push(StackType* s, char ch) {
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
	else return s->data[s->top--];
}

char peek(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[s->top];
}

void mid_num(char str[]) {
	StackType s;
	init_stack(&s);

	int len = strlen(str);
	int index = 0;
	char ch;
	char ch2[100];

	for (int i = 0; i < len; i++) {
		ch = str[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			ch2[index] = ch;
			index++;
		}
		else {
			if (is_empty(&s)) {
				push(&s, ch);
			}
			else {
				ch2[index] = pop(&s);
				index++;
				push(&s, ch);
			}
		}
	}
	while (!is_empty(&s)) ch2[index] = pop(&s);
	for (int i = 0; i <= index; i++) {
		printf("%c", ch2[i]);
	}
}

int main(void) {
	printf("1*2+3을 후위표기식으로\n");
	mid_num("1*2+3");
	return 0;
}