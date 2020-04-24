#include <stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node;

node *newNode(int data)
{
    node *new_node = (node *)malloc(sizeof(node));    
    new_node -> data = data;
    new_node -> left = NULL;
    new_node -> right = NULL;
    return new_node;
}

void inorder_traverse(node *root)
{
    if(root == NULL)
        return ;
    inorder_traverse(root->left);
    printf("%d ", root->data);
    inorder_traverse(root->right);
}

void preorder_traverse(node *root)
{
    if(root == NULL)
        return ;
    printf("%d ", root->data);
    preorder_traverse(root->left);
    preorder_traverse(root->right);
}

void postorder_traverse(node *root)
{
    if(root == NULL)
        return ;
    postorder_traverse(root->left);
    postorder_traverse(root->right);
    printf("%d ", root->data);
}

int main()
{
    node *root          = newNode(1); 
    root->left          = newNode(2); 
    root->right         = newNode(3); 
    root->left->left    = newNode(4); 
    root->left->right   = newNode(5);    
    
    printf("preorder: ");
    preorder_traverse(root);
    printf("\ninorder: ");
    inorder_traverse(root);
    printf("\npostorder: ");
    postorder_traverse(root);
    printf("\n");
    
}
