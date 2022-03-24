#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	double x;
	double y;
}number;

void strjud(char* str){
	int i=0;
	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
	int ncnt = 0;
	while (str[i] != '\0') {
		if (str[i] >= 65 && str[i] <= 90) { // 값이 영어 대문자인지 판별
			cnt1++;
		}
		else if (str[i] >= 97 && str[i] <= 122) { // 값이 영어 소문자인지 판별
			cnt2++;
		}
		else if (str[i] == '!' || str[i] == '?' || str[i] == '#' || str[i] == '*' || str[i] == '$') { // 값이 특수문자인지 판별
			cnt3++;
		}
		else if (str[i] >= 48 && str[i] <= 57) { // 값이 숫자 0~9사이인지 판별
			cnt4++;
		}
		else // 조건에 해당되지 않는경우
			ncnt++;
		i++;
	}

	if (cnt1 >= 1 && cnt2 >=1 && cnt3 >= 1 && cnt4 >= 1) { // 조건이 모두 충족되는경우
		printf("문자열에서 알파벳 대문자, 소문자, 숫자, 특수문자(!,?,*,#,$)가 모두 포함되어있습니다\n");
		if (1 <= ncnt) { // 조건이 모두 충족되지만 다른문자도 포함되있는 경우
			printf("해당하지 않는 문자도 포함되어있습니다.\n");
		}
	}
	if (cnt1 == 0) { // 대문자가 포함되어있지 않는 경우
		printf("대문자가 포함되어있지 않습니다\n");
	}
	if (cnt2 == 0) { // 소문자가 포함되어있지 않는 경우
		printf("소문자가 포함되어있지 않습니다\n");
	}
	if (cnt3 == 0) { // 특수문자가 포함되어있지 않는경우
		printf("특수문자(!,?,*,#,$)가 포함되어있지 않습니다\n");
	}
	if (cnt4 == 0) { // 숫자가 포함되어있지 않는 경우
		printf("숫자가 포함되어있지 않습니다\n");
	}
	if (i == ncnt) { // 조건이 충족되지 않는 경우
		printf("문자열에서 알파벳 대문자, 소문자, 숫자, 특수문자(!,?,*,#,$)가 모두 포함되어있지 않습니다\n");
	}

	if (i < 10) { // 문자열 길이 판별
		printf("문자열의 길이가 10이하입니다.\n");
	}
	else printf("문자열의 길이가 10이상입니다.\n");
}
void sum(number* ptr,int n,double resultx, double resulty) {
	if (n == 0) {
		printf("%.1f + %.1fi\n", resultx, resulty);
		return 0;
	}
	else {
		resultx +=(*ptr).x; // 실수부분의 합
		resulty +=(*ptr).y; // 허수부분의 합
		ptr++; // 다음번째 값으로 이동
		sum(ptr, n - 1, resultx, resulty);
	}
}
int length(char *str) {
	if (*str == '\0') return 0;
	else return 1 + length(str + 1);
}
int Binsearch(int * arr, int bottom, int top, int n,int idx) {
	int mid = (bottom + top) / 2;
	idx++;
	printf("%d번째 위치 arr[%d] 값 %d\n",idx, mid, arr[mid]);
	if (n == arr[mid]) {
		return printf("최종숫자의 위치: arr[%d] 값 : %d \n", mid, arr[mid]);
	}
	else if (n < arr[mid])
		return Binsearch(arr, bottom, mid, n,idx);
	else
		return Binsearch(arr, mid, top, n,idx);
}
int main(void)
{
	int n;
	while (1) {
		printf("\n1~4번중 선택하세요. (0번을 누르면 프로그램 종료!): ");
		scanf("%d", &n);

		switch (n) {
		case 0: { // 0번을 누르면 프로그램 종료
			printf("프로그램 종료!");
			return 0;
		}
		case 1: { // 1번을 누르면 1번 문제풀이
			char str[100];
			printf("\n길이 100이하 문자열 입력: ");
			scanf("%s", str);
			strjud(str);
			break;
		}
		case 2: { // 2번을 누르면 2번 문제풀이
			int n;
			double resultx = 0;
			double resulty = 0;
			printf("n을 입력하세요\n");
			scanf("%d", &n);
			number * ptr = (number*)malloc(sizeof(number) * n);
			for (int i = 0; i < n; i++) {
				printf("%d번째 복소수 입력: ",i+1);
				scanf("%lf %lf", &ptr[i].x, &ptr[i].y);
			}
			sum(ptr,n,resultx,resulty);
			free(ptr);
			break;
		}
		case 3: { // 3번을 누르면 3번 문제풀이
			char str[100];
			int len = 1;
			printf("길이 100이하 문자열 입력: ");
			scanf("%s", str);
			printf("입력받은 문자열의 길이 %d\n",length(str,len));
			break;
			
		}
		case 4: { // 4번을 누르면 4번 문제풀이
			int arr[10];
			int n;
			int temp = 0;
			int a = 0;
			int idx = 0;
			printf("10개의 숫자 입력: \n");
			for (int i = 0; i < 10; i++) {
				scanf("%d", &arr[i]);
			}

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10-1; j++) {
					if (arr[j] > arr[j + 1]) {
						temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
					}
				}
			}
			for (int i = 0; i < 10; i++) {
				printf("%d ", arr[i]);
			}
			int bottom = 0; // 배열의 첫번째 인덱스 저장
			int top = 10; // 배열의 마지막 인덱스 저장
			printf("\n찾고싶은 숫자 입력: ");
			scanf("%d", &n);
			for (int i = 0; i < 10; i++) { // 배열에 찾는 숫자가 있는지 판별
				if (n == arr[i])
					a += 1;
			}
			if (a >= 1)
				Binsearch(arr, bottom, top, n,idx);
			else
				printf("찾는숫자가 배열에 없습니다.\n");

			break;
		}
		}
	}
	return 0;
}