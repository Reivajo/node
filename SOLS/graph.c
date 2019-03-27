/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


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

/* Declaracion de funciones privadas */
int find_node_index(const Graph *, int);
int* graph_getConectionsIndex(const Graph *, int);


// #####  Private functions  ##### 
int find_node_index(const Graph * g, int nId1) {
    int i;
    if (!g) return -1;
    
    for(i=0; i < g->num_nodes; i++) {
        if (node_getId (g->nodes[i]) ==  nId1) return i;
    }
   
    // ID not find
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
        
// ###### Public Interface ###########

Graph * graph_ini(){
    Graph *pg = NULL;
    int i;
    
    pg = (Graph *) malloc(sizeof(Graph));
    if (!pg) {
        // imprime mensaje de error
        fprintf (stderr, "%s\n", strerror(errno));
        return NULL;
    }
    
    pg->num_nodes = 0;
    pg->num_edges = 0;
    
    // discutir
    for (i=0; i< MAX_NODES; i++)
        pg->nodes[i] = NULL;
    
    return pg;
}

void graph_destroy(Graph * g) {
    int i;
    
    if (!g) return;
    
    // libera los nodos del grafo
    for(i=0; i< g->num_nodes; i++) {
        node_destroy(g->nodes[i]);
    }
    
    // libera grafo
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
    int i, index, id;
    
    if (!g || !n) return ERROR; 
    
    // obtengo el id del nodo
    id = node_getId (n);
    
    // busco si en el grafo hay ya un nodo con el mismo id
    index = find_node_index(g, id);
    if (index >= 0) return ERROR;
    
    // hago una copia del nodo
    aux = node_copy (n);
    if (!aux) return ERROR;
    
    // asigno el nodo al array de nodos 
    g->nodes[g->num_nodes] = aux;
    
    // asigno a 0 el número de conexiones del nodo
    node_setConnect (aux, 0);
    
    // aumento el número de nodos del grafo
    g->num_nodes ++;
    
    // asigno las conexiones del nodo en la matriz  de conexiones a FALSE
    for (i = 0; i < g->num_nodes; i++) {
        g->connections[g->num_nodes][i] = FALSE;
        g->connections[i][g->num_nodes] = FALSE;
    }
    
    return OK;
}

Status graph_insertEdge(Graph * g, const int nId1, const int nId2) {
    int from, to, n_from;
    if (!g) return ERROR;
    
    // obtengo ,los índices de los nodes
    from = find_node_index (g, nId1);
    if (from < 0) return ERROR;
    
    to = find_node_index (g, nId2);
    if (to < 0) return ERROR;
    
    // creo la conexión
    g->connections[from][to] = TRUE;
    
    // actualizo el total de aristas del nodo
    n_from = node_getConnect (g->nodes[from]) + 1;
    node_setConnect( g->nodes[from], n_from);
    
    // actualizo el total de aristas del grafo
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
        // imprime mensaje de error
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

    // array con los indices de los nodos conectados 
    array_index = graph_getConectionsIndex (g, index);
    if (!array_index) return NULL;
        
    /* para cada uno de ellos obtengo su Id y sobr-escribo el valor del índice 
     * por su Id */
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
        // imprime el i-esimo nodo
        fputs("\n", pf);
        bytes = bytes + node_print(pf, g->nodes[i]);
        
        // imprime las conexiones del i-esimo nodo
        total = node_getConnect (g->nodes[i]);
        id = node_getId( g->nodes[i]);
     
        array = graph_getConnectionsFrom (g, id);
        if (!array) return -1;
        
        for (j=0; j < total; j++)
            bytes = bytes + fprintf(pf, "%d ", array[j]);
        
        // libera recursos
        free (array);
    }
    
    // comprueba si ha habido errores en el flujo de salida
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
    Queue *s = NULL;
    Node *v = NULL;     // vertex where the search starts
    Node *u = NULL;     // vertex extracted from the queue
    Node *w = NULL;     // neighbour of u
    int *w_id = NULL;   // array with the w id's  
    int i, u_id, u_ncon;
    Bool encontrado = FALSE;
    
    if(!g) return NULL;
    
    s = queue_ini(node_destroy, node_copy, node_print);   // CdE
  
    v = graph_getNode (g, from_id);     
    queue_insert (s,v);  //CdE
    
    while (queue_isEmpty(s) == FALSE && encontrado == FALSE ) {
        u = queue_extract(s);
        
        if (node_getLabel (u) == BLANCO) {
            u_id = node_getId (u);
            
            // actualiza la etiqueta del nodo
            node_setLabel(u, NEGRO);
            graph_setNode(g, u);
            
            // obtiene los id de los nodos adyacentes
            w_id =  graph_getConnectionsFrom(g, u_id);
            u_ncon = node_getConnect(u);
            
            // procesa los nodos adyacentes
            for (i=0; i<u_ncon; i++) {
                w = graph_getNode(g, w_id[i]);   // CdE
                if (w_id[i] == to_id) {
                    node_setAntecesorId (w, u_id); 
                    graph_setNode(g, w);
                    encontrado = TRUE;
                    break;
                }
                else if (node_getLabel (w) == BLANCO) {
                    node_setAntecesorId (w, u_id);
                    graph_setNode(g, w);
                    queue_insert (s, w);         // CdE  
                }
                node_destroy(w);
                w = NULL;
            }
            // libera el array de id vecinos
            free (w_id);
            w_id = NULL;
        }
        node_destroy(u);
    }
    node_destroy(v);
    queue_destroy(s);
    return w;
}

void graph_printPath (FILE *pf, Graph *g, int id){
    int index, j;
    if (id == -1) return;
    
    // get the antecessor
    index = find_node_index(g, id);
    j = node_getAntecesorId(g->nodes[index]);
    
    graph_printPath(pf, g, j);
    fprintf(pf, "%d ", j);
}

