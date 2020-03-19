#include<stdio.h> 
#include<stdlib.h> 

#define INF 10000

typedef struct graph_node
{
	int vertex; 
	int key;
	struct graph_node *parent; 	
} graph_node;

void swap(graph_node **x, graph_node **y)
{
	graph_node *temp = *x; 
	*x = *y;
	*y = temp;
}

void moveDown(graph_node **arr, int n, int i)
{
	int smallest = i;
	int l = 2*i + 1;
	int r = 2*i + 2; 
	
	if(l<n && arr[l]->key < arr[smallest]->key)
		smallest = l;
		
	if(r<n && arr[r]->key < arr[smallest]->key)
		smallest = r;
		
	if(smallest != i)
	{
		swap(&arr[i], &arr[smallest]); 
		moveDown(arr, n, i);
	}
}

void moveUp(graph_node **arr, int n, int i)
{

	int p = (i-1)/2;
	if(p >= 0 && arr[i]->key < arr[p]->key)
	{
		swap(&arr[i], &arr[p]); 
		moveUp(arr, n, p);
	}
}

void buildHeap(graph_node *arr[], int n)
{
	int start = (n/2)-1; 
	for(int i=start; i >= 0; i--)
		moveDown(arr, n, i);
}

graph_node *extractMin(graph_node *arr[], int *n)
{
	if(*n <= 0)
	{
		printf("Heap is Empty!\n");
		return NULL;
	}	
	
	graph_node *min = arr[0]; 

	swap(&arr[0], &arr[(*n)-1]);
	// arr[0] = arr[(*n)-1]; 

	(*n)--; 
	moveDown(arr, *n, 0);
	return min;
}

void decreaseKey(graph_node *arr[], int n, int i, int x)
{
	if(x < arr[i]->key)
	{
		arr[i]->key = x;
		moveUp(arr, n, i);
	}
}

int belong(graph_node *arr[], int n, int vertex)
{
	for(int i=0; i<n; i++)
	{
		if(arr[i]->vertex == vertex)
			return 1;
	}
	
	return 0;
}

void printHeap(graph_node **heap, int heapSize)
{
	printf("Heap (vertex, key)-------------------------\n");
	for(int i=0; i<heapSize; i++)
		printf("(%d %d) ", heap[i]->vertex, heap[i]->key); 
	printf("\n\n");
}

typedef struct node
{
    int vertex; 
    int weight; 
    struct node *next;
} node; 

node *insert(node *head, int vertex, int weight)
{
    node *new_node = (node *)malloc(sizeof(node));
	new_node->vertex = vertex; 
    new_node->weight = weight;
	new_node->next = NULL;

    node *a = head; 

    if(head == NULL)
		return new_node;
	else 
	{
		while(a->next != NULL)
			a = a->next;
		a->next = new_node;
	}
	return head;
}

void print_graph(node *heads[], int nv)
{
    printf("----------------------------\n");
	printf("Graph Adjacency list: \n");
	for(int i=0; i<nv; i++)
	{
		printf("vertex %d -> ", i);
		node *p = heads[i]; 
		while(p != NULL)
		{
			printf("%d-%d | ", p->vertex, p->weight);
			p = p->next;
		}
		printf("\n");
	}
	printf("----------------------------\n");
}

int getWeight(node **heads, int u, int v)
{
	node *temp = heads[u]; 
	while(temp->vertex != v)
		temp = temp->next; 
		
	return temp->weight;
}

int getPosition(graph_node **heap, int v, int heapSize)
{
	for(int i=0; i<heapSize; i++)
	{
		if(heap[i]->vertex == v)
			return i;
	}
}

graph_node **prims(node *heads[], int nv)
{	
	graph_node **heap = (graph_node **) malloc(nv*sizeof(graph_node *)); 
	for(int i=0; i<nv; i++)
	{
		heap[i] = (graph_node *) malloc(sizeof(graph_node)); 
		heap[i]->vertex = i; 
		heap[i]->key = INF; 
		heap[i]->parent = NULL;
	}
	
	heap[0]->key = 0; 
	int heapSize = nv; 
	
	while(heapSize != 0)
	{
		/*--------------
		printHeap(heap, heapSize);
		--------------*/

		graph_node *u = extractMin(heap, &heapSize);

		/*--------------
		printf("Minimum: (%d %d)\n", u->vertex, u->key);
		printHeap(heap, heapSize);
		printf("\n");
		--------------*/	

		node *v = heads[u->vertex]; 
		while(v != NULL)
		{
			int v_pos = getPosition(heap, v->vertex, heapSize);

			/*------------
			printf("\n");
			printHeap(heap, heapSize);
			printf("Checking v_pos:\nextracted position: %d for vertex %d\n\n", v_pos, v->vertex);
			------------*/
			if(belong(heap, heapSize, v->vertex) == 1 && getWeight(heads, u->vertex, v->vertex) < heap[v_pos]->key)
			{

				/*-------------
				printHeap(heap, heapSize);
				printf("Decreasing key (%d %d) at position %d\n", heap[v_pos]->vertex, heap[v_pos]->key, v_pos);
				-------------*/

				decreaseKey(heap, heapSize, v_pos, getWeight(heads, u->vertex, v->vertex));

				/*-------------
				printf("After decreasing key: \n");
				printHeap(heap, heapSize);
				-------------*/
			
				v_pos = getPosition(heap, v->vertex, heapSize);

				heap[v_pos]->parent = u;
				/*
				printf("parent child:(%d %d)\n", heap[v_pos]->parent->vertex, heap[v_pos]->vertex);
				printf("%d %d\n", u->vertex, v->vertex);
				*/
			}
			
			v = v->next;
		}
	}
		
	return heap;
}

int main()
{

    int nv, ne, start, end, weight;
    printf("Enter the no. of vertices: ");
    scanf("%d", &nv); 

    printf("Enter the no. of edges: ");
    scanf("%d", &ne);

    node *heads[nv]; 
    for(int i=0; i<nv; i++)
        heads[i] = NULL;

    printf("Enter the start, end and weight of edges\n");
    for(int i=0; i<ne; i++)
    {
        printf("Edge %d: ", i+1);
        scanf("%d %d %d", &start, &end, &weight);

        heads[start] = insert(heads[start], end, weight);
        heads[end] = insert(heads[end], start, weight);
    }
    print_graph(heads, nv); 
    
    graph_node **prim_graph = prims(heads, nv); 

	printf("Minimum Spanning Tree: \n");
    for(int i=0; i<nv; i++)
	{
		if(prim_graph[i]->parent != NULL)
		{
			printf("(%d %d) ", prim_graph[i]->vertex, prim_graph[i]->parent->vertex); 
		}
	}
	printf("\n");
	
	return 0;
}
