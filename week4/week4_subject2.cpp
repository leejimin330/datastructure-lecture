#include"Stack.h"
#include"StackInt.h"

#define N 100

int evaluate(char str[], int arr[], int n)
{
	StackInt S;
	S.top = -1;
	
	int op1, op2;
	int idxStr = 0;

	for(int i = 0; i < n; i++){
		if(arr[i] != -1){
			pushInt(&S, arr[i]);
		}
		else{
			char c = str[idxStr++];
			
			op2 = popInt(&S);
			op1 = popInt(&S);
			
			switch(c){
				case '+': pushInt(&S, op1 + op2); break;
				case '-': pushInt(&S, op1 - op2); break;
				case '*': pushInt(&S, op1 * op2); break;
				case '/': pushInt(&S, op1 / op2); break;
			}
		}
	}
	return popInt(&S);
}

int prec(char op)
{
	if(op == '+' || op == '-') return 1;
	if(op == '*' || op == '/') return 2;
	return 0;
}

void infixToPostfix(int n, char expr[], int arr[])
{
	StackType S;
	init(&S);
	
	char c, op;
	
	int afterArr[N];
	char afterStr[N];
	
	int idxArr = 0;
	int idxStr = 0;
	int idxExpr = 0;
	for(int i = 0; i < n; i++){
		if(arr[i] == -1){
			c = expr[idxExpr++];
			if(c == '('){
				push(&S, c);
			}
			else if(c == ')')
			{
				while(!isEmpty(&S))
				{
					op = pop(&S);
					if(op == '('){
						break;
					}
					printf("%c ", op);
					afterArr[idxArr++] = -1;
					afterStr[idxStr++] = op;
				}
			}
			else if (strchr("+-*/", c))
			{
				while(!isEmpty(&S)){
					op = peek(&S);
					if(op == '(') {
						break;
					}
					if(prec(c) <= prec(op)){
						char op2 = pop(&S);
						printf("%c ", op2);
						afterArr[idxArr++] = -1;
						afterStr[idxStr++] = op2;
					}
					else 
						break;
				}
				push(&S, c);
			}
		}
		else {
			printf("%d ", arr[i]);
			afterArr[idxArr++] = arr[i];
		}
	}
	while(!isEmpty(&S) ){
		char op2 = pop(&S);
		printf("%c ", op2);
		afterArr[idxArr++] = -1;
		afterStr[idxStr++] = op2;
	}
	printf("\n");
	afterStr[idxStr] = '\0';
	printf("%d", evaluate(afterStr, afterArr, idxArr));
}

int inputStr(char input[], int arr[], char str[]){
	int inputSize = strlen(input); 
	int idxArr = 0;
	int idxStr = 0;
	for(int i = 0; i < inputSize; i++){
		char c = input[i];
		if(strchr("+-*/()", c)){
			arr[idxArr++] = -1;
			str[idxStr++] = c;
		}
		else if(c >= '0' && c <= '9'){
        char num[N] = {0};
        int j = 0;
        while(i < inputSize && input[i] >= '0' && input[i] <= '9'){
            num[j++] = input[i++];
        }
        num[j] = '\0'; 
        arr[idxArr++] = atoi(num);
        i--;
    	}
	}
	str[idxStr] = '\0';
	return idxArr;
}

int main(){
	int arr[N];
	char input[N];
	char str[N];
	
	printf("Input Expr... ");
	fgets(input, N, stdin);
	int n = inputStr(input, arr, str);
	infixToPostfix(n, str, arr);
	
	//printf("%d\n", evaluate(str));
	
}
