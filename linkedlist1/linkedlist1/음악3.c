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

typedef struct DLinkNode{ // 이중 연결 노드 타입
	element data;
	struct DLinkNode* llink;
	struct DLinkNode* rlink;
}DLinkNode;

void error(char* message) { // 에러 함수
	fprintf(stderr, "%s", message);
	exit(1);
}

void init(DLinkNode* phead) { // 이중 연결 리스트 초기화
	phead->llink = phead;
	phead->rlink = phead;
}

void dinsert_node(DLinkNode* phead, char m[], char s[], char g, int y) { // 오름차순 노드 삽입
	DLinkNode* node = phead->rlink;
	DLinkNode* nextnode = (DLinkNode*)malloc(sizeof(DLinkNode));

	strcpy(nextnode->data.music, m);
	strcpy(nextnode->data.singer, s);
	nextnode->data.genre = g;
	nextnode->data.year = y;

	if (phead->rlink == phead || strcmp(node->data.music, nextnode->data.music) >= 0) {
		// 데이터가 아무것도 없거나 node의 음악이 nextnode의 음악보다 같거나 클경우 맨 앞으로 저장
		nextnode->llink = phead;
		nextnode->rlink = phead->rlink;
		phead->rlink->llink = nextnode;
		phead->rlink = nextnode;
	}
	else { // 데이터가 있고 node의 음악이 nextnode의 음악보다 작을경우
		while (node != phead) {
			if (strcmp(node->data.music, nextnode->data.music) < 0) {
				// node의 음악이 nextnode 음악보다 작을경우
				if (node->rlink == phead || strcmp(node->rlink->data.music, nextnode->data.music) >= 0) {
					// node의 다음 링크의 값이 처음이거나 node 다음의 음악이 nextnode 음악보다 클경우 그 전에 삽입
					nextnode->rlink = node->rlink;
					nextnode->llink = node;
					node->rlink->llink = nextnode;
					node->rlink = nextnode;
					return;
				}
				node = node->rlink; // 아닐경우 node를 다음으로 이동시켜 만족할때까지 비교
			}
		}
	}
}

int dlist_length(DLinkNode* phead) { // 연결된 노드의 갯수 계산 함수
	int cnt = 0;
	DLinkNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		cnt++;
	}
	return cnt;
}

/*int dlist_length2(DLinkNode* phead) { // 연결된 노드의 갯수 순환호출 계산
	phead = phead->rlink;
	if (phead->rlink == phead) return 0;
	else return 1 + dlist_length2(phead);
}*/

void dlist_display(DLinkNode* phead) { // 현재 리스트에 연결된 노드 데이터 출력

	DLinkNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<- %s %s %c %d -> ", p->data.music, p->data.singer, p->data.genre, p->data.year);
	}
	printf("\n");
}

/*void dlist_display2(DLinkNode* phead) { // 순환호출을 이용하여 노드 데이터 출력
	DLinkNode* p = phead->rlink;
	if (p != phead) {
		printf("<- %s %s %c %d -> ", p->data.music, p->data.singer, p->data.genre, p->data.year);
		return dlist_display2(phead->rlink);
	}
	printf("\n");
}

void dlist_display3(DLinkNode* phead) { // 순환호출을 이용하여 노드 데이터 역순으로 출력
	if (phead->rlink != phead) {
		dlist_display3(phead->rlink);
		printf("%s %s %c %d -> ", phead->data.music, phead->data.singer, phead->data.genre, phead->data.year);
	}
}*/

void delete_node(DLinkNode* phead, char name[]) { // 음악 제목 삭제 함수
	DLinkNode* removed = phead->rlink;
	int n = 0;

	if (removed == phead) return;
	while (removed != phead) {
		if (strcmp(removed->data.music, name) == 0) {
			removed->llink->rlink = removed->rlink;
			removed->rlink->llink = removed->llink;
			free(removed);
			printf("'%s'를 삭제하였습니다.\n", name);
			n++;
			return;
		}
		removed = removed->rlink;
	}
	if (n == 0) printf("\n같은 이름의 음악이 없습니다.\n");
}

