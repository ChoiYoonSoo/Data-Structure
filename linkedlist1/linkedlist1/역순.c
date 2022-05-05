#define _CRT_NO_WARININGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
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

LinkNode* reverse(LinkNode* head) {
	LinkNode* p, * q, * r;

	p = head;
	q = NULL;
	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

int main(void) {
	LinkNode* head1 = NULL;
	LinkNode* head2 = NULL;

	head1 = insert_first(head1, 10);
	head1 = insert_first(head1, 20);
	head1 = insert_first(head1, 30);
	print_list(head1);

	head2 = reverse(head1);
	print_list(head2);
	return 0;
}