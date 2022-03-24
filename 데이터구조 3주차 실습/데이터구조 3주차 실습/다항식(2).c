#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 101
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	float coef; // 계수
	int expon; // 차수
} polynomial;

polynomial terms[MAX_TERMS] = { 0,{0,} };
int avail;

char compare(int a, int b)
{
	if (a > b) return '>'; // b항 차수보다 a항 차수가 클 경우 '>' 반환
	else if (a == b) return '='; // a항과 b항의 차수가 같을경우 '=' 반환
	else return '<'; // a항 차수보다 b항 차수가 클 경우 '<' 반환
}
//C항 넣는 함수
void attach(float coef, int expon)
{
	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].coef = coef; // A,B항의 저장된 공간 뒤부터 C항 저장
	terms[avail].expon = expon;
	avail++;
}
void poly_sub(int As, int Ae, int Bs, int Be, int* Cs,int* Ce)
{
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be)
		switch (compare(terms[As].expon, terms[Bs].expon)) {
		case '>': // A의 차수 > B의 차수
			attach(terms[As].coef, terms[As].expon);
			As++; break;
		case '=': // A의 차수 == B의 차수
			tempcoef = terms[As].coef - terms[Bs].coef;
			if (tempcoef)
				attach(tempcoef, terms[As].expon);
			As++; Bs++; break;
		case '<': // A의 차수 < B의 차수
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++; break;
		}
	// A의 나머지 항들을 이동함
	for (; As <= Ae; As++)
		attach(terms[As].coef, terms[As].expon);
	// B의 나머지 항들을 이동함
	for (; Bs <= Be; Bs++)
		attach(terms[Bs].coef, terms[Bs].expon);
	*Ce = avail - 1;
}

void print_poly(int s, int e) // 다항식 출력함수
{
	for (int i = s; i < e; i++) {
		if(terms[i].coef < 0)
			printf(" %3.1fx^%d ", terms[i].coef, terms[i].expon);
		else 
			printf(" + %3.1fx^%d ", terms[i].coef, terms[i].expon);
	}
	if(terms[e].coef < 0)
		printf(" %3.1fx^%d\n", terms[e].coef, terms[e].expon);
	else
		printf(" + %3.1fx^%d\n", terms[e].coef, terms[e].expon);
}
// a항의 계수와 차수, b항의 계수와 차수 입력
void input_poly(int Ae, int Be)
{
	for (int i = 0; i <= Ae; i++)
	{
		printf("A항의 계수와 차수 입력: ");
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
	}
	for (int i = Ae+1; i <= Be; i++)
	{
		printf("B항의 계수와 차수 입력: ");
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
	}

}
void poly_x(int s, int e) // X값 대입
{
	int x;
	float sum = 0;
	printf("x의 값 입력: ");
	scanf("%d", &x);
	for (int i = s; i <= e; i++) {
		sum += terms[i].coef * pow(x, terms[i].expon);
	}
	printf("A(%d) = %.1f\n", x, sum);
}
int main(void)
{
	int As = 0;
	int Ae, Bs, Be, Cs, Ce;
	printf("A항의 갯수 입력: ");
	scanf("%d", &Ae);
	printf("B항의 갯수 입력: ");
	scanf("%d", &Be);
	Ae = Ae - 1;
	Bs = Ae + 1;
	Be = Ae + Be;
	input_poly(Ae, Be);
	avail = Be + 1;
	poly_sub(As, Ae, Bs, Be, &Cs, &Ce);
	print_poly(As, Ae);
	print_poly(Bs, Be);
	printf("\n----------------------------------------------------------------------------- \n");
	print_poly(Cs, Ce);
	poly_x(Cs, Ce);
	return 0;
}