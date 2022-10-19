#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct {
	int key;
}element;

typedef struct HeapType {
	element heap[SIZE];
	int heap_size;
}HeapType;

// 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

// 초기화 함수
void init(HeapType* h) {
	h->heap_size = 0;
}

// 현재 요소의 개숙 heap_size인 히프 h에 item을 삽입
// 삽입 함수
void insert_heap(HeapType* h, element item) { // 삽입 함수
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key)) { // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
}

// 삭제 함수
element delete_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 큰 자식노드를 찾는다.
		if (child < h->heap_size && (h->heap[child].key < h->heap[child + 1].key))
			child++;
		if (temp.key >= h->heap[child].key) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void sort(element a[], int size) {
	HeapType* h;
	int i;

	h = create();
	init(h);

	for (int i = 0; i < size; i++) {
		insert_heap(h, a[i]);
	}

	for (int i = size - 1; i >= 0; i--) {
		a[i] = delete_heap(h);
	}

	
}

#define ARRSIZE 8
int main(void) {
	element arr[ARRSIZE] = { 10,4,30,6,70,40,25,6 };
	sort(arr, ARRSIZE);

	for (int i = 0; i < ARRSIZE; i++) {
		printf("< %d > ", arr[i].key);
	}
	return 0;
}