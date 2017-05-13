#include <stdio.h>
#include <malloc.h> // �����Ҵ�
#include <stdlib.h> // exit()
#include <string.h>
#include <Windows.h>
#define MAX_IN 100

typedef char element;
typedef struct StackNode{	//���Ḯ��Ʈ ������ ����ü ����
	element item;
	struct StackNode *link;
}StackNode;

typedef struct{
	StackNode *top;
}LinkStack;

// �ʱ�ȭ �Լ�
void init(LinkStack *s)
{
	s->top = NULL;
}
// ���� ���� ���� �Լ�
int is_empty(LinkStack *s)
{
	return (s->top == NULL);
}
// ���� �Լ�
void push(LinkStack *s, int item)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	if (temp == NULL)
	{
		fprintf(stderr, "�޸� �Ҵ翡��\n");
		return;
	}
	else
	{
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}
// ���� �Լ�
element pop(LinkStack *s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "������ �������\n");
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
// ��ũ �Լ�
element peek(LinkStack *s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "������ �������\n");
	}
	else
		return s->top->item;

	return 0;
}
// �������� �켱���� ��ȯ
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
// ���� ǥ�� ���� -> ���� ǥ�� ����
char *infix_to_postfix(char exp[]) // �������� ������ �ٲ� �迭 postfix�� �ѱ�� �Լ�
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
		case '+': case '-': case '*': case '/': // ������
			//���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
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
			// ���� ��ȣ�� ���������� ���
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
// ���� ǥ�� ���� ��� �Լ�
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
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') // �Է��� �ǿ������̸� 
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
	printf("Infix(���� ǥ��� �Է�) : "); 
	scanf("%s", input);
	printf("Convert Infix to Postfix(���� ǥ������� ��ȯ)  : ");
	postfix = infix_to_postfix(input);	//����ǥ���->����ǥ������� ��ȯ�ϱ�
	printf("%s\n", postfix);
	printf("\n");
	result = eval(postfix);
	printf("Result(���� ǥ������� ����� �����) : %d\n", result);
	printf("\n");

	return 0;
	system("pause");
}




