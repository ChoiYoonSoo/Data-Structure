#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void sub(int n)
{
	int p = 0;
	int pp = 1;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum = p + pp;
		p = pp;
		pp = sum;
		
	}
	printf("%d", sum);
}
int main(void)
{
	int n;
	printf("숫자 입력: ");
	scanf("%d", &n);
	sub(n);
	return 0;
}