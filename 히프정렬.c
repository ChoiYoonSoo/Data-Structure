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

// ���� �Լ�
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

// �ʱ�ȭ �Լ�
void init(HeapType* h) {
	h->heap_size = 0;
}

// ���� ����� ���� heap_size�� ���� h�� item�� ����
// ���� �Լ�
void insert_heap(HeapType* h, element item) { // ���� �Լ�
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key)) { // Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
}

// ���� �Լ�
element delete_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ū �ڽĳ�带 ã�´�.
		if (child < h->heap_size && (h->heap[child].key < h->heap[child + 1].key))
			child++;
		if (temp.key >= h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
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