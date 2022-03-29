#define _CRT_SECURE_NO_WARNINGS
#define ROWS 3
#define COLS 3
#include <stdio.h>
int swaparr(int arr1[][COLS], int arr2[][COLS])
{
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			arr2[j][i] = arr1[i][j];
		}
	}
}
void printarr(int a[][COLS])
{
	printf("\n ---------- \n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("%3d ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n ---------- \n");
}
int main(void)
{
	int arr1[ROWS][COLS] = { {1,2,3},
		                     {4,5,6},
	                      	 {7,8,9} };
	int arr2[ROWS][COLS] = { {0,}, };

	printarr(arr1);
	swaparr(arr1, arr2);
	printarr(arr2);
	return 0;
}