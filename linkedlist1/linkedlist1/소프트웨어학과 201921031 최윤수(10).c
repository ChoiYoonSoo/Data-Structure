#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct {
	char music[10]; // 음악제목
	char singer[10]; // 가수
	char genre; // 장르
	int year; // 발표년도
	int time; // 재생시간
}element;

typedef struct DLinkNode { // 이중 연결 노드 타입
	element data;
	struct DLinkNode* llink;
	struct DLinkNode* rlink;
}DLinkNode;

DLinkNode* song;

void error(char* message) { // 에러 함수
	fprintf(stderr, "%s", message);
	exit(1);
}

void init(DLinkNode* phead) { // 이중 연결 리스트 초기화
	phead->llink = phead;
	phead->rlink = phead;
}

void dinsert_node(DLinkNode* phead, char m[], char s[], char g, int y, int t) { // 오름차순 노드 삽입
	DLinkNode* node = phead->rlink;
	DLinkNode* nextnode = (DLinkNode*)malloc(sizeof(DLinkNode));

	strcpy(nextnode->data.music, m);
	strcpy(nextnode->data.singer, s);
	nextnode->data.genre = g;
	nextnode->data.year = y;
	nextnode->data.time = t;

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

void dlist_display(DLinkNode* phead) { // 현재 리스트에 연결된 노드 데이터 출력

	DLinkNode* p;
	if (phead->rlink == phead) {
		printf("재생목록이 비어있습니다.\n");
		return;
	}
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<- %s %s %c %d %d -> ", p->data.music, p->data.singer, p->data.genre, p->data.year, p->data.time);
	}
	printf("\n");
}

void delete_node(DLinkNode* phead, char name[]) { // 음악 제목 삭제 함수
	DLinkNode* removed = phead->rlink;
	int n = 0;

	if (removed == phead) {
		printf("재생목록이 비어있습니다.\n");
		return;
	}

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

DLinkNode* search_node(DLinkNode* phead, char name[]) { // 음악 제목으로 검색
	DLinkNode* p = phead->rlink;
	int n = 0;

	while (p != phead) {
		if (strcmp(p->data.music, name) == 0) {
			return p;
		}
		p = p->rlink;
	}
	return NULL;
}

DLinkNode* Recently_music(DLinkNode* phead) { // 최근 발매한 음악정보
	DLinkNode* p = phead->rlink;
	DLinkNode* music = phead->rlink;

	if (p == phead) return NULL;

	printf("\n========최근 발매한 음악 ========\n\n");
	for (; p != phead; p = p->rlink) {
		if (p->data.year >= music->data.year) {
			music = p;
		}
	}
	return music;
}

void search_genre(DLinkNode* phead, char c) { // 특정 장르 음악 검색
	DLinkNode* p = phead->rlink;
	int n = 0;
	if (p == phead) {
		printf("재생목록이 비어있습니다.\n");
		return;
	}
	while (p != phead) {
		if (c == p->data.genre) {
			printf("%s %s %c %d %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year, p->data.time);
			n++;
		}
		p = p->rlink;
	}
	if (n == 0) printf("입력한 장르의 음악이 없습니다.\n");
}

void play_music(DLinkNode* phead) { // 음악 실행 출력
	DLinkNode* p;
	int cnt = song->data.time;

	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (p == song) {
			printf(" <- playing ~ %s 재생시간: %d초 -> ", p->data.music, p->data.time);
		}
		else
			printf(" <- %s %d -> ", p->data.music, p->data.time);
	}

	for (int i = 1; i <= cnt; i++) {
		printf("\n실행중 %d...\n", i);
		Sleep(1000);
	}
	printf("\n재생완료\n");
}

void start_music(DLinkNode* phead, char ch) { // 음악 이동
	switch (ch) {
	case 'P':
		song = song->rlink;
		if (song == phead) {
			song = song->rlink;
		}
		play_music(phead);
		break;
	case '>':
		song = song->rlink;
		if (song == phead) {
			song = song->rlink;
		}
		play_music(phead);
		break;
	case '<':
		song = song->llink;
		if (song == phead) {
			song = song->llink;
		}
		play_music(phead);
		break;
	case 'F': case 'f':
		song = phead->rlink;
		play_music(phead);
		break;
	case 'L': case 'l':
		song = phead->llink;
		play_music(phead);
		break;
	}
}

void all_free(DLinkNode* phead) {
	DLinkNode* removed = phead->rlink;

	while (removed != phead) {
		phead->rlink = removed->rlink;
		removed->rlink->llink = phead;
		free(removed);
		removed = phead->rlink;
	}
	printf("\nAll Free!\n");
}

int main(void) {
	DLinkNode* head = (DLinkNode*)malloc(sizeof(DLinkNode));
	init(head);
	song = head;
	char m[10];
	char s[10];
	char g;
	int y, n, t;

	while (1) {
		printf("\n0. 종료\n");
		printf("1. 입력\n");
		printf("2. 노드 출력\n");
		printf("3. 갯수 출력\n");
		printf("4. 노드 삭제\n");
		printf("5. 음악검색\n");
		printf("6. 최근 발매한 음악정보\n");
		printf("7. 음악 장르검색\n");
		printf("8. 재생메뉴\n");
		scanf("%d", &n);

		switch (n) {
		case 0: {
			all_free(head);
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		case 1: {
			printf("음악제목, 가수, 장르, 발표년도, 재생시간 입력: ");
			scanf("%s %s %c %d %d", m, s, &g, &y, &t);

			if (g != 'B' && g != 'C' && g != 'H' && g != 'J' && g != 'T') {
				printf("\n\n장르를 잘못 입력하였습니다.\n");
			}
			else {
				dinsert_node(head, m, s, g, y, t);
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
			DLinkNode* p;
			char search_music[10];
			printf("찾을 음악 제목 입력:\n");
			scanf("%s", search_music);
			p = search_node(head, search_music);

			if (p != NULL) {
				printf("\n%s %s %c %d %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year, p->data.time);
			}
			else printf("음악의 정보가 없습니다.\n");
			break;
		}
		case 6: {
			DLinkNode* p;
			p = Recently_music(head);
			if (p != NULL) {
				printf("%s %s %c %d %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year, p->data.time);
			}
			else printf("음악의 정보가 없습니다.\n");
			break;
		}
		case 7: {
			char c;
			printf("찾으실 음악의 장르를 입력하세요.(B,C,H,J,T) : ");
			getchar();
			scanf("%c", &c);

			if (c != 'B' && c != 'C' && c != 'H' && c != 'J' && c != 'T') {
				printf("\n장르를 잘못 입력하였습니다.\n");
				break;
			}
			printf("\n========찾으신 장르의 음악 정보========\n\n");
			search_genre(head, c);
			break;
		}
		case 8: {
			char ch;
			printf("\n=========재생메뉴========\n");
			printf("P 재생\n");
			printf("> 다음곡\n");
			printf("< 이전곡\n");
			printf("L/l 마지막곡\n");
			printf("F/f 처음곡\n");
			getchar();
			scanf("%c", &ch);
			
			start_music(head, ch);
			break;
		}
		}
	}
	return 0;
}