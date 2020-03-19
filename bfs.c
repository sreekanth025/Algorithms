#include<stdio.h>
#include<stdlib.h>

#define INF 10000 

typedef struct graph_node 
{
    int vertex; 
    struct graph_node *parent; 
    int distance; 
    int visited; 
} graph_node; 

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
	printf("%d ", Q->front->data);
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
	printf("\n");
	printf("----------------------------\n");
    printf("Graph Adjacency List: \n"); 
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

graph_node **BFS(node *heads[], int nv, int entry_point)
{
    graph_node **vertex = malloc(nv*sizeof(graph_node *)); 
    for(int i=0; i<nv; i++)
    {
        vertex[i] = (graph_node *) malloc(sizeof(graph_node));
        vertex[i]->parent = NULL; 
        vertex[i]->distance = INF; 
        vertex[i]->visited = 0;
        vertex[i]->vertex = i; 
    }

    vertex[entry_point]->parent = NULL;
    vertex[entry_point]->distance = 0; 
    vertex[entry_point]->visited = 1; 

    queue *Q = init();
    Q = enqueue(Q, entry_point);
    
    printf("BFS Traversal: ");

    while(!isEmpty(Q))
    {
        int parent = Q->front->data; 
        Q = dequeue(Q); 

        node *m = heads[parent]; 
        while(m != NULL)
        {
            if(vertex[m->vertex]->visited == 0)
            {
                vertex[m->vertex]->parent = vertex[parent];
                vertex[m->vertex]->distance = vertex[parent]->distance + 1; 
                vertex[m->vertex]->visited = 1;
                Q = enqueue(Q, m->vertex); 
            }

            m = m->next;
        }
    }

    printf("\n");
    return vertex;
}

void print_path(graph_node **bfs_vertex, int source, int destination)
{
    if(destination == source)
        printf("%d ", source);
    
    else if(bfs_vertex[destination]->parent == NULL)
        printf("There is no path from %d to %d", source, destination);
    
    else 
    {
        print_path(bfs_vertex, source, bfs_vertex[destination]->parent->vertex);
        printf("%d ", destination);
    }
}

void print_shortest_path(graph_node **bfs_vertex, int nv, int source)
{
    printf("Shortest paths from source %d: \n",source);
    for(int i=0; i<nv; i++)
    {
        printf("%d: ", i);
        print_path(bfs_vertex, source, i); 
        printf("\n"); 
    }
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

    print_graph(heads, nv); 

    int entry_point; 
	printf("Enter entry point: ");
	scanf("%d", &entry_point); 

    graph_node **bfs_vertex = BFS(heads, nv, entry_point); 
    print_shortest_path(bfs_vertex, nv, entry_point); 
    return 0; 
}