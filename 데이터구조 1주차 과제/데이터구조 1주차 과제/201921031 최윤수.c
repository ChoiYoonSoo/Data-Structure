#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int convert(char str[]) {
	int n=0;
	int len = strlen(str);
	if (str[0] == '-') {
		for (int i = 1; i < len; i++)
			n += (str[i] - '0') * pow(10, len - i - 1);
		n *= -1;
	}
	else {
		for (int i = 0; i < len; i++)
			n += (str[i] - '0') * pow(10, len - i - 1);
	}
	return n;
}

typedef struct {
	int xpos;
	int ypos;
}Point;

int distance(Point* po) {
	int idx;
	double arr[5];
	for (int i = 0; i < 5; i++) {
		arr[i] = sqrt((double)(po[i].xpos * po[i].xpos) + (po[i].ypos * po[i].ypos));
	}

	double max = arr[0];
	for (int i = 1; i < 5; i++) {
		if (max < arr[i]) {
			max = arr[i];
			idx = i;
		}
	}
	return idx;
}

int Birth_date(char **birth) {
	int month[10];
	int m, i;
	int sameday = 0, person = 0;

	for (int i = 0; i < 10; i++) {
		month[i] = atoi(birth[i]); 
	}
	printf("\n몇 월?: ");
	scanf("%d", &m);

	for (int i = 0; i < 10; i++) {
		sameday = (month[i] / 100) % 100;
		if (sameday == m)
			person += 1;
	}
	return person;
}
int repeat(int m, int n) {
	int sum = 0;
	for (int i = m; i <= n; i++) {
		sum += i;
	}
	return sum;
}

int rotation(int m, int n) {
	if (m > n) return 0;
	else return m + rotation(m + 1, n);
}

int main(void) {
	int n;
	while (1) {    // 무한루프
		printf("\n1~4번 중 선택하세요.(0번을 누르면 프로그램을 종료합니다)\n");
		scanf("%d", &n);   // n의값 입력
		switch(n) {   //switch문 시작

		case 0: {   // n == 0이면 아래문장 실행
			printf("\n프로그램 종료!\n");
			return 0;
		}
		case 1: {   // n == 1이면 아래문장 실행
			 char str[10];
			  printf("숫자 입력: ");
			  scanf("%s", str);
			  printf("변환시킨 숫자: %d\n",convert(str));
			  break;
		  }
		case 2: {   // n == 2이면 아래문장 실행
			Point po[5];
			for (int i = 0; i < 5; i++) {
				printf("%d번째 x좌표 y좌표 입력: ", i + 1);
				scanf("%d %d", &po[i].xpos, &po[i].ypos);
			}
			int idx = distance(&po);
			printf("\n원점에서부터 가장 먼 좌표: %d %d\n", po[idx].xpos, po[idx].ypos);
			break;
		}
		case 3: {    // n == 3이면 아래문장 실행
			char* birth[10]= { "20000901", "20100900", "20100304", "19970519", "20030814",
				"19801102", "20181204", "20170607", "20000504", "20180402" };
			printf("같은 월 생의 수: %d\n", Birth_date(&birth));
			break;
		}
		case 4: {    // n == 4이면 아래문장 실행
			int m, n;
			printf("m입력: ");
			scanf("%d", &m);
			printf("n입력 (m보다 커야함): ");
			scanf("%d", &n);
			if (m > n) {
				printf("m보다 n의 값이 더 커야합니다.");
				break;
			}
			printf("반복함수 m부터 n까지의 합: %d \n순환함수 m부터 n까지의 합: %d\n", repeat(m, n), rotation(m, n));
			break;
		}
		}
	}
	return 0;
}