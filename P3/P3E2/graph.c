#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#include "graph.h"
#include "queue.h"


# define MAX_NODES 1064
# define MAX_LINE 256

extern int errno ;

enum { NO_FILE_POS_VALUES = 2 };

struct _Graph {
	Node *nodes[MAX_NODES];
	Bool connections[MAX_NODES][MAX_NODES];
	int num_nodes;    
	int num_edges;
};

/********** private functions *****************/
int find_node_index(const Graph * g, int nId1) {
	int i;
	if (!g) return -1;
	
	for(i=0; i < g->num_nodes; i++) {
		if (node_getId (g->nodes[i]) ==  nId1) return i;
	}
   
	/* ID not find   */
   return -1; 
}

int* graph_getConectionsIndex(const Graph * g, int index) {
	int *array = NULL, i, j = 0, size;
	
	if (!g) return NULL;
	if (index < 0 || index >g->num_nodes) return NULL;

	// get memory for the array with the connected nodes index
	size = node_getConnect (g->nodes[index]);
	array = (int *) malloc(sizeof(int) * size);
	if (!array) {
		// print errorr message
		fprintf (stderr, "%s\n", strerror(errno));
		return NULL;
	}
	
	// asigno valores al array con los indices de los nodos conectados
	for(i = 0; i< g->num_nodes; i++) {
		if (g->connections[index][i] == TRUE) {
			array[j] = i;
			j++;
		}
	}
	
	return array;
}
		
// Status insertLast(Stack *s, const void *e);

/*********************************************/

Graph * graph_ini(){
	Graph *g = NULL;
	int i;
	
	g = (Graph *) malloc(sizeof(Graph));
	if (!g) {
		
		fprintf (stderr, "%s\n", strerror(errno));
		return NULL;
	}
	
	g->num_nodes = 0;
	g->num_edges = 0;
	
	for (i=0; i< MAX_NODES; i++)
		g->nodes[i] = NULL;
	
	return g;
}

void graph_destroy(Graph * g) {
	int i;
	
	if (!g) return;
	for(i=0; i< g->num_nodes; i++) {
		node_destroy(g->nodes[i]);
	}

	free (g);
}
 
int graph_getNumberOfNodes(const Graph * g) {
	if (g==NULL) return -1;
	
	return  g->num_nodes; 
}

int graph_getNumberOfEdges(const Graph * g){
	if (g==NULL) return -1;
	
	return g->num_edges;
}
 
Status graph_insertNode(Graph * g, const Node* n) {
	Node *aux;
	int i, id;
	
	if ((g == NULL) || (n == NULL)) {
		fprintf(stderr, "%s\n", strerror(errno));
		return ERROR;
	}
	id = node_getId (n);
	
	if (find_node_index(g, id) != -1) return ERROR;
	aux = node_copy (n);
	if (!aux) return ERROR;
 
	g->nodes[g->num_nodes] = aux;
   
	node_setConnect (aux, 0);
	
	g->num_nodes ++;
   
	for (i = 0; i < g->num_nodes; i++) {
		g->connections[g->num_nodes][i] = FALSE;
		g->connections[i][g->num_nodes] = FALSE;
	}
	
	return OK;
}

Status graph_insertEdge(Graph * g, const int nId1, const int nId2) {
	int from, to, n_from;
	if (!g) return ERROR;
	
	from = find_node_index (g, nId1);
	if (from < 0) return ERROR;
	
	to = find_node_index (g, nId2);
	if (to < 0) return ERROR;

	g->connections[from][to] = TRUE;
	
	n_from = node_getConnect (g->nodes[from]) + 1;
	node_setConnect( g->nodes[from], n_from);
	
	g->num_edges ++ ;
	
	return OK;
}

Node * graph_getNode(const Graph * g, int nId) {
	Node *pn = NULL;
	int index;
	
	if (!g) return NULL;
	
	index = find_node_index (g, nId);
	if (index < 0) return NULL;
	
	pn = node_copy( g->nodes[index]);
	
	return pn;
}
 

Status graph_setNode (Graph *g, const Node *n){
	int index;
	
	if (!g || !n) return ERROR;
	
	index = find_node_index(g, node_getId(n) );
	if (index ==-1) return ERROR;
	
	/* set values */
	node_setName (g->nodes[index], node_getName(n));
	node_setConnect (g->nodes[index], node_getConnect(n));
	
	node_setLabel(g->nodes[index], node_getLabel(n));
	node_setAntecesorId(g->nodes[index], node_getAntecesorId(n));
	
	return OK;
}

Bool graph_areConnected(const Graph * g, const int nId1, const int nId2){
	int index1, index2;
	
	if (!g) return FALSE;
	
	index1 = find_node_index(g, nId1);
	if (index1 < 0) return FALSE;
	
	index2 = find_node_index(g, nId2);
	if (index2 < 0) return FALSE;
			
	return g->connections[index1][index2];
}
 
int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId) {
	int index;
	
	if (!g) return -1;
	
	index = find_node_index(g, fromId);
	if (index < 0) return -1;
	
	return node_getConnect(g->nodes[index]);
}

int *graph_getNodesId (const Graph *g){
	int *array = NULL, i;
	
	if (!g) return NULL;
	
	array = (int*) malloc(sizeof(int) * g->num_nodes);
	if (!array) {
		fprintf (stderr, "%s\n", strerror(errno));
		return NULL;
	}
	
	for(i=0; i< g->num_nodes; i++)
		array[i] = node_getId (g->nodes[i]);
	
	return array;
}

