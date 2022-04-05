#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#define MAX_STRING_SIZE 100

typedef struct {
	int student_no;
	char name[MAX_STRING_SIZE];
	char addrees[MAX_STRING_SIZE];
}element;

element stack[MAX_STACK_SIZE];
int top = -1;

int is_full() {
	return (top == MAX_STACK_SIZE - 1);
}

int is_empty() {
	return (top == -1);
}

void push(element info) {
	if (is_full()) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	else {
		stack[++top] = info;
	}
}

element pop() {
	if (is_empty()) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else {
		return stack[top--];
	}
}

element peek() {
	if (is_empty()) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else {
		return stack[top];
	}
}

int main(void) {
	element n1 = { 21239243,"홍길동","충남" };
	element n2;

	push(n1);
	n2 = peek();

	printf("학번: %d\n", n2.student_no);
	printf("이름: %s\n", n2.name);
	printf("주소: %s\n", n2.addrees);
	return 0;
}