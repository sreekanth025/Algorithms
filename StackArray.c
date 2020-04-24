#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 4

struct st{
	int A[MAXLEN];
	int top;
};

typedef struct st stack;

stack init ();
int isEmpty (stack);
int isFull (stack);
int GetTopElement (stack);
stack push (stack, int);
stack pop (stack);
void print (stack);


int main ()
{
	stack S;

	S = init();      printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = push(S, 12); printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = push(S, 2);  printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = push(S, 99); printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = pop(S);      printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = push(S, 3);  printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = push(S, 33); printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = push(S, 39); printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = pop(S);      printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = pop(S);      printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = pop(S);      printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = pop(S);      printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));
	S = pop(S);      printf("Current stack : "); print(S); printf(" with top = %d.\n\n", GetTopElement(S));

	return 0;
}

stack init ()
{
	stack S;
	S.top = -1;
	return S;
}

int isEmpty (stack S)
{
	return (S.top == -1);
}

int isFull (stack S)
{
	return (S.top == MAXLEN - 1);
}

int GetTopElement (stack S)
{
	if (isEmpty(S)) {
		printf("Stack is Empty ");
		return 0;
	}
	return S.A[S.top];
}

stack push (stack S , int data)
{
	if (isFull(S)) {
		printf("Stack is Full.\n");
		return S;
	}
	++S.top;
	S.A[S.top] = data;
	return S;
}

stack pop (stack S)
{
	if (isEmpty(S)) {
		printf("Stack is Empty.\n");
		return S;
	}
	--S.top;
	return S;
}

void print (stack S)
{
	int i;
	for (i = S.top; i >= 0; --i)
		printf("%4d",S.A[i]);
}

