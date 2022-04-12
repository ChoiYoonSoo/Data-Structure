#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_STACK_SIZE 100
typedef int element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) { // 스택 생성
	s->top = -1;
}

int is_empty(StackType* s) { // 스택 공백 상태 확인
	return s->top == -1;
}

int is_full(StackType* s) { // 스택 포화 상태 확인
	return s->top == (MAX_STACK_SIZE - 1);
}

void push(StackType* s, element item) { // 스택 삽입
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s) { // 스택 삭제
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	return s->data[(s->top)--];
}

element peek(StackType* s) { // 스택 top위치
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	return s->data[s->top];
}

int prec(char ch) { // 연산자 우선순위 (반환값이 클수록 먼저계산)

	switch (ch)
	{
	case'|': return 1;
	case'&': return 2;
	case'<': case'>': return 3;
	case'+': case'-': return 4;
	case'*': case'/': case'%': return 5;
	case'^': return 6;
	}
	return -1;
}

void infix_to_postfix(char str[], char str2[]) { // 중위표기식 -> 후위표기식 변환
	StackType s;
	init_stack(&s);

	char ch, topch, endch;
	int len = strlen(str);
	int idx = 0;
	int npu = 1;

	printf("\n\n===================중위표기식 -> 후위표기식=================\n\n");
	for (int i = 0; i < len; i++) {
		ch = str[i];
		switch (ch)
		{
		case'|': case'&': case'<': case'>': case'+': case'-': case'*': case'/': case'%': case'^': { // 연산자일 경우 실행
			if (!is_empty(&s) && ch == '^' && ch == peek(&s, ch)) {
				printf("\n%d번 스택 PUSH -> [ %c ]\n", npu++, ch);
				push(&s, ch);
				break;
			}
			while (!is_empty(&s) && prec(ch) <= prec(peek(&s))) { // 스택에 있는 연산자의 우선순위가 더 높을경우
				printf("\n%d번 스택 POP -> [ %c ]  \n", --npu, peek(&s));
				str2[idx++] = pop(&s);
			}
			printf("\n%d번 스택 PUSH -> [ %c ]\n",npu++, ch);
			push(&s, ch);
			break;
		}
		case'(': { // 열린괄호일 경우
			printf("\n%d번 스택 PUSH -> [ %c ]\n",npu++, ch);
			push(&s, ch);
			break;
		}
		case')': { // 닫힌괄호일 경우
			printf("\n[ ) ] 연산자 발견\n");
			topch = pop(&s);
			printf("\n%d번 스택 POP- > [ %c ]\n",--npu, topch);

			while (topch != '(') { // '('문자가 나올때까지 모두 pop
				str2[idx++] = topch;
				topch = pop(&s);
				printf("\n%d번 스택 POP -> [ %c ]\n",--npu, topch);
			}
			break;
		}
		default: // 피연산자일경우 배열에 저장
			printf("\n피연산자 %c 저장\n", ch);
			str2[idx++] = ch;
			break;
		}
	}

	while (!is_empty(&s)) { // 스택에 남아있을경우
		endch = pop(&s);
		printf("\n%d번 스택 POP -> [ %c ]\n",--npu, endch);
		str2[idx++] = endch;
	}

	str2[idx] = NULL;
	printf("\ninfix to postfix: ");

	for (int i = 0; i < idx; i++) {
		printf("%c", str2[i]);
	}
	printf("\n");
}

void postfix_eval(char str[]) { // 후위표기식 계산
	StackType s;
	init_stack(&s);

	char ch;
	int len = strlen(str);
	int n1, n2, result, n=1;

	printf("\n\n=========== 후위표기식 계산 ==========\n\n");
	for (int i = 0; i < len; i++) {
		ch = str[i];
		// 연산자가 아닐 경우
		if (ch != '+' && ch != '-' && ch != '/' && ch != '*' && ch != '^' && ch != '>' && ch != '<' && ch != '=' && ch != '&' && ch != '|' && ch != '%') {
			result = ch - '0';
			printf("\n%d번 스택 PUSH -> %d\n",n++, result);
			push(&s, result);
		}
		else { // 연산자일 경우 두 개의 피연산자 꺼내와서 계산 후 push
			n2 = pop(&s);
			n1 = pop(&s);
			printf("\n[ %c 연산자 발견 두 개의 피연산자 POP]\n",ch);
			printf("\n%d번 스택 POP -> %d\n",--n, n2);
			printf("\n%d번 스택 POP -> %d\n",--n, n1);
			switch (ch) {
			case'+': // +연산 실행
				push(&s, n1 + n2);
				printf("\n%d + %d 결과값 PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'-': // -연산 실행
				push(&s, n1 - n2);
				printf("\n%d - %d 결과값 PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'/': // /연산 실행
				push(&s, n1 / n2);
				printf("\n%d / %d 결과값 PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'*': // *연산 실행
				push(&s, n1 * n2);
				printf("\n%d * %d 결과값 PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'^': // 거듭제곱 연산 실행
				push(&s, pow(n1, n2));
				printf("\n%d ^ %d 결과값 PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'>': // 대소비교
				push(&s, n1 > n2);
				printf("\n%d > %d 결과값 PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'<': // 대소비교
				push(&s, n1 < n2);
				printf("\n%d < %d 결과값 PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'=': // ==연산 실행
				push(&s, n1);
				printf("\n%d == %d 결과값 PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'&': // &&연산 실행
				push(&s, n1 && n2);
				printf("\n%d && %d 결과값 PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'|': // ||연산 실행
				push(&s, n1 || n2);
				printf("\n%d || %d 결과값 PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'%': // %연산 실행
				push(&s, n1 % n2);
				printf("\n%d %c %d 결과값 PUSH -> %d\n", n1, 37, n2, peek(&s));
				n++;
				break;
			}
		}
	}
	printf("\n결과값: %d\n", pop(&s));
}
int main(void) {
	char str[100];
	char str2[100];
	int n;

	do {
		printf("중위표기식 수식 입력: ");
		scanf("%s", str);
		infix_to_postfix(str, str2);
		postfix_eval(str2);

		printf("\n1.계속\n");
		printf("2.종료\n");
		scanf("%d", &n);

		if (n == 2) {
			printf("\n프로그램을 종료합니다.\n");
			break;
		}
	} while (1);

	return 0;
}