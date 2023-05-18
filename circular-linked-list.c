/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {	//양방향 연결 리스트의 노드를 구조체로 선언한다.
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;


/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {	//인수 headnode의 값을 변경하기 위해 이중 포인터로 매개변수 선언

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)	
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	listNode *p = h->rlink;
	listNode *prev = NULL;

	while(p != NULL || p != h)	//prev포인터가 p포인터의 뒤를 따라가며 메모리 할당 해제한다.
	{
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);	//헤드포인터 또한 메모리 할당 해제한다.

	return 0;
}



void printList(listNode* h) {	
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {		//리스트가 존재하지 않을 경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {	//리스트의 마지막 노드거나 또는 최초 노드로 돌아왔을 때 까지 반복한다.
		printf("[ [%d]=%d ] ", i, p->key);	// 노드 출력
		p = p->rlink;	//포인터 이동
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);	
	//리스트에 존재하는 노드들의 값과 주소를 동시에 출력한다.

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode * node = (listNode *)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	listNode* p = h->llink;	//포인터 p를 리스트의 마지막 노드로 이동

	p->rlink = node;	//노드를 리스트의 마지막에 연결하고 첫번째 노드와도 연결하여 순환리스트를 완성한다.
	node->llink = p;
	node->rlink = h;
	h->llink = node;
	
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	listNode* p = h->llink ;//pointer p를 리스트의 마지막 노드로 이동

	if(p == h || h == NULL)	//list에 헤드노드 하나뿐이라면 삭제 중단.
	{
		printf("nothing to delete\n");
		return 0;
	}
	
	p->llink->rlink = h;	//마지막 노드의 연결을 끊고 메모리 해제한다.
	h->llink = p->llink;
	free(p);

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode *)malloc(sizeof(listNode));
	node -> key = key;
	node -> rlink = NULL;
	node -> llink = NULL;	//삽입할 노드 설정

	node->rlink = h->rlink;
	node->llink = h;
	h->rlink->llink = node;
	h->rlink = node;	//노드 첫번째(헤드노드 바로 다음 순서)에 삽입

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	listNode* p = h->rlink;	//포인터 p가 첫번째 노드를 가리키도록 한다.
	if(p == h || h == NULL)	//리스트에 헤드노드 뿐이라면 삭제 중단
	{
		printf("nothing to delete\n");
		return 0;
	}

	h->rlink = p->llink;	//첫번째 노드의 연결을 끊는다.
	p->llink->rlink = h;
	free(p);	//첫번째 노드 메모리 할당 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {	//리스트가 존재하지 않는다면 실행중단
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;				//노드를 가리킬 포인터들 선언
	listNode *trail = h;
	listNode *middle = h;

	
	h->llink = h->rlink;		//첫번째 노드를 마지막 노드로 옮긴다.

	while(n != NULL && n != h){	//모든 노드를 검사한다.
		trail = middle;			//노드 포인터 이동
		middle = n;
		n = n->rlink;
		middle->rlink = trail;	//노드를 역순정렬한다.
		middle->llink = n;
	}

	h->rlink = middle;			//마지막노드를 첫번째 노드로 옮긴다.

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	listNode* Node = (listNode *)malloc(sizeof(listNode));
	Node->key = key; 
	Node->llink = NULL;
	Node->rlink = NULL;		//삽입할 노드 설정

	listNode* p = h;		//노드를 가리킬 포인터 p선언
	while(p->rlink != h)	
	{
		if(p->rlink->key >= key)	//적절한 위치에 노드를 삽입한다.
		{
			Node->rlink = p->rlink;
			Node->llink = p;
			p->rlink->llink = Node;
			p->rlink = Node;
			return 1;
		}
		p = p->rlink;
	}
	printf("asdf");
	Node->rlink = h;	//삽입할 위치가 마지막이거나 리스트에 노드가 존재하지 않을 경우
	Node->llink = p;
	p->rlink = Node;
	h->llink = Node;
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode * p = h;

	while(p->rlink != h)	//리스트의 모든 노드를 검사한다.
	{
		p = p->rlink;
		if(p->key == key)	//key값이 일치하다면 노트 삭제
		{
			p->llink->rlink = p->rlink;
			p->rlink->llink = p->llink;
			free(p);
			return 1;
		}
	}
	printf("nothing to delete\n");	//리스트의 모든 노드를 검사했다면 삭제할게 없는 것!

	return 0;
}


//이종연 배연복 피하기