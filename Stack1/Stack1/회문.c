#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef int element;

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
	return s->top == (MAX_STACK_SIZE - 1);
}

void push(StackType* s, element item) {
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = item;
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

void palidrome(char str[]) {
	StackType s;
	init_stack(&s);

	char str2[100];
	char ch;

	int idx = 0;
	int cnt = 0;
	int len = strlen(str);

	for (int i = 0; i < len; i++) { // str배열중 알파벳소문자만 str2에 순서대로 저장
		ch = str[i];
		if (ch >= 65 && ch <= 90) {
			ch = ch + 32;
		}
		if (ch >= 'a' && ch <= 'z') {
			str2[idx++] = ch;
		}
	}

	for (int i = 0; i < idx; i++) { // str2배열 요소들을 순서대로 스택에 저장
		ch = str2[i];
		push(&s, ch);
	}

	for (int i = 0; i < idx; i++) {
		if (str2[i] == pop(&s)) {
			cnt++;
		}
	}

	if (cnt == idx) {
		printf("회문입니다\n");
	}
	else
		printf("회문이아닙니다.");
}
int main(void) {
	char str[100];
	printf("문자열을 입력하시오: ");
	gets(str);
	palidrome(str);
	return 0;
}