#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 10
#define MAX_STACK_SIZE 100

typedef struct // 행 열 생성
{
	short r;
	short c;
}element;

typedef struct // 스택타입
{
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) // 스택생성
{
	s->top = -1;
}

int is_full(StackType* s) // 스택 포화상태 검사
{
	return s->top == (MAX_STACK_SIZE - 1);
}

int is_empty(StackType* s) // 스택 공백상태 검사
{
	return s->top == -1;
}

void push(StackType* s, element item) // 스택 삽입 함수
{
	if (is_full(&s))
	{
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s) // 스택 삭제 함수
{
	if (is_empty(&s))
	{
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) // 스택 상단요소 반환
{
	if (is_empty(&s))
	{
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[s->top];
}


char maze[MAZE_SIZE][MAZE_SIZE] = { // 미로배열 생성
	{'0','0','0','0','0','0','1','1','1','1'},
	{'e','0','0','0','0','1','1','1','1','1'},
	{'0','1','0','1','0','0','0','0','1','1'},
	{'0','0','0','0','1','1','1','0','0','1'},
	{'1','1','1','0','0','0','0','1','0','0'},
	{'1','1','1','1','1','1','0','0','1','0'},
	{'1','1','1','1','1','1','1','0','1','0'},
	{'1','1','1','1','1','1','1','0','0','x'},
	{'1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1'},
};

void push_loc(StackType* s, int r, int c) // 미로가 '1'이거나 '.'이 아닐경우 push
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		element temp;
		temp.r = r;
		temp.c = c;
		push(s, temp);
	}
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) // 미로 출력 함수
{
	for (int r = 0; r < MAZE_SIZE; r++)
	{
		for (int c = 0; c < MAZE_SIZE; c++)
		{
			printf("%c", maze[r][c]);
		}printf("\n");
	}
}

int main(void)
{
	StackType s;
	while (1) {
		init_stack(&s);

		element here = { 1,0 };
		element rec[MAZE_SIZE * MAZE_SIZE];

		int r, c;
		int num = 2;
		int idx = 0;
		rec[idx++] = here;

		printf("\n\n1번째 미로의 이동경로 -> (%d, %d)\n\n", here.r, here.c);
		while (maze[here.r][here.c] != 'x')
		{
			r = here.r;
			c = here.c;
			maze[r][c] = '.';
			maze_print(maze);
			push_loc(&s, r - 1, c);
			push_loc(&s, r + 1, c);
			push_loc(&s, r, c - 1);
			push_loc(&s, r, c + 1);
			if (is_empty(&s))
			{
				printf("\n다른 이동경로가 없습니다.\n");
				return 0;
			}
			else {
				here = pop(&s);
				rec[idx++] = here;
				printf("\n%d번째 미로의 현재경로 -> (%d, %d)\n\n", num++, here.r, here.c);
			}
		}

		printf("\n탈출성공\n\n");
		printf("\n========== 미로의 총 이동경로 ==========\n\n");
		for (int i = 0; i < idx; i++) {
			printf("(%d, %d) -> ", rec[i].r, rec[i].c);
		}
		printf("도착");
	}
	return 0;
}
