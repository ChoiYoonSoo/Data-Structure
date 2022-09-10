#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	int n[2];
	int num = 0;
	int sum = 0;
	int result = 0;
	int cnt = 0;

	scanf("%d", &num);
	n[0] = num / 10;
	n[1] = num - (num / 10) * 10;
	
	if (num >= 0 && num <= 99) {
			while (1) {
				sum = n[0] + n[1];

				if (sum > 9) {
					sum = sum % 10;
				}

				result = (n[1] * 10) + sum;
				n[0] = n[1];
				n[1] = sum;
				cnt++;

				if (result == num)
					break;
			}
	}

	printf("%d", cnt);
	return 0;
}