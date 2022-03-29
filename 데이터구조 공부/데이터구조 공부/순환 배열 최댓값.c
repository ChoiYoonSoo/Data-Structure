#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int max(int* arr,int n,int maxn)
{
	if (n < 0) return maxn;
	else if (maxn < *arr) {
		maxn = *arr;
	}
	arr++;
	max(arr, n - 1,maxn);
}

int main(void)
{	
	int arr[5];
	int n=5;
	for (int i = 0; i < 5; i++) {
		printf("%d번째 정수 입력: ", i + 1);
		scanf("%d", &arr[i]);
	}
	int maxn = arr[0];
	printf("배열 중 최댓값: %d",max(arr, n,maxn));
	return 0;
}