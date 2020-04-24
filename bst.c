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


node *build_bst(int pre_order[], int low, int high)
{	
		node *root = new_node(pre_order[low]);
//		printf("%d added to tree\n", pre_order[low]);

		if(low == high)
			return root;		

		int i,j;	
		for(i=low+1; i<=high; i++)
		{
			if(pre_order[i] > pre_order[low])
				j = i;
		}
		root->left = build_bst(pre_order, low+1, j-1);
		root->right = build_bst(pre_order, j, high);
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

void postorder_traversal(node *root)
{
	if(root == NULL)
		return;
	postorder_traversal(root->left);
	postorder_traversal(root->right);
	printf("%d ", root->data);
}

void inorder_traversal(node *root)
{
	if(root == NULL)
		return;
	inorder_traversal(root->left);
	printf("%d ", root->data);
	inorder_traversal(root->right);
}

node *search(node *root, int key)
{
	if(root == NULL || root->data == key)
		return root;
	
	if(key < root->data)
		return search(root->left, key);
	
	if(key > root->data)
		return search(root->right, key);
}



int main()
{
	int n,i,s;
	printf("Enter the number of elements: ");
	scanf("%d", &n);	

	int pre_order[n];
	printf("Enter the elements in preorder: ");
	for(i=0; i<n; i++)	
		scanf("%d", &pre_order[i]);

	node* bst = build_bst(pre_order, 0, n-1);
	printf("Preorder traversal: ");
	preorder_traversal(bst);
	printf("\nPostorder traversal: ");
	postorder_traversal(bst);
	printf("\nInorder traversal: ");
	inorder_traversal(bst);
	printf("\n");

	printf("Enter the elemrnt to search: ");
	scanf("%d", &s);
	node *p = search(bst, s);
	if(p == NULL)
		printf("Element not found!\n");
	else
		printf("Element found at %p\n", p);
	return 0;
}
