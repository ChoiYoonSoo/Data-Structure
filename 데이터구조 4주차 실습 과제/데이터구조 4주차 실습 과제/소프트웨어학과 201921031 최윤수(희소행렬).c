#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 100
#include <stdio.h>

typedef struct {
	int row; // 행 위치
	int col; // 열 위치
	int value; // 값
}element;

typedef struct {
	element data[MAX_TERMS];
	int rows; // 행 개수
	int cols; // 열 개수
	int terms; // 항 개수
}SparseMatrix;

SparseMatrix save_matrix(int r, int c, int A[][10]) { // 희소행렬을 SparseMatrix 구조로 저장하는 함수

	SparseMatrix a;
	int idx = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (A[i][j] != 0) {
				a.data[idx].row = i;
				a.data[idx].col = j;
				a.data[idx++].value = A[i][j];
			}
		}
	}
	a.rows = r;
	a.cols = c;
	a.terms = idx;
	return a;
}

SparseMatrix add_matrix(SparseMatrix a, SparseMatrix b) { // 두 개의 SparseMatrix 덧셈하는 함수
	
	SparseMatrix c;
	int aindex = 0, bindex = 0, cindex = 0;

	if (a.rows != b.rows || a.cols != b.cols) { // 두 행렬의 행과 열이 다르면 덧셈 불가능
		printf("두 행렬의 연산이 불가능합니다.\n");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;

	while ((aindex < a.terms) && (bindex < b.terms)) {
		int anum = a.data[aindex].row * a.cols + a.data[aindex].col; // A위치
		int bnum = b.data[bindex].row * b.cols + b.data[bindex].col; // B위치

		if (anum < bnum) { // A위치보다 B위치가 더 크면 실행
			c.data[cindex++] = a.data[aindex++];
		}
		else if (anum == bnum) { // A위치와 B위치가 같을 경우 덧셈연산 실행
			if (a.data[aindex].value + b.data[bindex].value != 0) { // A+B 값이 0이 아니면 실행
				c.data[cindex].row = a.data[aindex].row;
				c.data[cindex].col = a.data[aindex].col;
				c.data[cindex++].value = a.data[aindex++].value + b.data[bindex++].value;
			}
			else {
				aindex++; bindex++;
			}
		}
		else { // A위치보다 B위치가 더 크면 실행
			c.data[cindex++] = b.data[bindex++];
		}
	}
	for (; aindex < a.terms;) // A행의 나머지 부분 실행
		c.data[cindex++] = a.data[aindex++];

	for (; bindex < b.terms;) // B행의 나머지 부분 실행
		c.data[cindex++] = b.data[bindex++];

	c.terms = cindex;
	return c;
}

void print1_matrix(SparseMatrix a) { // 0을 포함한 이차원 행렬 출력하는 함수
	
	int idx = 0;
	int n = 0;
	printf("0을 포함한 이차원 행렬 출력\n\n");

	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (a.data[idx].row == i) {
				if (a.data[idx].col == j)
					printf("%3d", a.data[idx++].value);
				else
					printf("%3d",n);
			}
			else
				printf("%3d",n);
		}
		printf("\n");
	}
	printf("\n");
}

void print2_matrix(SparseMatrix a) { // 0을 포함하지 않은 이차원 행렬 출력하는 함수
	
	int idx = 0;
	printf("0을 포함하지 않은 이차원 행렬 출력\n\n");

	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (a.data[idx].row == i) {
				if (a.data[idx].col == j) {
					printf("row: %d  col: %d  value: %d\n", a.data[idx].row, a.data[idx].col, a.data[idx].value);
					idx++;
				}
			}
		}
	}
	printf("\n");
}

int main(void) {

	int a[8][10] = { { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0,-3, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0,-1, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

	int b[8][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0,-1, 0, 0, 0, 0, 0, 0 },
				     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 } };

	int c[8][10] = { { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
				   	 { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 4, 0, 0, 0 } };

	int n;
	int rr = 8, cc = 10;
	SparseMatrix SA, SB, SC, result;

	SA = save_matrix(rr, cc, a);
	SB = save_matrix(rr, cc, b);
	SC = save_matrix(rr, cc, c);

	while (1) {
		printf("0~3번 중 선택하세요.\n");
		printf("0. 프로그램 종료\n1. 0을 포함한 이차원 행렬 출력\n2. 0을 포함하지 않은 이차원 행렬 출력\n3. 두 항의 덧셈결과 출력\n");
		scanf("%d", &n);
		switch (n) {
		case 0: { // 프로그램 종료
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		case 1: { // 0을 포함한 이차원 행렬 출력하는 함수 실행
			printf("A항 "); print1_matrix(SA);
			printf("B항 "); print1_matrix(SB);
			printf("C항 "); print1_matrix(SC);
			break;
		}
		case 2: { // 0을 포함하지 않은 이차원 행렬 출력하는 함수 실행
			printf("A항 "); print2_matrix(SA);
			printf("B항 "); print2_matrix(SB);
			printf("C항 "); print2_matrix(SC);
			break;
		}
		case 3: { // 두 항의 덧셈 결과를 저장한 행렬 출력하는 함수 실행
			result = add_matrix(SA, SB);
			printf("A+B항 "); print1_matrix(result);
			result = add_matrix(SA, SC);
			printf("A+C항 "); print1_matrix(result);
			result = add_matrix(SB, SC);
			printf("B+C항 "); print1_matrix(result);
			break;
		}
		}
	}
	
	return 0;
}