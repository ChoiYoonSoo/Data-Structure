#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	int n;
	int j = 0;
	char str[4] = "GDSC";

	scanf("%d", &n);

	if (n <= 10000) {
		for (int i = 0; i < n; i++) {
			printf("%c", str[j]);
			if (str[j] == 'C') {
				j = 0;
				continue;
			}
			j++;
		}
	}
	else {
		printf("n ���� �ʰ�");
	}

	return 0;
}