#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct {
	element data;
	struct LinkNode* link;
}LinkNode;

LinkNode* insert_first(LinkNode* head, element value) {
	LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

void print_list(LinkNode* head) {
	for (LinkNode* p = head; p != NULL; p = p->link) {
		printf("%d -> ", p->data);
	}printf("NULL\n");
}

LinkNode* search_list(LinkNode* head, element x) {
	
	if (head != NULL) {
		if (head->data == x)
			return head;
		else {
			head = head->link;
			search_list(head, x);
		}
	}
	return NULL;
}

int main(void) {
	LinkNode* head = NULL;

	head = insert_first(head, 10);
	print_list(head);

	head = insert_first(head, 20);
	print_list(head);

	head = insert_first(head, 30);
	print_list(head);

	if (search_list(head, 20) != NULL) {
		printf("성공");
	}
	else
		printf("실패");
	return 0;
}