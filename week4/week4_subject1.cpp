#include"Stack.h"

#define N 100

int evaluate(char str[])
{
	StackType S;
	init(&S);
	
	int op1, op2, num;
	char c;
	
	int n = strlen(str);
	
	for(int i = 0; i < n; i++){
		c = str[i];
		if(isdigit(c)){
			num = c - '0';
			push(&S, num);
		}
		else if(strchr("+-*/", c)){
			op2 = pop(&S);
			op1 = pop(&S);
			
			switch(c){
				case '+':
					push(&S, op1 + op2);
					break;
				case '-':
					push(&S, op1 - op2);
					break;
				case '*':
					push(&S, op1 * op2);
					break;
				case '/':
					push(&S, op1 / op2);
					break;
			}
		}
	}
	return pop(&S);
}

int prec(char op)
{
	if(op == '!' || op == '@' || op == '#') return 6;
	if(op == '*' || op == '/') return 5;
	if(op == '+' || op == '-') return 4;
	if(op == '<' || op == '>') return 3;
	if(op == '&') return 2;//&&연산자는 &로 처리 
	if(op == '|') return 1;//||연산자는 |로 처리 
	return 0; 
}

bool checkstr(char c)
{
	if(c == '+') return true;
	if(c == '-') return true;
	if(c == '*') return true;
	if(c == '/') return true;
	if(c == '>') return true;
	if(c == '<') return true;
	if(c == '!') return true;
	if(c ==  '&') return true;
	if(c == '|') return true;
	return false;
}

bool checklogic(char c)
{
	if(c ==  '&') return true;
	if(c == '|') return true;
	return false;
}

void printOp(char c){
	if(c == '&' || c == '|'){
		printf("%c%c", c, c);
	}
	else if(c == '@'){
		printf("++");
	}
	else if(c == '#'){
		printf("--");
	}
	else printf("%c", c);
	return;
}

void infixToPostfix(char expr[])
{
	StackType S;
	init(&S);
	
	char c, op;
	int n = strlen(expr);
	
	for(int i = 0; i < n; i++){
		c = expr[i];
		if(isdigit(c))//숫자라면 그냥 출력 
			printf("%c", c);
		else if(c == '(')//괄호열림 등장시 그냥 넣기 
			push(&S, c);
		else if(c == ')'){//괄호닫으면 
			while(!isEmpty(&S)){
				op = pop(&S);
				if(op == '(') break;//괄호 열기나올 때까지 pop
				printOp(op);
			}
		}
		else if(checkstr(c)){//연산자 확인 
			while(!isEmpty(&S)){
				op = peek(&S);
				if(op == '(') break;
				if(c == '!') break;
				if(prec(c) <= prec(op)){
					char op2 = pop(&S);
					printOp(op2);
				}
				else break;
			}
			push(&S, c);
		}
	}
	while(!isEmpty(&S)){
		char op2 = pop(&S);
		if(op2 != '('){
			printOp(op2);
		}
	}
	printf("\n");
}

void normalize(char *str1, char *str2){
    int i = 0, j = 0;

    while(str1[i]){
        if(str1[i] == '&' && str1[i+1] == '&'){
            str2[j++] = '&';
            i += 2;
        }
        else if(str1[i] == '|' && str1[i+1] == '|'){
            str2[j++] = '|';
            i += 2;
        }
        else if(str1[i] == '+' && str1[i+1] == '+'){
        	str2[j++] = '@';
        	i += 2;
		}
        else if(str1[i] == '-' && str1[i+1] == '-'){
        	str2[j++] = '#';
        	i += 2;
		}
        else{
            str2[j++] = str1[i++];
        }
    }
    str2[j] = '\0';
}

int main(){
	int tc;
	scanf("%d", &tc);
	getchar();
	while(tc--){
		char str1[N], str2[N];
		printf("Input Expr...");
		fgets(str1, N, stdin);
		normalize(str1, str2);
		infixToPostfix(str2);
	}
}

