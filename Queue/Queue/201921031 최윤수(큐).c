#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100
typedef int element;

typedef struct { // 원형 큐 타입
	element  data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message) // 오류 함수
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) // 큐 초기값 설정
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) // 큐 공백 상태 검사
{
	return (q->front == q->rear);
}

int is_full(QueueType* q) // 큐 포화 상태 검사
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void queue_print(QueueType* q) // 원형큐 출력 함수
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void enqueue(QueueType* q, element item) // 큐 삽입 함수
{
	if (is_full(q))
		error("Queue is full");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) // 큐 삭제 함수
{
	if (is_empty(q))
		error("Queue is empty");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element peek(QueueType* q) // 큐 삭제 함수
{
	if (is_empty(q))
		error("Queue is empty");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void) {
	QueueType man;
	init_queue(&man);

	QueueType woman;
	init_queue(&woman);

	int m = 0, w = 0, i = 0;
	int student, random;

	printf("학생의 수 : ");
	scanf("%d", &student);

	while (i++ < student) {
		random = (rand() % 100 + 1);
		printf("번호표: %d\n", random);
		if ((random % 2) == 1) {
			w++;
			enqueue(&woman, w);
			printf("여성%d 입장 - ", w);
		}
		else {
			m++;
			enqueue(&man, m);
			printf("남성%d 입장 - ", m);
		}
		if (!is_empty(&woman) && !is_empty(&man)) {
			printf("여성%d <--> 남성%d 매칭\n", dequeue(&woman), dequeue(&man));
		}
		else
			printf("대기\n");
		printf("현재 여성 큐 front : %d  |  rear : %d\n", woman.front, woman.rear);
		printf("현재 남성 큐 front : %d  |  rear : %d\n", man.front, man.rear);
		printf("======================================\n");
	}
	return 0;
}