#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right; 
} node;

node *new_node(int data)
{
	node *t = (node *)malloc(sizeof(node));
	t -> data = data;
	t -> left = NULL;
	t -> right = NULL;

	return t;
}

node *insert(node *root, int key)
{
	if(root == NULL)
		root = new_node(key);

	if(key < root->data)
		root->left = insert(root->left, key);

	else if(key > root->data)
		root->right = insert(root->right, key);
	
	return root;
}

node *delete(node *root, int key)
{
	if(root == NULL)
		return root;

	if(key < root->data)
		root-> left = delete(root->left, key);
	else if(key > root-> data)
		root -> right = delete(root->right, key);

	else
	{
		if(root->left != NULL && root->right != NULL)
		{
			node *t = root->right;
			while(t->left != NULL)
				t = t->left;
			root->data = t->data;
			root->right = delete(root->right, t->data);
			return root;
		}
		node *t = (root->left != NULL) ? root->left : root->right;
		free(root);
		return t;
	}
	return root;
}

void preorder_traversal(node *root)
{
	if(root == NULL)
		return;
	printf("%d ", root->data);
	preorder_traversal(root->left);
	preorder_traversal(root->right);
}

int main()
{
	node *bst = NULL;
	int n; 
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	
	printf("Enter the elements: ");
	int i,s;
	for(i=0; i<n; i++)
	{
		scanf("%d", &s);
		bst = insert(bst, s);
	}	
	
	printf("PreOrder traversal: ");
	preorder_traversal(bst);
	printf("\n");
	
	printf("Enter the element to delete: ");
	scanf("%d", &s);
	bst = delete(bst, s);

	printf("PreOrder traversal: ");
	preorder_traversal(bst);
	printf("\n");

	return 0;
}
