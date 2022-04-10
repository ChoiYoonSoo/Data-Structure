#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 6
#define MAX_STACK_SIZE 100

typedef struct
{
	short r;
	short c;
}element;

typedef struct
{
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s)
{
	 s->top = -1;
}

int is_full(StackType* s)
{
	return s->top == (MAX_STACK_SIZE - 1);
}

int is_empty(StackType* s)
{
	return s->top == -1;
}

void push(StackType* s, element item)
{
	if (is_full(&s))
	{
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
	if (is_empty(&s))
	{
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s)
{
	if (is_empty(&s))
	{
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[s->top];
}


char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'},
};

element temp;
element rec[MAZE_SIZE * MAZE_SIZE];

void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		temp.r = r;
		temp.c = c;
		push(s, temp);
	}
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE],int n)
{
	printf("\n%d번째 미로의 움직임\n", n);
	printf("\n");
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
	init_stack(&s);
	element here = { 1,0 };
	int r, c;
	int idx = 0;
	int num = 1;

	while (maze[here.r][here.c] != 'x')
	{
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		maze_print(maze,num);
		num++;
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);

		if (is_empty(&s))
		{
			printf("실패\n");
			return;
		}
		else {
			here = pop(&s);
			rec[idx++] = here;
		}
	}
	printf("\n탈출성공\n\n");

	for (int i = 0; i < idx; i++) {
		printf("%d번째 미로의 경로: %d %d\n", i + 1, rec[i].r, rec[i].c);
	}
	return 0;
}
