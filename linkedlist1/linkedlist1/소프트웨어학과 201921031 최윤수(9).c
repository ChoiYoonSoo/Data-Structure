#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char music[10]; // 음악제목
	char singer[10]; // 가수
	char genre; // 장르
	int year; // 발표년도
}element;

typedef struct {
	element data;
	struct LinkNode* link;
}LinkNode;

void error(char* message) { // 에러 함수
	fprintf(stderr, "%s", message);
	exit(1);
}

LinkNode* insert_node(LinkNode* head, char m[],char s[], char g,int y) { // 오름차순 노드 삽입
	LinkNode* node = head;
	LinkNode* nextnode = (LinkNode*)malloc(sizeof(LinkNode));

	strcpy(nextnode->data.music, m);
	strcpy(nextnode->data.singer, s);
	nextnode->data.genre = g;
	nextnode->data.year = y;

	if (head == NULL || strcmp(node->data.music, nextnode->data.music) >= 0) {
		nextnode->link = head;
		head = nextnode;
		return head;
	}
	else {
		while (node != NULL){
			if (strcmp(node->data.music, nextnode->data.music) <= 0) {
				if (node->link == NULL || strcmp(node->data.music, nextnode->data.music) >= 0) {
					nextnode->link = node->link;
					node->link = nextnode;
					return head;
				}
			}
			node = node->link;
		}
	}
}

int list_length(LinkNode* head) { // 연결된 노드의 갯수 계산 함수
	int cnt = 0;
	while (head != NULL) {
		head = head->link;
		cnt++;
	}
	return cnt;
}

void list_display(LinkNode* head) { // 현재 리스트에 연결된 노드 데이터 출력

	LinkNode* p = head;

	while (p != NULL) {
		printf("%s %s %c %d -> ", p->data.music, p->data.singer, p->data.genre, p->data.year);
		p = p->link;
	}
	printf("NULL\n");
}

int main(void) {
    LinkNode* head = NULL;
    char m[10];
    char s[10];
    char g;
    int y,n;

	while (1) {
		printf("\n1. 입력 2. 노드 출력 3. 갯수 출력 4. 종료\n");
		scanf("%d", &n);

		switch (n) {
		case 1: {
			printf("음악제목, 가수, 장르, 발표년도 입력: ");
			scanf("%s %s %c %d", m, s, &g, &y);

			if (g != 'B' && g != 'C' && g != 'H' && g != 'J' && g != 'T') {
				printf("장르를 잘못 입력하였습니다.\n");
				break;
			}
			else {
				head = insert_node(head, m, s, g, y);
			}
			break;
		}
		case 2: {
			list_display(head);
			break;
		}
		case 3: {
			printf("노드의 갯수 : %d\n", list_length(head));
			break;
		}
		case 4: {
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		}
	}
	return 0;
}