void search_node(DLinkNode* phead, char name[]) { // 음악 제목으로 검색
	DLinkNode* p = phead->rlink;
	int n = 0;

	while (p != phead) {
		if (strcmp(p->data.music, name) == 0) {
			printf("\n%s %s %c %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year);
			n++;
		}
		p = p->rlink;
	}
	if (n == 0) printf("\n같은 이름의 음악이 없습니다.\n");
}

void Recently_music(DLinkNode* phead) { // 최근 발매한 음악정보
	int music = phead->rlink->data.year;
	DLinkNode* p = phead->rlink;

	while (p != phead) {
		if (music <= p->data.year) {
			music = p->data.year;
		}
		p = p->rlink;
	}

	printf("\n========최근 발매한 음악 ========\n\n");
	for (DLinkNode* p = phead->rlink; p != phead; p = p->rlink) {
		if (music == p->data.year) {
			printf("%s %s %c %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year);
		}
	}
}

void search_genre(DLinkNode* phead, char c) { // 특정 장르 음악 검색
	DLinkNode* p = phead->rlink;
	while (p != phead) {
		if (c == p->data.genre) {
			printf("%s %s %c %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year);
		}
		p = p->rlink;
	}
}

int main(void) {
	DLinkNode* head = (DLinkNode*)malloc(sizeof(DLinkNode));
	init(head);
	char m[10];
	char s[10];
	char g;
	int y, n;

	while (1) {
		printf("\n1. 입력\n2. 노드 출력\n3. 갯수 출력\n4. 노드 삭제\n5. 종료\n6. 순환 프린트\n7. 순환 역순 프린트\n8. 순환 노드갯수\n9. 음악검색\n10. 최근 발매한 음악정보\n11. 음악 장르검색\n");
		scanf("%d", &n);

		switch (n) {
		case 1: {
			printf("음악제목, 가수, 장르, 발표년도 입력: ");
			scanf("%s %s %c %d", m, s, &g, &y);

			if (g != 'B' && g != 'C' && g != 'H' && g != 'J' && g != 'T') {
				printf("\n\n장르를 잘못 입력하였습니다.\n");
			}
			else {
				dinsert_node(head, m, s, g, y);
			}
			break;
		}
		case 2: {
			printf("\n========음악 정보 출력========\n\n");
			dlist_display(head);
			break;
		}
		case 3: {
			printf("노드의 갯수 : %d\n", dlist_length(head));
			break;
		}
		case 4: {
			char name[10];
			printf("삭제할 음악 제목을 입력하세요. : ");
			scanf("%s", name);

			delete_node(head, name);
			break;
		}
		case 5: {
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		/*case 6: {
			printf("\n========순환호출을 이용한 음악정보 출력========\n\n");
			dlist_display2(head);
			break;
		}
		case 7: {
			printf("\n========순환호출을 이용한 음악정보 역순 출력========\n\n");
			dlist_display3(head);
			printf("NULL\n");
			break;
		}
		case 8: {
			printf("순환호출을 이용한 노드의 갯수 : %d\n", dlist_length2(head));
			break;
		}*/
		case 9: {
			char search_music[10];
			printf("찾을 음악 제목 입력:\n");
			scanf("%s", search_music);
			search_node(head, search_music);
			break;
		}
		case 10: {
			Recently_music(head);
			break;
		}
		case 11: {
			char c;
			printf("찾으실 음악의 장르를 입력하세요. : ");
			getchar();
			scanf("%c", &c);

			if (c != 'B' && c != 'C' && c != 'H' && c != 'J' && c != 'T') {
				printf("장르를 잘못 입력하였습니다.\n");
				break;
			}
			printf("\n========찾으신 장르의 음악 정보========\n\n");
			search_genre(head, c);
			break;
		}
		}
	}
	return 0;
}