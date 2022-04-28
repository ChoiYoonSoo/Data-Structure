 #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5
typedef int element;

typedef struct
{
	element data[MAX_QUEUE_SIZE];
	int rear, front;
}QueueType;

void error(char* massage)
{
	fprintf(stderr, "%s\n", massage);
	exit(1);
}

void init_queue(QueueType* q)
{
	q->rear = q->front = 0;
}

int is_empty(QueueType* q)
{
	return q->front == q->rear;
}

int is_full(QueueType* q)
{
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void queue_print(QueueType* q)
{
	printf("QUE(front=%d rear=%d) = ", q->front, q->rear);
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

void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("Queue is full");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("Queue is empty");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element peek(QueueType* q)
{
	if (is_empty(q))
		error("Queue is empty");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void){
	QueueType queue;
	init_queue(&queue);

	int element;
	printf("--데이터 추가 단계--\n");
	while (!is_full(&queue)) {
		printf("정수를 입력하시오: ");
		scanf("%d", &element);
		enqueue(&queue, element);
		queue_print(&queue);
	}
	printf("\n\nQueue is full\n\n");

	printf("--데이터 삭제 단계--\n");
	while (!is_empty(&queue))
	{
		element = dequeue(&queue);
		printf("꺼내진 정수: %d \n", element);
		queue_print(&queue);
	}
	printf("\n\nQueue is empty\n");
	return 0;
}