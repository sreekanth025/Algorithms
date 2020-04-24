#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char data;
    struct node *next;
} node;

typedef struct stack{
    node *top;
} stack;

stack *init()
{
    stack *S = (stack *)malloc(sizeof(stack));
    S -> top = NULL;
    return S;
}

int isEmpty(stack *S)
{
    if(S -> top == NULL)
        return 1;
    else 
        return 0;
}

char getTopElement(stack *S)
{
    if (isEmpty(S))
        return 0;
    return S -> top -> data;
}

stack *push(stack *S, char data)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node -> data = data;
    new_node -> next = S -> top;
    S -> top = new_node;
    return S;
}

stack *pop(stack *S)
{
    if(isEmpty(S))
        return S;
    node *del_node = S -> top;
    S -> top = S -> top -> next;
    free(del_node);
    return S;
}

int main()
{
    char pre[100], post[100];
    int i, end = 0;
    printf("Enter the infix expression: \n");
    scanf("%s", pre);
    int len = strlen(pre);

    
    stack *S = init();
    
    for(i = 0; i < len; i++)
    {
        if(pre[i] >= 'a' && pre[i] <= 'z')
            post[end++] = pre[i];
            
        if(pre[i] == '(')
            S = push(S, pre[i]);
            
        if(pre[i] == '*' || pre[i] == '/')
        {
            while(getTopElement(S) == '*' || getTopElement(S) == '/')
            {
                post[end++] = getTopElement(S);
                S = pop(S);
            }
            
            S = push(S, pre[i]);
        }
        
        if(pre[i] == '+' || pre[i] == '-')
        {
            while(getTopElement(S) == '*' || getTopElement(S) == '/' || getTopElement(S) == '+' || getTopElement(S) == '-')
            {
                post[end++] = getTopElement(S);
                S = pop(S);
            }
            
            S = push(S, pre[i]);
        }
        
        if(pre[i] == ')')
        {
            while(getTopElement(S) != '(')
            {
                post[end++] = getTopElement(S);
                S =  pop(S);
            }
            
            S = pop(S);
        }
    }
    
    while(getTopElement(S) != NULL)
    {
        post[end++] = getTopElement(S);
        S = pop(S);
    }
    
    post[end++] = '\0';
    printf("%s\n", post);
    return 0;
}

