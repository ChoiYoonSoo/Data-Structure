#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 10

typedef struct {
	int front, rear;
	int data[MAX_QUEUE_SIZE];
} QueueType;

//오류함수
void error(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//초기화 함수
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// 큐 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->rear == q->front);
}

// 큐 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

// 큐 출력 함수
void print_queue(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

// 큐 삽입 함수
void enqueue(QueueType* q, int item)
{
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 큐 삭제 함수
int dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int peek(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	return q->data[(q->front + 1)] % MAX_QUEUE_SIZE;
}

int fibonachi(QueueType* q, int num) {
	if (num == 0) return 0;
	else if (num == 1) return 1;

	for (int i = 2; i <= num; i++) {
		enqueue(q, dequeue(q) + q->data[q->rear]);
	}
	return q->data[q->rear];
}

int main(void) {
	QueueType q;
	init_queue(&q);
	enqueue(&q, 0);
	enqueue(&q, 1);
	int num;
	printf("계산할 숫자를 입럭하시오: ");
	scanf_s("%d", &num);
	printf("%d", fibonachi(&q, num));
	return 0;
}