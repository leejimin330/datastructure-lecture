#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define N 100

typedef char element;

typedef struct
{
	element stack[N];
	int top;
}StackType;

void init(StackType* S)
{
	S->top = -1;
}

int isEmpty(StackType* S)
{
	return S->top == -1;
}

int isFull(StackType *S)
{
	return S->top == N - 1;
}

void push(StackType* S, element e){
	if(isFull(S))
		printf("Overflow!\n");
	else{
		S->top++;
		S->stack[S->top] = e;
	}
}

element pop(StackType* S){
	if(isEmpty(S)){
		printf("Empty!\n");
		return -1;
	}
	
	element e = S->stack[S->top];
	S->top--;
	return e;
}

element peek(StackType* S){
	if(isEmpty(S)){
		printf("Empty!\n");
		return -1;
	}
	
	element e = S->stack[S->top];
	return e;
	
}

void print(StackType* S)
{
	for(int i = S->top; i>= 0; i--)
	{
		printf("|	%c	|\n", S->stack[i]);
		printf(" ------- \n");
	}
}

