#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char element;

typedef struct Node
{
	element data;
	struct Node* next;
	struct Node* previous;
} Node;

typedef struct
{
	Node* H;
	Node* T;
  Node* cursor; //cursor를 포인터로 변환
  int size;
} DListType;

Node* makeNode(element e)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = e;
	node->next = NULL;
	node->previous = NULL; 
	return node;
}

void init(DListType* DL)
{
	DL->H = makeNode(0);
	DL->T = makeNode(0);
	DL->cursor = DL->H;//cursor를 가장 앞 head로 선언

	DL->H->next = DL->T;
	DL->H->previous = NULL;

	DL->T->previous = DL->H;
	DL->T->next = NULL;
  
  DL->size = 0;
}

int isEmpty(DListType* DL)
{
	return DL->size == 0;
}

void moveLeft(DListType* DL){
  if(DL->cursor != DL->H)//cursor가 가장 앞 head가 아니면
    DL->cursor = DL->cursor->previous;//cursor를 하나 앞으로 이동
  return;
}

void moveRight(DListType* DL){
  if(DL->cursor->next != DL->T){//cursor가 tail이 아니면
    DL->cursor = DL->cursor->next;//cursor를 하나 뒤로 이동
    return;
  }
}

void insertChar(DListType* DL, element e)
{
	Node* node = makeNode(e);

	//cursor의 위치가 곧 삽입할 위치이므로 cursor의 위치에 값을 삽입
	node->next = DL->cursor->next;
	node->previous = DL->cursor;

	DL->cursor->next->previous = node;
	DL->cursor->next = node;

	DL->size++;
    DL->cursor = node;
}

/*void insertFirst(DListType* DL, element e)
{
	insert(DL, e);
}

void insertLast(DListType* DL, element e)
{
	insert(DL, e, DL->size + 1);
}*/

element deleteChar(DListType* DL)
{
  if(isEmpty(DL)) return 0;
  if(DL->cursor == DL->H) return 0;
  //cursor가 가리키는 위치에 있는 값 delete
  Node* p = DL->cursor;

	element data = p->data;
    //p의 앞 뒤를 연결해서 값을 삭제
	p->previous->next = p->next;
	p->next->previous = p->previous;
  
  DL->cursor = p->previous;
	free(p);

	DL->size--;
	return data;
}

void printText(DListType* DL)
{
	for(Node* p = DL->H->next; p != DL->T; p = p->next)
	{
		printf("%c ", p->data);
    if(DL->cursor == p)
      printf("| ");
	}
  printf("\n");
}

int main()
{
	DListType DL;
	init(&DL);
	char s[50];
  scanf("%s", s);
	
  for(int i = 0; i < strlen(s); i++){
    if(s[i] <= 'Z' && s[i] >= 'A'){
      insertChar(&DL, s[i]);
    }
    else if(s[i] == '<') 
      moveLeft(&DL);
    else if(s[i] == '>')
      moveRight(&DL);
    else if(s[i] == '-')
      deleteChar(&DL);
    printText(&DL);
  }

	printText(&DL);
}
