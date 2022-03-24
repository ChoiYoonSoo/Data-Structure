#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ((a)>(b))?(a):(b)
#define MAX_DEGREE 101
#include <stdio.h>
#include <math.h>

typedef struct
{
	int degree; // 차수
	float coef[MAX_DEGREE]; // 계수
}Polynomial;

Polynomial input_poly(Polynomial p) // A항, B항의 차수 계수 입력
{
	printf("항의 차수 입력: ");
	scanf("%d", &p.degree);
	for (int i = 0; i <= p.degree; i++) {
		printf("항의 계수 입력: ");
		scanf("%f", &p.coef[i]);
	}
	printf("\n");
	return p;
}
void print_poly(Polynomial p) // 입력받은 다항식 출력
{
	for (int i = p.degree; i > 0; i--) {
		if (p.coef[p.degree - i] != 0) {
			if (p.coef[p.degree - i] >= 0)
				printf(" + %3.1fx^%d", p.coef[p.degree - i], i);
			else
				printf(" %3.1fx^%d", p.coef[p.degree - i], i);
		}
	}
	if (p.coef[p.degree] != 0) {
		if (p.coef[p.degree] >= 0)
			printf(" + %3.1f\n", p.coef[p.degree]);
		else
			printf(" %3.1f\n", p.coef[p.degree]);
	}
}
void poly_x(Polynomial p) // x값 대입
{
	int x;
	float sum = 0;
	int degree = p.degree;
	printf("\nx의 값 입력 : ");
	scanf("%d", &x);


	for (int i = 0; i <= p.degree; i++)
	{
		sum += p.coef[i] * pow(x, degree--);
	}
	printf("A(%d) = %.1f\n", x, sum);
}
Polynomial poly_sub(Polynomial A, Polynomial B) // 두 다항식의 뺄셈
{
	Polynomial C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree);
	while (degree_a == degree_b) { // 두 다항식의 차수가 같을경우
		if (A.coef[Apos] == B.coef[Bpos]) { // 두 다항식의 계수가 같을경우 0이기 때문에 저장 x
			Apos++; Bpos++;
			degree_a--; degree_b--; // 차수 줄이기
			C.degree--; // C항의 차수 줄이기 (최고차항 계산값이 0이면 저장안하기때문)
		}
		else
			break;
	}
	while (Apos <= A.degree && Bpos <= B.degree) 
	{
		if (degree_a > degree_b) { // a항의 차수가 b항의 차수보다 클 경우 c항에 a값 대입
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) { // a항과 b항의 차수가 같을경우 뺀 값 c항에 저장
			C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else { // b항의 차수가 a항의 차수보다 클 경우 c항에 b값 대입
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}
int main(void)
{
	Polynomial a = { 0,{0,} };
	Polynomial b = { 0,{0,} };
	Polynomial c;
	a = input_poly(a);
	b = input_poly(b);
	c = poly_sub(a, b);
	print_poly(a);
	print_poly(b);
	printf("\n------------------------\n");
	print_poly(c);
	poly_x(c);
	return 0;

}