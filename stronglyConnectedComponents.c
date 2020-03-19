#include<stdio.h>
#include<stdlib.h>

int TIME = 0;

typedef struct graph_node 
{
    int vertex; 
    struct graph_node *parent; 
    int visited; 
    int disc_time;
    int finish_time; 
} graph_node; 

typedef struct node 
{
    int vertex;
    struct node *next; 
} node;

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
//	printf("\n");
//	printf("----------------------------\n");
	printf("Graph Adjacency list: \n");
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

// Defining topo_sort node globally 
node *final_time_sort = NULL;

node *topo_insert(int vertex)
{
    if(final_time_sort == NULL)
    {
        node *head = (node *)malloc(sizeof(node));
        head->vertex = vertex;
        head->next = NULL;
        return head;
    }

    node *head = (node *)malloc(sizeof(node));
    head->vertex = vertex;
    head->next = final_time_sort; 
    return head;
}

void DFS_VISIT(node *heads[], graph_node **vertex, int u)
{
	TIME += 1;
	vertex[u]->disc_time = TIME;
	vertex[u]->visited = 1; 
	
	printf("%d ", u);
	
	node *m = heads[u];
	while(m != NULL)
	{
		if(vertex[m->vertex]->visited == 0)
		{
			vertex[m->vertex]->parent = vertex[u]; 
			DFS_VISIT(heads, vertex, m->vertex);
		}
		
		m = m->next;
	}
	
	TIME += 1;
	vertex[u]->finish_time = TIME;
	final_time_sort = topo_insert(u);
}

graph_node **DFS(node *heads[], int nv, int entry_point)
{
	printf("DFS Traversal: ");
	graph_node **vertex = malloc(nv*sizeof(graph_node *)); 
    for(int i=0; i<nv; i++)
    {
        vertex[i] = (graph_node *) malloc(sizeof(graph_node));
        vertex[i]->parent = NULL; 
        vertex[i]->visited = 0; 
        vertex[i]->vertex = i;
        vertex[i]->disc_time = -1;
        vertex[i]->finish_time = -1; 
    }
    
    TIME = 0; 
    for(int i=0; i<nv; i++)
    {
    	if(vertex[i]->visited == 0)
    		DFS_VISIT(heads, vertex, i);
    } 
    
    printf("\n");
    
	return vertex;
}

node **Transpose_graph(node *heads[], int nv)
{
	node **transpose = (node **) malloc(nv*sizeof(node *)); 
	node *t; 
	
	for(int i=0; i<nv; i++)
		transpose[i] = NULL;
		
	for(int i=0; i<nv; i++)
	{
		t = heads[i]; 
		while(t != NULL)
		{
//			printf("%d ", t->vertex);
			transpose[t->vertex] = insert(transpose[t->vertex], i);
			t = t->next; 
		}
//		printf("\n");
	}

//	print_graph(transpose, nv);
	return transpose;
}

void DFS_util(int vertex, int visited[], int nv, node **transpose)
{
	visited[vertex] = 1; 
	printf("%d ", vertex);
	
	node *t = transpose[vertex];
	
	while(t != NULL)
	{
		if(visited[t->vertex] == 0)
			DFS_util(t->vertex, visited, nv, transpose);
		t = t->next;
	}
}

int main()
{
	int nv, ne, start, end;
    printf("Enter the no. of vertices: ");
    scanf("%d", &nv);

    printf("Enter the no. of edges: ");
    scanf("%d", &ne);

    node *heads[nv]; 
    for(int i=0; i<nv; i++)
        heads[i] = NULL;

    printf("Enter the start and end vertices of edges\n");
    for(int i=0; i<ne; i++)
    {
        printf("Edge %d: ", i+1);

        scanf("%d %d", &start, &end);

        heads[start] = insert(heads[start], end);
//        heads[end] = insert(heads[end], start);
    }

//    print_graph(heads, nv);
    
    int entry_point = 0; 
    /*
	printf("Enter the entry point: ");
	scanf("%d", &entry_point);
	*/
	
	graph_node **dfs_vertex = DFS(heads, nv, entry_point);

	node **transpose = Transpose_graph(heads, nv);
	
	/*
	printf("Transpose graph: \n");
	print_graph(transpose, nv);
	
	node *t = final_time_sort; 
	printf("Final time sort: ");
	while(t != NULL)
	{
		printf("%d ", t->vertex);
		t = t->next;
	}
	printf("\n");
	*/
	
	int visited[nv]; 
	for(int i=0; i<nv; i++)
		visited[i] = 0; 
	
	int num_scc = 0;
	printf("\nStrongly Connected Components: \n");
	node *t = final_time_sort;
	while(t != NULL)
	{
		if(visited[t->vertex] == 0)
		{
			num_scc++;
			DFS_util(t->vertex, visited, nv, transpose);
			printf("\n");
		}	
		t = t->next;
	}
	printf("The number of strongly connected components are %d.\n", num_scc);
	
	return 0;
}
