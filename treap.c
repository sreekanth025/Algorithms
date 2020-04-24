#include<stdio.h>
#include<stdlib.h>

typedef struct tnode
{
	int key;
	double priority;
	struct tnode *left, *right;
} tnode;

tnode *newNode(int data, double priority)
{
	tnode *new = (tnode *)malloc(sizeof(tnode));
	new -> key = data;
	new -> priority = priority;
	new -> left = NULL;
	new -> right = NULL;

	return new;
}

tnode *rightRotate(tnode *root)
{
	tnode *temp = root->left;
	root->left = temp->right;
	temp->right = root;
	
	return temp;
}

tnode *leftRotate(tnode *root)
{
	tnode *temp = root->right;
	root->right = temp->left;
	temp->left = root;
	
	return temp;
}

tnode *insert(tnode *root, int key, double priority)
{
	if(root == NULL)
		return newNode(key, priority);
	if(key < root->key)
	{
		root->left = insert(root->left, key, priority);
		
		if(root->left->priority > root->priority)
			root = rightRotate(root);

	}
	else if(key > root->key)
	{
		root->right = insert(root->right, key, priority);
		
		if(root->right->priority > root->priority)
			root = leftRotate(root);
	}
	return root;
}

tnode *delete(tnode *root, int key)
{
	if(root == NULL)
	{
		printf("Element %d is not present in the treap\n", key);	
		return NULL;
	}

	if(key < root->key)
		root->left = delete(root->left, key);
	
	else if(key > root->key)
		root->right = delete(root->right, key);

	else if(root->left == NULL)
	{
		tnode *temp = root->right;
		free(root);
		root = temp;
	}

	else if(root->right == NULL)
	{
		tnode *temp = root->left;
		free(root);
		root = temp;
	}
	
	else if (root->left->priority < root->right->priority)
	{
		root = leftRotate(root);
		root->left = delete(root->left, key);
	}
	
	else
	{
		root = rightRotate(root);
		root->right = delete(root->right, key);
	}
	
	return root;
}

void printTreap(tnode *root)
{
	if(root == NULL)
		return ;
	if(root->right == NULL && root->left == NULL)
		printf("(%d, %lf) -> (NULL,-), (NULL,-)\n", root->key, root->priority);
	else if(root->left != NULL && root->right == NULL)
		printf("(%d, %lf) -> (%d, %lf), (NULL,-)\n", root->key, root->priority, root->left->key, root->left->priority);	
	else if(root->left == NULL && root->right != NULL)
		printf("(%d, %lf) -> (NULL,-), (%d, %lf)\n", root->key, root->priority, root->right->key, root->right->priority);
	else
		printf("(%d, %lf) -> (%d, %lf), (%d, %lf)\n", root->key, root->priority, root->left->key, root->left->priority,root->right->key, root->right->priority);	
		
	printTreap(root->left);
	printTreap(root->right);
}

int main()
{
	tnode *root = NULL;

	int n;
	printf("Enter the number of insertions: ");
	scanf("%d", &n);
	
	int k[n];
	double p[n];
	
	printf("Enter the keys and priorities:\n");
	for(int i=0; i<n; i++)
		scanf("%d %lf", &k[i], &p[i]);
		
	for(int i=0; i<n; i++)
	{
		root = insert(root, k[i], p[i]);
		printf("Inserted key %d\n", k[i]);
		printf("Treap after insertion:\n");
		printTreap(root);
		printf("--------------------------------------------------------------\n");
	}
	
	printf("Enter the number of deletions: ");
	scanf("%d", &n);
	int d[n];
	
	printf("Enter the keys to delete: ");
	for(int i=0; i<n; i++)
		scanf("%d", &d[i]);
		
	for(int i=0; i<n; i++)
	{
		printf("Deleting %d\n", d[i]);
		root = delete(root, d[i]);
		printf("Treap after deletion:\n");
		printTreap(root);
		printf("--------------------------------------------------------------\n");
	}
	return 0;
}