int* graph_getConnectionsFrom (const Graph * g, const int fromId) {
	int *array_index = NULL, index, size, i;
	Node *aux;
	
	if (!g) return NULL;
	
	index = find_node_index(g, fromId);
	if (index < 0) return NULL;
	
	size = node_getConnect (g->nodes[index]);

	array_index = graph_getConectionsIndex (g, index);
	if (!array_index) return NULL;
		
	for (i=0; i < size; i++) {
		aux = g->nodes[ array_index[i] ];
		array_index[i] = node_getId (aux);
	}
  
	return array_index;
}
	

int graph_print(FILE *pf, const Graph * g) {
	int i, j, total, id;
	int *array;
	ssize_t bytes = 0;
	
	if (!pf || !g) return -1;
	
	for(i=0; i< g->num_nodes; i++) {
		fputs("\n", pf);
		bytes = bytes + node_print(pf, g->nodes[i]);
		
		total = node_getConnect (g->nodes[i]);
		id = node_getId( g->nodes[i]);
	 
		array = graph_getConnectionsFrom (g, id);
		if (!array) return -1;
		
		bytes = bytes + fprintf(pf, " >> ");

		for (j=0; j < total; j++)
			bytes = bytes + fprintf(pf, "%d ", array[j]);
	   
		free (array);
	}
	
	if (ferror (pf)) {
		fprintf(stderr, "fprintf failed\n");
	}
	
	return bytes;
}


Status graph_readFromFile (FILE *fin, Graph *g) {
	Node *n;
	char buff[MAX_LINE], name[MAX_LINE];
	int i, nnodes = 0, id1, id2;
	Status flag = ERROR;
   
	// read number of nodes 
	if ( fgets (buff, MAX_LINE, fin) != NULL) 
		if ( sscanf(buff, "%d", &nnodes) != 1) return ERROR;
	
	// init buffer_node
	n = node_ini();
	if (!n) return ERROR; 
	
	// read nodes line by line
	for(i=0; i < nnodes; i++) {    
		if ( fgets(buff, MAX_LINE, fin) != NULL) 
			if (sscanf(buff, "%d %s", &id1, name) != NO_FILE_POS_VALUES) break; 
		
		// set node name and node id
		node_setName (n, name);
		node_setId (n, id1);
		
		// insert node in the graph 
	if ( graph_insertNode (g, n) == ERROR) break;
	}
	
	// Check if all node have been inserted
	if (i < nnodes) {
		node_destroy(n);
		return ERROR;
	}
	
	// read connections line by line and insert it
	while ( fgets(buff, MAX_LINE, fin) ) {
		if ( sscanf(buff, "%d %d", &id1, &id2) == NO_FILE_POS_VALUES )
			if (graph_insertEdge(g, id1, id2) == ERROR) break; 
	}
	
	// check end of file
	if (feof(fin)) flag = OK;
	
	// clean up, free resources
	node_destroy (n);  
	return flag;
}


Node *graph_findDeepSearch (Graph *g, int from_id, int to_id){
	Queue *q = NULL;
	Node *v = NULL;     
	Node *u = NULL;     
	Node *w = NULL;     
	int *w_id = NULL;
	int i, u_id, u_ncon;
	Bool found = FALSE;
	
	if(!g) return NULL;
	
	q = queue_ini(node_destroy, node_copy, node_print);   
  
	v = graph_getNode (g, from_id);  

	queue_insert(q, v);                  
	
	while (queue_isEmpty(q) == FALSE && found == FALSE ) {
		u = queue_extract(q);
		
		if (node_getLabel (u) == WHITE) {
			u_id = node_getId (u);
			
			// updates the node's label
			node_setLabel(u, BLACK);
			graph_setNode(g, u);
			
			// obtains abjacents nodes
			w_id =  graph_getConnectionsFrom(g, u_id);
			u_ncon = node_getConnect(u);
			
			for (i=0; i<u_ncon; i++) {
				w = graph_getNode(g, w_id[i]);   
				if (w_id[i] == to_id) {
					node_setAntecesorId (w, u_id); 
					graph_setNode(g, w);
					found = TRUE;
					break;
				}
				else if (node_getLabel (w) == WHITE) {
					node_setAntecesorId (w, u_id);
					graph_setNode(g, w);
					queue_insert(q, w);         
				}
				node_destroy(w);
				w = NULL;
			}
			
			free (w_id);
			w_id = NULL;
		}
		node_destroy(u);
	}
	node_destroy(v);
	queue_destroy(q);
	return w;
}

// Status insertLast(Stack *s, const void *e) {
// 	Stack *sAux = NULL;
// 	void *ele = NULL;
// 	int i;

// 	sAux = stack_ini(node_destroy, node_copy, node_print);

// 	for(i = 0; i < get_NumberOfElements(s); i++) {
// 		ele = stack_pop(s);
// 		stack_push(sAux, ele);
// 		free(ele);
// 	}

// 	stack_push(s, e);
// 	for(i = 0; i < get_NumberOfElements(sAux); i++) {
// 		ele = stack_pop(sAux);
// 		stack_push(s, ele);
// 		free(ele);
// 	}

// 	stack_destroy(sAux);

// 	return OK;
// }

void graph_printPath (FILE *pf, Graph *g, int id){
	int index, j;
	if (id == -1) return;
	
	// get the antecessor
	index = find_node_index(g, id);
	j = node_getAntecesorId(g->nodes[index]);
	graph_printPath(pf, g, j);
	fprintf(pf, "%d ", id);
}
