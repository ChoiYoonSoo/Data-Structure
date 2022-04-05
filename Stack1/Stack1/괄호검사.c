#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
typedef char element;

typedef struct {
	int top;
	element data[MAX_STACK_SIZE];
}StackType;

void init_stack(StackType* s) { // top위치 설정
	s->top = -1;
}

int is_empty(StackType* s) { // 스택 공백 검사
	return s->top == -1;
}

int is_full(StackType* s) { // 스택 포화 검사
	return s->top == (MAX_STACK_SIZE - 1);
}

void push(StackType* s,char str) { // 스택 집어넣기
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = str;
}

element pop(StackType* s) { // 스택 최상단값 꺼내고 삭제
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) { // 스택 최상단값 꺼내기
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[s->top];
}

int check_matching(char str[]) { // 수식 검사
	StackType s;
	StackType n;

	char ch, popch;
	int len = strlen(str);
	int number = 1;

	init_stack(&s);
	init_stack(&n);

	printf("괄호 수: ");
	for (int i = 0; i < len; i++) {
		ch = str[i];

		switch (ch) {
		case'[': case'(':  case'{': { 
			push(&s, ch);
			push(&n, number);
			printf("%d ", number);
			number++;
			break;
		}
		case']': case')': case'}': {
			if (is_empty(&s)) return 0;
			popch = pop(&s);
			if ((popch == '[' && ch != ']') ||
				(popch == '(' && ch != ')') ||
				(popch == '{' && ch != '}')) {
				return 0;
			}
			printf("%d ", pop(&n));
			break;
		}
		}
	}
	if (!is_empty(&s)) return 0;
	return 1;
}

int main(void) {
	char str[100];

	printf("수식 입력: ");
	scanf("%s", str);

	printf("수식: ");
	printf("%s\n", str);

	if (check_matching(str) == 1) {
		printf("\n괄호 검사 성공\n");
	}
	else {
		printf("\n괄호 검사 실패\n");
	}

	return 0;
}