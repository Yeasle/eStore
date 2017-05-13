#include <stdio.h>
#include <malloc.h> // 동적할당
#include <stdlib.h> // exit()
#include <string.h>
#include <Windows.h>
#define MAX_IN 100

typedef char element;
typedef struct StackNode{	//연결리스트 스택의 구조체 생성
	element item;
	struct StackNode *link;
}StackNode;

typedef struct{
	StackNode *top;
}LinkStack;

// 초기화 함수
void init(LinkStack *s)
{
	s->top = NULL;
}
// 공백 상태 검출 함수
int is_empty(LinkStack *s)
{
	return (s->top == NULL);
}
// 삽입 함수
void push(LinkStack *s, int item)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	if (temp == NULL)
	{
		fprintf(stderr, "메모리 할당에러\n");
		return;
	}
	else
	{
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}
// 삭제 함수
element pop(LinkStack *s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	else
	{
		StackNode *temp = s->top;
		int item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}
// 피크 함수
element peek(LinkStack *s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "스택이 비어있음\n");
	}
	else
		return s->top->item;

	return 0;
}
// 연산자의 우선순위 반환
int priority(char op)
{
	switch (op)
	{
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}
// 중위 표기 수식 -> 후위 표기 수식
char *infix_to_postfix(char exp[]) // 중위에서 후위로 바뀐 배열 postfix을 넘기는 함수
{
	int i = 0, j = 0;
	char ch, top_op;
	int len = strlen(exp);
	static char postfix[MAX_IN];
	LinkStack s;

	init(&s);
	for (i = 0; i<len; i++)
	{
		ch = exp[i];
		switch (ch)
		{
		case '+': case '-': case '*': case '/': // 연산자
			//스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while (!is_empty(&s) && (priority(ch) <= priority(peek(&s))))
			{
				postfix[j] = pop(&s);
				j++;
			}
			push(&s, ch);
			break;
		case '(':
			push(&s, ch);
			break;
		case ')':
			top_op = pop(&s);
			// 왼쪽 괄호를 만날때까지 출력
			while (top_op != '(')
			{
				postfix[j] = top_op;
				j++;
				top_op = pop(&s);
			}
			break;
		default:
			postfix[j] = ch;
			j++;
			break;
		}
	}
	while (!is_empty(&s))
	{
		postfix[j] = pop(&s);
		j++;
	}

	return postfix;
}
// 후위 표기 수식 계산 함수
int eval(char exp[])
{
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	LinkStack s;

	init(&s);
	for (i = 0; i<len; i++)
	{
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') // 입력이 피연산자이면 
		{
			value = ch - '0';
			push(&s, value);
		}
		else
		{
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch){
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1*op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);
}


int main(void)
{
	char input[MAX_IN];
	char *postfix;
	int result;

	printf("[Convert Infix to Postfix Program]\n\n");
	printf("Infix(중위 표기식 입력) : "); 
	scanf("%s", input);
	printf("Convert Infix to Postfix(후위 표기식으로 변환)  : ");
	postfix = infix_to_postfix(input);	//중위표기식->후위표기식으로 변환하기
	printf("%s\n", postfix);
	printf("\n");
	result = eval(postfix);
	printf("Result(후위 표기식으로 계산한 결과값) : %d\n", result);
	printf("\n");

	return 0;
	system("pause");
}




