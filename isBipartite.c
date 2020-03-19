#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int vertex;
	struct node *next;
} node; 

typedef struct queue_node
{
	int data;
	struct queue_node *next; 
} queue_node; 

typedef struct queue
{
	queue_node *front;
	queue_node *rear;
} queue;

queue *init()
{
	queue *Q = (queue *)malloc(sizeof(queue));
	Q->front = NULL;
	Q->rear = NULL;
	return Q; 
}

int isEmpty(queue *Q)
{
	return (Q->front==NULL && Q->rear==NULL);
}

queue *enqueue(queue *Q, int data)
{
	queue_node *new_node = NULL;
	new_node = (queue_node*)malloc(sizeof(queue_node));
	new_node->data = data; 
	new_node->next = NULL; 
	
	if(isEmpty(Q))
	{
		Q->front = new_node;
		Q->rear = new_node;
		return Q; 
	}
	
	Q->rear->next = new_node; 
	Q->rear = new_node; 
	return Q;
}

queue *dequeue(queue *Q)
{
	if(isEmpty(Q))
	{
		printf("Queue is Empty\n");
		return Q;
	}
//	printf("%d ", Q->front->data);
	queue_node *del_node = Q->front;
	Q->front = Q->front->next; 
	
	if(Q->rear == del_node)
		Q->rear = NULL; 
		
	free(del_node);
	return Q;
}

void print_queue(queue *Q)
{
	if(isEmpty(Q))
		return ;
	queue_node *e;
	for (e = Q->front; e != NULL ; e = e->next)
	printf("%4d", e->data);
}

node *insert(node *head, int vertex)
{
	node *new_node = (node *)malloc(sizeof(node));
	new_node->vertex = vertex; 
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
	printf("\n\n");
	printf("----------------------------\n");
	for(int i=0; i<nv; i++)
	{
		printf("vertex %d -> ", i);
		node *p = heads[i]; 
		while(p != NULL)
		{
			printf("%d ", p->vertex);
			p = p->next;
		}
		printf("\n");
	}
	printf("----------------------------\n");
}

int main()
{
	int nv, ne, start, end;
	printf("Enter the number of vertices: ");
	scanf("%d", &nv);
	printf("Enter the number of edges: ");
	scanf("%d", &ne);
	
	node *heads[nv]; 
	for(int i=0; i<nv; i++)
		heads[i] = NULL; 
	
	printf("Enter start and end vertex of edges\n");
	for(int i=0; i<ne; i++)
	{
		printf("Edge %d: ", i+1);
		scanf("%d %d", &start, &end);
		
		heads[start] = insert(heads[start], end);
		heads[end] = insert(heads[end], start);
	}	
	
//	print_graph(heads, nv);

	int entry_point; 
	printf("Enter entry point: ");
	scanf("%d", &entry_point);
	
	queue *Q = init(); 
	
	int visited[nv]; 
	for(int i=0; i<nv; i++)
		visited[i] = 0; 
		
	Q = enqueue(Q, entry_point);
	visited[entry_point] = 1;
	
	int t;
	node *m; 
	
	int colour[nv];
	for(int i=0; i<nv; i++)
		colour[i] = 0; 
	
	colour[entry_point] = 1;
	int pc; 
	
	while(!isEmpty(Q))
	{
		t = Q->front->data; 
		m = heads[t]; 
		
		pc = colour[t];
		
		while(m != NULL)
		{
			if(visited[m->vertex] != 1)
			{
				Q = enqueue(Q, m->vertex);
				visited[m->vertex] = 1;
				if(pc==1)
					colour[m->vertex] = 2; 
				if(pc==2)
					colour[m->vertex] = 1; 
			}	
			else if(pc == colour[m->vertex])
			{
				printf("Not a bipartite graph\n");
				return 0;
			}
			m = m->next;
		}
		Q = dequeue(Q);
	}
	printf("It is a bipartite graph\n");
	printf("\n");
	return 0;
}

