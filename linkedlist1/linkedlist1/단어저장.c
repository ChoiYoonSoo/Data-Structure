#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[100];
}element;

typedef struct {
	element data;
	struct LinkNode* link;
}LinkNode;

void error(char* message) {
	fprintf(stderr, "%s", message);
	exit(1);
}

void print_list(LinkNode* head) {

	for (LinkNode* p = head; p != NULL; p = p->link) {
		printf("%s -> ",p->data.name);
	}
	printf("NULL\n");
}

LinkNode* insert_first(LinkNode* head, element value) {
	LinkNode* p;
	p = (LinkNode*)malloc(sizeof(LinkNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

int main(void) {
	LinkNode* head = NULL;
	element data;

	strcpy(data.name, "Apple");
	head = insert_first(head, data);
	print_list(head);

	strcpy(data.name, "Banana");
	head = insert_first(head, data);
	print_list(head);

	strcpy(data.name, "Kiwi");
	head = insert_first(head, data);
	print_list(head);
	return 0;
}
