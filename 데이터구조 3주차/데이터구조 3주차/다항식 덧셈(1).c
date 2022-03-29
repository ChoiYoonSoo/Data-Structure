#define _CRT_SECURE_NO_WARNINGS
#define SIZE 100
#define MAX(a,b) ((a)>(b))?(a):(b)
#include <stdio.h>
#include <math.h>
typedef struct
{
	int degree;
	float coef[SIZE];
}Polynomial;

Polynomial Input_poly(Polynomial p)
{
	printf("항의 차수를 입력하세요 : ");
	scanf("%d", &p.degree);
	for (int i = 0; i <= p.degree; i++)
	{
		printf("항의 계수를 입력하세요 : ");
		scanf("%f", &p.coef[i]);
	}
	return p;
}

void Print_poly(Polynomial p)
{
	for (int i = p.degree; i > 0; i--)
	{
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
	}
	printf("%3.1f\n", p.coef[p.degree]);
}

Polynomial Poly_add1(Polynomial a, Polynomial b)
{
	Polynomial C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int  A_degree = a.degree;
	int B_degree = b.degree;
	C.degree = MAX(a.degree, b.degree);

	while (Apos <= a.degree && Bpos <= b.degree)
	{
		if (A_degree > B_degree)
		{
			C.coef[Cpos++] = a.coef[Apos++];
			A_degree--;
		}
		else if (A_degree == B_degree)
		{
			C.coef[Cpos++] = a.coef[Apos++] * b.coef[Bpos++];
			A_degree--; B_degree--;
		}
		else
		{
			C.coef[Cpos++] = b.coef[Bpos++];
			B_degree--;
		}
	}
	return C;

}
void Xpoly(Polynomial p)
{
	int x;
	float sum = 0;;
	printf("대입할 x값 입력: ");
	scanf("%d", &x);
	int  D_gree = p.degree;

	for (int i = 0; i <= p.degree; i++)
	{
		sum += p.coef[i] * pow(x, D_gree--);
	}
	
	
	printf("A(x) : %f", sum);

}
int main(void)
{
	Polynomial A = { 0,{0,} };
	Polynomial B = { 0,{0,} };
	Polynomial C;
	A = Input_poly(A);
	B = Input_poly(B);
	C = Poly_add1(A, B);
	Print_poly(A);
	Print_poly(B);
	printf("\n-----------------\n");
	Print_poly(C);
	Xpoly(C);
	return 0;
}