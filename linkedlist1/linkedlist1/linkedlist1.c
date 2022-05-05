#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

void error(char* message) {
	fprintf(stderr, "%s", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, element value) {
	ListNode* p;
	p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert(ListNode* head, element value, ListNode* pre) {
	ListNode* p;
	p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre;
	pre = removed->link;
	free(removed);
	return head;
}

void print_Node(ListNode* head) {

	for (ListNode* p = head; p != NULL; p = p->link) {
		printf("%d -> ",p->data);
	}
	printf("NULL\n");
}

element get_entry(ListNode* head, int index) { // index 번째의 데이터 찾기
	ListNode* p;
	p = (ListNode*)malloc(sizeof(ListNode));
	for (int i = 0; i <= index; i++) {
		p = head->data;
		head = head->link;
	}
	return p;
}

int get_length(ListNode* head) { // 노드의 갯수
	int n = 0;
	while (head != NULL) {
		head = head->link;
		n++;
	}
	return n;
}
ListNode* sort(ListNode* head) {
	ListNode* p = head;
	while (p != NULL) {
		if (p->data < head->data) {
			p->link = head->link;
		}
		else {
			p->link = head;
		}
	}
	return p;
}

int main(void) {
	ListNode* head = NULL;
	ListNode* p = NULL;

	for (int i = 0; i < 5; i++) {
		head = insert_first(head, i);
		print_Node(head);
	}

	/*for (int i = 0; i < 5; i++) {
		head = delete_first(head, i);
		print_Node(head);
	}*/
	printf("\n찾고자하는 인덱스 데이터 : %d\n", get_entry(head, 2));
	printf("노드의 갯수: %d\n", get_length(head));

	for (int i = 0; i < 5; i++) {
		p = sort(head);
		print_Node(p);
	}
	return 0;
}