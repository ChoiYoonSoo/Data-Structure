#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_STACK_SIZE 100
typedef int element;

typedef struct { // 스택 생성
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) { // top위치 초기화
	s->top = -1;
}

int is_empty(StackType* s) { // 스택 공백 검사
	return s->top == -1;
}

int is_full(StackType* s) { // 스택 포화 검사
	return s->top == (MAX_STACK_SIZE - 1);
}

void push(StackType* s, element item) { // 스택 집어넣기
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s) { // 스택 최상단 위치 값 꺼내고 삭제
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) { // 스택 최상단 위치 값 꺼내기
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)];
}

int check_matching(char str[]) { // 괄호 수식 검사 함수
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
		case'[': case'(':  case'{': { // 열린 괄호 나오면 스택에 저장, 숫자도 스택에 저장
			push(&s, ch);
			push(&n, number);
			printf("%d ", number);
			number++;
			break;
		}
		case']': case')': case'}': { // 닫힌 괄호 나오면 스택의 상단 값 꺼내서 비교
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
	if (!is_empty(&s)) return 0; // 스택에 남아있는 수식 확인
	return 1;
}

void runLength(char str[]) { // 문자열 길이 압축
	StackType s;
	init_stack(&s);

	int i = 0, n = 0;
	int cnt = 1;
	int len = strlen(str);
	char ch;

	while (str[len - i] >= 0) { // 대문자 -> 소문자 변환 후 스택 저장
		ch = str[len - i];
		if (ch >= 65 && ch <= 90) {
			ch = ch + 32;
		}
		push(&s, ch);
		i++;
	}

	while (n < len) { // pop해서 얻은 값과 peek 값을 비교해서 같으면 count 증가
		ch = pop(&s);
		if (ch == peek(&s)) {
			cnt++;
		}
		else { // 값이 다르면 count와 문자 출력
			printf("%d%c", cnt, ch);
			cnt = 1;
		}
		n++;
	}

}

void palindrome(char str[]) { // 문자열 회문 검사
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

	for (int i = 0; i < idx; i++) { // str2배열에 들어있는 문자들과 스택에 쌓여있는 문자들 비교
		if (str2[i] == pop(&s)) {
			cnt++;
		}
		printf("%c ", str2[i]);
	}

	if (cnt == idx) { // count 값과 index값이 같으면 문자열 일치 
		printf("회문입니다\n");
	}
	else
		printf("회문이아닙니다.");
}

void result_stack(char str[]) { // 후위표기식 계산하는 함수
	StackType s;
	init_stack(&s);

	char ch;
	int len = strlen(str);
	int n1, n2, result;

	for (int i = 0; i < len; i++) {
		ch = str[i];

		//숫자문자면 숫자로 변환하여 스택에 저장
		if (ch != '+' && ch != '-' && ch != '/' && ch != '*' && ch != '^' && ch != '>' && ch != '<' && ch != '=' && ch != '&' && ch != '|') {
			result = ch - '0';
			push(&s, result);
		}
		else { // 숫자문자가 아닌 연산자일경우 연산 진행
			n2 = pop(&s);
			n1 = pop(&s);
			if (ch == '+') { // +연산
				push(&s, n1 + n2);
				printf("\n%d + %d 결과값: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '-') { // -연산
				push(&s, n1 - n2);
				printf("\n%d - %d 결과값: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '/') { // /연산
				push(&s, n1 / n2);
				printf("\n%d / %d 결과값: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '*') { // *연산
				push(&s, n1 * n2);
				printf("\n%d * %d 결과값: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '^') { // 거듭제곱 연산
				push(&s,pow(n1,n2));
				printf("\n%d ^ %d 결과값: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '>') { // 대소비교
				push(&s, n1 > n2);
				printf("\n%d > %d 결과값: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '<') { // 대소비교
				push(&s, n1 < n2);
				printf("\n%d < %d 결과값: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '=') { // 값이 같을경우
				push(&s, n1);
				printf("\n%d == %d 결과값: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '&') { // AND연산
				push(&s, n1 && n2);
				printf("\n%d && %d 결과값: %d\n",n1,n2, peek(&s));
			}
			else { // OR연산
				push(&s, n1 || n2);
				printf("\n%d || %d 결과값: %d\n",n1,n2, peek(&s));
			}
		}
	}
	printf("\n결과 값: %d\n", pop(&s));
}


int main(void) {
	int n;
	while (1) {
		printf("\n1~4번 중 선택하세요.(0을 누르면 종료): ");
		scanf("%d", &n);

		switch (n)
		{

		case 0: {
			printf("프로그램을 종료합니다\n");
			return 0;
		}

		case 1: {
			printf("\n괄호 매칭 번호 매기기\n");
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
			break;
		}

		case 2: {
			printf("\nrun-length 압축\n");
			char str[100];
			printf("문자열을 입력하시오: ");
			scanf("%s", str);
			runLength(str);
			break;
		}

		case 3: {
			printf("\npalindrome\n");
			char str[100];
			printf("문자열을 입력하시오: ");
			getchar();
			scanf("%[^\n]s", str);
			palindrome(str);
			break;
		}
		case 4: {
			printf("\n후위표기식계산\n");
			char str[100];
			printf("수식입력: ");
			scanf("%s", str);
			result_stack(str);
		}
		}
	}
	return 0;
}