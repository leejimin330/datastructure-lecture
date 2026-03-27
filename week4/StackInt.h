#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define N 100

typedef int elementInt;

typedef struct
{
	elementInt stack[N];
	int top;
}StackInt;

void initInt(StackInt* S)
{
	S->top = -1;
}

int isEmptyInt(StackInt* S)
{
	return S->top == -1;
}

int isFullInt(StackInt *S)
{
	return S->top == N - 1;
}

void pushInt(StackInt* S, elementInt e){
	if(isFullInt(S))
		printf("Overflow!\n");
	else{
		S->top++;
		S->stack[S->top] = e;
	}
}

elementInt popInt(StackInt* S){
	if(isEmptyInt(S)){
		printf("Empty!\n");
		return -1;
	}
	
	elementInt e = S->stack[S->top];
	S->top--;
	return e;
}

elementInt peekInt(StackInt* S){
	if(isEmptyInt(S)){
		printf("Empty!\n");
		return -1;
	}
	
	elementInt e = S->stack[S->top];
	return e;
	
}

void printInt(StackInt* S)
{
	for(int i = S->top; i>= 0; i--)
	{
		printf("|	%c	|\n", S->stack[i]);
		printf(" ------- \n");
	}
}

