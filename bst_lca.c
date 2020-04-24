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

void lca(node *root, int a, int b)
{
	if(a < root->data && b < root->data)
		return lca(root->left, a, b);

	if(a > root->data && b > root->data)
		return lca(root->right, a, b);	

	if((a >= root->data && b <= root->data) || (a <= root->data && b >= root->data))
		printf("Lowest common ancestor of %d and %d is %d\n", a, b, root->data);
}

void lca2(node *root, int a, int b, node *parent)
{
	if(a < root->data && b < root->data)
		return lca2(root->left, a, b, root);
	
	if(a > root->data && b > root->data)
		return lca2(root->right, a, b, root);

	if((a > root->data && b < root->data) || (a < root->data && b > root->data))
		printf("Lowest common ancestor of %d and %d is %d\n", a, b, root->data);

	else if((a >= root->data && b <= root->data) || (a <= root->data && b >= root->data))
	{
		if(parent == NULL)
			printf("-1\n");
		else
			printf("Lowest common ancestor of %d and %d is %d\n", a, b, parent->data);
	}
	
}

int main()
{
	int n; 
	node *bst = NULL;
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	
	printf("Enter the elements: ");
	int i,s;
	for(i=0; i<n; i++)
	{
		scanf("%d", &s);
		bst = insert(bst, s);
	}	

	int a,b;
	printf("Enter two elements to find their LCA: ");
	scanf("%d %d", &a, &b);

	lca2(bst, a, b, NULL);	
		
	return 0;	
}
