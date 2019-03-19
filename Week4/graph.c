#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "graph.h"
#define MAX_NUM_NODES 4096
#define MAX_LINE 256

struct _Graph {
    Node *node[MAX_NUM_NODES];
    Bool matrix[MAX_NUM_NODES][MAX_NUM_NODES]; /*[row][column]*/
    int num_edges;
    int num_nodes;	
};
enum { NO_FILE_POS_VALUES = 2 };

/********** private functions *****************/
int find_node_index(const Graph * g, int nId1) {    
	int i;    
	if (!g) return -1;

	for(i=0; i < g->num_nodes; i++) {        

		if (node_getId(g->node[i]) ==  nId1) 
			return i;    

	} /* ID not find   */
	return -1; 
} 

int* graph_getConectionsIndex(const Graph * g, int index) {    
	int *array = NULL;
	int i, j=0, size;

	if (!g) return NULL;    

	if (index < 0 || index >g->num_nodes) return NULL;    

	/* get memory for the array with the connected nodes index */

	size = node_getConnect (g->node[index]);    
	array = (int*) malloc(sizeof(int) * size);    

	if (!array) {        
	/* print errorr message  */
	fprintf (stderr, "%s\n", strerror(errno));        
	return NULL;    
	}        

    /* assign values to the array with the indexes of the connected nodes  */  
	for(i = 0; i< g->num_nodes; i++) {        
		if (g->matrix[index][i] == TRUE) {            
			array[j] = i;            
			j++;        
		}    
	}        
	return array; 
}

/*********************************************/


Graph * graph_ini() {
    int i, j;
    Graph *g = NULL;
    g = (Graph*) malloc(sizeof (Graph));
    if (!g) {
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    g->num_edges = 0;
    g->num_nodes = 0;
    for (i = 0; i < MAX_NUM_NODES; i++) {
        g->node[i] = NULL;
    }
    for (i = 0; i < MAX_NUM_NODES; i++) {
        for (j = 0; j < MAX_NUM_NODES; j++) {
            g->matrix[i][j] = 0;
        }
    }
    return g;
}

void graph_destroy(Graph * g) {
    int i;
    for (i = 0; i < g->num_nodes; i++) {
        node_destroy(g->node[i]);
    }
    free(g);
}

Status graph_insertNode(Graph * g, const Node* n) {
    
    int id;
    if ((g == NULL) || (n == NULL)) {
        fprintf(stderr, "%s\n", strerror(errno));
        return ERROR;
    }
    id = node_getId(n);
    if (find_node_index(g, id) != -1) return ERROR;
    
    g->node[g->num_nodes]=node_copy(n);
    	

    g->num_nodes++;
    return OK;

}

Status graph_insertEdge(Graph * g, const int nId1, const int nId2){
	int index1 = find_node_index(g, nId1);
	int index2 = find_node_index(g, nId2);
	int num_connections=0;

	if(index1 < 0 || index2 < 0)
		return ERROR;

	g->matrix[index1][index2] = TRUE;
	num_connections=node_getConnect(g->node[index1]);
	node_setConnect(g->node[index1],num_connections+1);
	return OK;
}

Node *graph_getNode (const Graph *g, int nId){
	int index = find_node_index(g, nId);
	if(index == -1)
		return NULL;
	return g->node[index]; 
}

Status graph_setNode (Graph *g, const Node *n){

	int id;
	int index;

	if ((g == NULL) || (n == NULL)) {
        fprintf(stderr, "%s\n", strerror(errno));
        return ERROR;
    }

	id=node_getId(n);
	index=find_node_index(g,id);

	if((id== -1) || (index== -1)){

		return ERROR;
	}
	node_setName(g->node[index], node_getName(n));
	node_setConnect(g->node[index], node_getConnect(n));

	node_setLabel(g->nodes[index], node_getLabel(n));
    node_setAntecesorId(g->nodes[index], node_getAntecesorId(n));

	return OK;
}

int * graph_getNodesId (const Graph * g){

	int *ids, i;

	ids = (int*)malloc(g->num_nodes*sizeof(int));

	if(ids==NULL)
		return NULL;
	
	for(i = 0; i < g->num_nodes; i++)
		ids[i] = node_getId(g->node[i]);


	return ids;

}

int graph_getNumberOfNodes(const Graph * g){

	if(!g){
		return -1;
	}

	return g->num_nodes;
}

int graph_getNumberOfEdges(const Graph * g){


	if(!g){
		return -1;
	}

	return g->num_edges;
}

Bool graph_areConnected(const Graph * g, const int nId1, const int nId2){

	int index1,index2;

	index1=find_node_index(g,nId1);
	index2=find_node_index(g,nId2);

	return g->matrix[index1][index2];
}

int* graph_getConnectionsFrom(const Graph * g, const int fromId){
	
	int index,tam,i;
	int *var;
	Node *node;
	index=find_node_index(g,fromId);
	tam=node_getConnect(g->node[index]);


	if(!(var=graph_getConectionsIndex(g,index))){
		return NULL;
	}
	for(i=0;i<=tam;i++){
		node=g->node[var[i]];
		var[i]=node_getId(node);
	}
	return var;
}



int graph_print(FILE *pf, const Graph * g){
   if(!pf || !g){
     fprintf(stderr,"%s\n",strerror(errno));
         return -1;
   }
   int i,j,num_char=0;
   int *array;
   for(i=0;i<g->num_nodes;i++){
     num_char+=node_print(pf, g->node[i]);
     for(j=0;j>node_getConnect(g->node[i]);j++){
       array=graph_getConectionsIndex(g,i);
       num_char+=fprintf(pf,"%d",array[j]);
     }
     fprintf(pf,"\n");
   }
   free (array);
   return num_char;
}

Status graph_readFromFile (FILE *fin, Graph *g) {    
	Node *n;    
	char buff[MAX_LINE], name[MAX_LINE];    
	int i, nnodes = 0, id1, id2;    
	Status flag = ERROR;       
	/* read number of nodes     */
	if ( fgets (buff, MAX_LINE, fin) != NULL)         
		if ( sscanf(buff, "%d", &nnodes) != 1) return ERROR;        
	/* init buffer_node    */
	n = node_ini();    
	if (!n) return ERROR;         
	/* read nodes line by line  */  
	for(i=0; i < nnodes; i++) {            
		if ( fgets(buff, MAX_LINE, fin) != NULL)             
			if (sscanf(buff, "%d %s", &id1, name) != NO_FILE_POS_VALUES) break;  

		/* set node name and node id   */     
		node_setName (n, name);        
		node_setId (n, id1); 

		/* insert node in the graph */
	  if ( graph_insertNode (g, n) == ERROR) break;    
	}	  
	/* Check if all node have been inserted    */
	if (i < nnodes) {        
		node_destroy(n);        
		return ERROR;    
	}  

	/* read connections line by line and insert it */

	while ( fgets(buff, MAX_LINE, fin) ) {        
		if ( sscanf(buff, "%d %d", &id1, &id2) == NO_FILE_POS_VALUES )            
			if (graph_insertEdge(g, id1, id2) == ERROR) break;     
	}        

	/* check end of file    */
	if (feof(fin)) flag = OK;        
	/* clean up, free resources  */  
	node_destroy (n);      
	return flag; 
}
