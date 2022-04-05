//전치행렬(2)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 100

typedef struct
{
	int row; //행
	int col; //열
	int value; //값
}element;

typedef struct
{
	element data[SIZE]; //항을 저장할 배열
	int rows; //행의 갯수
	int cols; //열의 갯수
	int terms; //항의 갯수
}SparseMatrix;

SparseMatrix input_Matrix(SparseMatrix a) // 행렬 입력
{
	printf("행의 갯수 입력: ");
	scanf("%d", &a.rows);
	printf("열의 갯수 입력: ");
	scanf("%d", &a.cols);
	printf("항의 갯수 입력: ");
	scanf("%d", &a.terms);

	for (int i = 0; i < a.terms; i++) {
		printf("%d번 행 열 값 입력 :",i+1);
		scanf("%d %d %d", &a.data[i].row, &a.data[i].col, &a.data[i].value);
	}

	return a;
}

SparseMatrix matrix_transpose2(SparseMatrix p) // 전치행렬
{
	SparseMatrix b;

	int bidx;
	b.rows = p.cols;
	b.cols = p.rows;
	b.terms = p.terms;

	if (p.terms > 0) {

		bidx = 0;
		for (int c = 0; c < p.cols; c++) {
			for (int i = 0; i < p.terms; i++) {
				if (p.data[i].col == c) {

					b.data[bidx].row = p.data[i].col;
					b.data[bidx].col = p.data[i].row;
					b.data[bidx].value = p.data[i].value;
					bidx++;
				}
			}
		}
	}
	return b;

}
void print_matrix(SparseMatrix p)
{
	printf("\n=======================\n");
	for (int i = 0; i < p.terms; i++)
		printf("(%d, %d, %d)\n", p.data[i].row, p.data[i].col, p.data[i].value);
	printf("\n=======================\n");
}
int main(void)
{	
	SparseMatrix a={0,};
	SparseMatrix b={0,};

	a = input_Matrix(a);
	print_matrix(a);
	b = matrix_transpose2(a);
	print_matrix(b);
	return 0;
}