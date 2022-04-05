// 전치행렬(1)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ROWS 3
#define COLS 3

void matrix_transpose1(int matrix[ROWS][COLS], int matrix_t[ROWS][COLS]) // 전치행렬
{
	printf("\n===========전치행렬============\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++)
			matrix_t[j][i] = matrix[i][j];
	}
}

int input_matrix(int matrix[ROWS][COLS]) // 행렬입력
{
	printf("행렬 입력:\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("%d %d 위치 값 입력",i,j);
			scanf("%d", &matrix[i][j]);
		}
	}
	return **matrix;
}

void print_matrix(int matrix[ROWS][COLS]) // 행렬출력
{
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("[%d] ",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void add_matrix(int A[ROWS][COLS], int B[ROWS][COLS],int C[ROWS][COLS]) // 행렬 덧셈
{
	printf("\n==========행렬 덧셈==============\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	
}
void multi_matrix(int A[ROWS][COLS], int B[ROWS][COLS], int C[ROWS][COLS]) // 행렬 곱셈 (첫 번째 행렬 열과 두 번째 행렬 행이 같을경우에만 가능)
{
	printf("\n============행렬 곱셈============\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			for (int c = 0; c < 3; c++) {
				C[i][j] += A[i][c] * B[c][j];
			}
		}
	}

}
int main(void)
{
	int matrix[ROWS][COLS]={0,};
	int matrix_t[ROWS][COLS]={0,};
	int matrix_Add[ROWS][COLS] = {0,};
	int matrix_multi[ROWS][COLS] = { 0, };

	matrix[ROWS][COLS] = input_matrix(&matrix);
	matrix_transpose1(&matrix,&matrix_t);
	print_matrix(&matrix);
	print_matrix(&matrix_t);

	add_matrix(&matrix, &matrix_t,&matrix_Add);
	print_matrix(&matrix_Add);

	multi_matrix(&matrix, &matrix_t, &matrix_multi);
	print_matrix(&matrix_multi);
	return 0;
}