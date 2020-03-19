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
	printf("\n");
	printf("----------------------------\n");
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
node *topo_sort = NULL;

node *topo_insert(int vertex)
{
    if(topo_sort == NULL)
    {
        node *head = (node *)malloc(sizeof(node));
        head->vertex = vertex;
        head->next = NULL;
        return head;
    }

    node *head = (node *)malloc(sizeof(node));
    head->vertex = vertex;
    head->next = topo_sort; 
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
    topo_sort= topo_insert(u);
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

    print_graph(heads, nv);
    
    int entry_point = 0; 
    /*
	printf("Enter the entry point: ");
	scanf("%d", &entry_point);
    */
	
	graph_node **dfs_vertex = DFS(heads, nv, entry_point);
 
    printf("Topological sort: ");
    node *temp = topo_sort;  
    while(temp != NULL)
    {
        printf("%d ", temp->vertex);
        temp = temp->next; 
    }
    printf("\n");
    return 0;
}