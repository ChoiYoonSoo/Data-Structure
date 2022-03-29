#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int fact(int n)
{
	if (n <= 1) return 1;
	else return n* fact(n - 1);
}
int main(void)
{
	int n;
	printf("정수 입력: ");
	scanf("%d", &n);
	printf("n! : %d\n",fact(n));
	return 0;
}