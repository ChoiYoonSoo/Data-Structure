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

LinkNode* insert_node(LinkNode* head, char m[], char s[], char g, int y) { // 오름차순 노드 삽입
	LinkNode* node = head;
	LinkNode* nextnode = (LinkNode*)malloc(sizeof(LinkNode));

	strcpy(nextnode->data.music, m);
	strcpy(nextnode->data.singer, s);
	nextnode->data.genre = g;
	nextnode->data.year = y;

	if (head == NULL || strcmp(node->data.music, nextnode->data.music) >= 0) {
		// 빈 공간이거나 node의 음악이 nextnode의 음악보다 같거나 클경우 맨 앞으로 저장
		nextnode->link = head;
		head = nextnode;
		return head;
	}
	else { // 빈공간이 아니고 node의 음악이 nextnode의 음악보다 작을경우
		while (node != NULL) {
			if (strcmp(node->data.music, nextnode->data.music) < 0) {
				// node의 음악이 nextnode 음악보다 작을경우
				if (node->link == NULL || strcmp(node->link, nextnode->data.music) >= 0) {
					// node의 음악이 nextnode 음악보다 작고 node의 다음이 NULL이거나 node 다음의 음악이 nextnode 음악보다 클경우 그 전에 삽입
					nextnode->link = node->link;
					node->link = nextnode;
					return head;
				}
				node = node->link; // 아닐경우 node를 다음으로 이동시켜 만족할때까지 비교
			}
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

LinkNode* delete_node(LinkNode* head, char name[]) { // 음악 제목 삭제 함수
	LinkNode* removed;
	LinkNode* dnode = head;
	int n = 0;

	if (head == NULL) return NULL;
	if (strcmp(dnode->data.music, name) == 0) { // 헤드 노드 부분 삭제
		removed = head;
		head = removed->link;
		free(removed);
		printf("'%s'를 삭제하였습니다.\n", name);
		return head;
	}

	while (dnode->link != NULL) { // 중간 노드 부분 삭제
		if (strcmp(dnode->link, name) == 0) {
			removed = dnode->link;
			dnode->link = removed->link;
			free(removed);
			printf("'%s'를 삭제하였습니다.\n", name);
			n++;
			continue; // 같은 제목을 다 삭제하기위해
		}
		dnode = dnode->link;
	}
	if (n == 0) printf("\n같은 이름의 음악이 없습니다.\n");
	return head;
}

int main(void) {
	LinkNode* head = NULL;
	char m[10];
	char s[10];
	char g;
	int y, n;

	while (1) {
		printf("\n1. 입력 2. 노드 출력 3. 갯수 출력 4. 노드 삭제 5. 종료\n");
		scanf("%d", &n);

		switch (n) {
		case 1: {
			printf("음악제목, 가수, 장르, 발표년도 입력: ");
			scanf("%s %s %c %d", m, s, &g, &y);

			if (g != 'B' && g != 'C' && g != 'H' && g != 'J' && g != 'T') {
				printf("장르를 잘못 입력하였습니다.\n");
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
			char name[10];
			printf("삭제할 음악 제목을 입력하세요. : ");
			scanf("%s", name);

			head = delete_node(head, name);
			break;
		}
		case 5: {
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		}
	}
	return 0;
}