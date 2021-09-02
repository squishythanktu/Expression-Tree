#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE 
#include <stdio.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h> 
#include<math.h>
#include<Windows.h>
#define MAX 100
char Stack[MAX];
int top = -1, i = 0;
int precedence(char symbol) {
	if (symbol == '@' || symbol == '#' || symbol == '$' || symbol == '&' || symbol == '~' || symbol == '|' || symbol == '!') return 4;
	else if (symbol == '^')
	{
		return(3);
	}
	else if (symbol == '*' || symbol == '/')
	{
		return(2);
	}
	else if (symbol == '+' || symbol == '-')
	{
		return(1);
	}
	else
	{
		return(0);
	}
}
char TrigotoOperater(char item[]) {
	if (!strcmp(item, "sin")) return '@';
	else if (!strcmp(item, "cos")) return '#';
	else if (!strcmp(item, "tan")) return '$';
	else if (!strcmp(item, "cot")) return '&';
	else if (!strcmp(item, "log")) return '~';
	else if (!strcmp(item, "exp")) return '|';
}
void push(char item) {
	if (top >= MAX - 1)
	{
		printf("\n Stack Overflow.");
	}
	else
	{
		top = top + 1;
		Stack[top] = item;
	}
}
char pop()
{
	char item;
	if (top < 0)
	{
		printf("Stack Under Flow: Invalid Infix Expression");
		getchar();
		return 0;
	}
	else
	{
		item = Stack[top];
		Stack[top] = NULL;
		top = top - 1;
		return(item);
	}
}
char Top() {
	return Stack[top];
}
void removeString(char item[]) {
	for (int x = 0; x < MAX; x++) item[x] = NULL;
}
void InfixtoPostfix(char Infix[], char Postfix[][10]) {
	char temp = Infix[0], x;
	push('(');
	strcat(Infix, ")");
	int  j = 0, k = 0;
	while (1) {
		if (temp == NULL) {
			break;
		}
		if (isdigit(temp) || isalpha(temp)) {
			Postfix[i][j] = temp;
			j++;
		}
		else if (temp == '(') {
			if (isalpha(Postfix[i][j - 1])) {
				temp = TrigotoOperater(Postfix[i]);
				removeString(Postfix[i]);
				j = 0;
				k--;
				continue;
			}
			push(temp);
		}
		else if (precedence(temp) != 0) {
			if (isdigit(Postfix[i][0])) {
				i++;
				j = 0;
			}
			x = pop();
			while (precedence(x) != 0 && precedence(x) >= precedence(temp)) {

				Postfix[i][0] = x;
				i++;
				x = pop();
			}
			push(x);
			push(temp);
		}
		else if (temp == ')') {
			if (isdigit(Postfix[i][0])) {
				i++;
				j = 0;
			}
			x = pop();
			while (x != '(')
			{
				Postfix[i][0] = x;
				i++;
				x = pop();
			}
		}
		else
		{
			printf("\nInvalid infix Expression.\n");
			getchar();
		}
		k++;
		temp = Infix[k];
	}
}
// TREE STRUCTURE //
typedef struct tree
{
	char info[10];                  // to account for operators as nodes
	struct tree* left;
	struct tree* right;
}BTREE;
BTREE* root = NULL;
// STACK STRUCTURE //
typedef struct stack {
	BTREE* info[MAX];         // stack contains node's addresses
	int top;
}STACK;
STACK s;
BTREE* getnode(void)
{
	BTREE* p;
	p = (BTREE*)malloc(sizeof(BTREE));
	return(p);
}
BTREE* maketree(char item[])
{
	BTREE* p;
	p = getnode();
	strcpy(p->info, item);
	p->left = NULL;
	p->right = NULL;
	return(p);
}
void pushs(BTREE* item)
{
	if (s.top == MAX - 1)
	{
		printf("\n Stack Overflow!");
		getch();
		exit(1);
	}
	s.info[++s.top] = item;
}
BTREE* pops(void)
{
	if (s.top == -1)
	{
		printf("\n Stack Underflow!");
		getch();
		exit(1);
	}
	return(s.info[s.top--]);
}
void CreateExprTree(char Postfix[][10])
{
	BTREE* p;
	int x = 0;
	char temp[5];
	while (Postfix[x][0] != NULL)
		{
			if (isdigit(Postfix[x][0]))
			{
				p = maketree(Postfix[x]);
				pushs(p);
			}
			else     // char is operator
			{
				if (precedence(Postfix[x][0]) == 4) {
					if (Postfix[x][0] == '@') strcpy(temp, "sin");
					else if (Postfix[x][0] == '#') strcpy(temp, "cos");
					else if (Postfix[x][0] == '$') strcpy(temp, "tan");
					else if (Postfix[x][0] == '&') strcpy(temp, "cot");
					else if (Postfix[x][0] == '|') strcpy(temp, "exp");
					else if (Postfix[x][0] == '~') strcpy(temp, "log");
					if (Postfix[x][0] == '!') {
						p = maketree(Postfix[x]);
						p->left = pops();
						p->right = NULL;
					}
					else if (Postfix[x][0] == '~') {
						p = maketree(temp);
						p->right = pops();
						p->left = pops();

					}
					else {
						p = maketree(temp);
						p->left = NULL;
						p->right = pops();
					}
				}
				else {

					p = maketree(Postfix[x]);
					p->right = pops();
					p->left = pops();
				}
			pushs(p);
		}
	x++;
	}
	root = pops();      // stack now contains address of root node                                        
}
int getHeight(BTREE* p)
{
	if (!p)
		return 0;
	else {
		int left = getHeight(p->left);
		int right = getHeight(p->right);
		if (left >= right)
			return left + 1;
		else
			return right + 1;
	}
}
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
//PRINT TREE IN CONSOLE
void structure(BTREE* root, int x, int y, int px = 0) {
	if (root == NULL) return;
	gotoxy(x, y);
	int a = abs(px - x) / 2;
	printf("%s", root->info);
	structure(root->left, x - a, y + 1, x);
	structure(root->right, x + a, y + 1, x);
}

/* main function begins */
int main() {
	char Infix[MAX], Postfix[MAX][10];
	FILE* fi;
	fi = fopen("data.txt", "r");
	fscanf(fi, "%s", &Infix);
	fclose(fi);
	for (int k = 0; k < MAX; k++) {
		Stack[k] = NULL;
		for (int j = 0; j < 10; j++) {
			Postfix[k][j] = NULL;
		}
	}
	InfixtoPostfix(Infix, Postfix);
	for (int x = 0; x <= i; x++)
		printf("%s	", Postfix[x]);
	CreateExprTree(Postfix);
	s.top = -1;
	structure(root,50,10,1);
	getch();
	return 0;
}
