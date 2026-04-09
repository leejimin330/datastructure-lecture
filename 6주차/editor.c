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
	int size;
  int cursor;
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
	
	DL->H->next = DL->T;
	DL->H->previous = NULL;

	DL->T->previous = DL->H;
	DL->T->next = NULL;
  
  DL->size = 0;
  DL->cursor = 0;
}

int isEmpty(DListType* DL)
{
	return DL->size == 0;
}

void moveLeft(DListType* DL){
  if(DL->cursor > 0)
    DL->cursor--;
  return;
}

void moveRight(DListType* DL){
  if(DL->cursor >= DL->size){
    DL->cursor = DL->size;
    return;
  }
  DL->cursor++;
}


void insertChar(DListType* DL, element e)
{
	if(DL->cursor < 0 || DL->cursor > DL->size + 1){
		printf("Invalid Position1\n");
		return;
	}

	Node* p = DL->H;

	for(int i = 0; i < DL->cursor; i++){
		p = p->next;
	}

	Node* node = makeNode(e);

	node->next = p->next;
	node->previous = p;

	p->next->previous = node;
	p->next = node;

	DL->size++;
  moveRight(DL);
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
	if(isEmpty(DL)){
		return 0;
	}

	if(DL->cursor < 1 || DL->cursor > DL->size){
    return 0;
	}

	Node* p = DL->H;

	for(int i = 0; i < DL->cursor; i++){
		p = p->next;
	}

	element data = p->data;

	p->previous->next = p->next;
	p->next->previous = p->previous;

	free(p);
	DL->size--;
  moveLeft(DL);
  
	return data;
}

void printText(DListType* DL)
{
  int i = 1;
	for(Node* p = DL->H->next; p != DL->T; p = p->next)
	{
		printf("%c ", p->data);
    if(DL->cursor == i)
      printf("| ");
    i++;
	}
  if(DL->cursor == i)
    printf("| ");
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
