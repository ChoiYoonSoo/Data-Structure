#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct {
	element data;
	struct LinkNode* link;
}LinkNode;

void error(char* message) {
	fprintf(stderr, "%s", message);
	exit(1);
}

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

LinkNode* concat_list(LinkNode* head1, LinkNode* head2) {
	if (head1 == NULL) {
		return head2;
		if (head2 == NULL) {
			return NULL;
		}
	}
	else if (head2 == NULL) return head1;
	else {
		LinkNode* p;
		p = head1;
		while(p->link != NULL) {
			p = p->link;
		}
		p->link = head2;
		return head1;
	}
}

int main(void) {
	LinkNode* head1 = NULL;
	LinkNode* head2 = NULL;

	head1 = insert_first(head1, 10);
	head1 = insert_first(head1, 20);
	head1 = insert_first(head1, 30);
	print_list(head1);

	head2 = insert_first(head2, 40);
	head2 = insert_first(head2, 50);
	print_list(head2);
	LinkNode* result = concat_list(head1, head2);
	print_list(result);
	return 0;
}