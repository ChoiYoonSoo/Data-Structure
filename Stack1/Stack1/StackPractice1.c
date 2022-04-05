#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100

typedef int element;
element stack[MAX_STACK_SIZE];
int top = -1;

int empty() { //스택이 비어있으면 1, 아니면 0반환 
	return (top == -1);
}

int full() { //스택이 가득 차있으면 1, 아니면 0반환
	return (top == MAX_STACK_SIZE - 1);
}

void push(element item) { //스택에 요소 추가
	if (full()) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	else {
		stack[++top] = item;
	}
}

element pop() { //스택 요소 제거
	if (empty()) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else {
		return stack[top--];
	}
}

element peek() { //스택 상단 꺼내오기
	if (empty()) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else {
		return stack[top];
	}
}
int main(void) {
	push(1);
	push(2);
	push(3);
	pop();
	printf("%d\n", peek());
	return 0;
}