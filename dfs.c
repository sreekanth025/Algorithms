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
    
    int entry_point; 
	printf("Enter the entry point: ");
	scanf("%d", &entry_point);
	
	graph_node **dfs_vertex = DFS(heads, nv, entry_point);
	
	for(int i=0; i<nv; i++)
	{
		printf("%d (%d %d)\n", i, dfs_vertex[i]->disc_time, dfs_vertex[i]->finish_time);
	}
	
	for(int u=0; u<nv; u++)
	{
		node *m = heads[u]; 
		while(m != NULL)
		{
			int v = m->vertex; 
			int ust = dfs_vertex[u]->disc_time;
			int uft = dfs_vertex[u]->finish_time;
			int vst = dfs_vertex[v]->disc_time;
			int vft = dfs_vertex[v]->finish_time;
			
			if(vst<ust && ust<uft && uft<vft)
				printf("%d %d Back edge\n", u, v);

			else if(vst<vft && vft<ust && ust<uft)
				printf("%d %d Cross edge\n", u, v);\
				
			else
			{
				graph_node *p = dfs_vertex[v]->parent;
				if(p->vertex != u)
					printf("%d %d Forward edge\n", u, v);
				else
					printf("%d %d Tree edge\n", u, v);
			}
			m = m->next;
		}
	}
	
	for(int u=0; u<nv; u++)
	{
		node *m = heads[u]; 
		while(m != NULL)
		{
			int v = m->vertex; 
			int ust = dfs_vertex[u]->disc_time;
			int uft = dfs_vertex[u]->finish_time;
			int vst = dfs_vertex[v]->disc_time;
			int vft = dfs_vertex[v]->finish_time;
			
			if(vst<ust && ust<uft && uft<vft)
			{
				printf("Cycle: %d %d ", v, u);
				
				graph_node *p = dfs_vertex[u]->parent; 
				while(p->vertex != v)
				{
					printf("%d ", p->vertex);
					p = p->parent; 
				}
				printf("%d ", v);
				printf("\n");
			}
			
			m = m->next;
		}
	}
	return 0;
}
