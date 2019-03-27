/*
 * main.c
 *
 *  Created on: 24 mar. 2019
 *      Author: rosa
 */


#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "graph.h"

extern int errno ;

int mainCleanUp(int ret_value, Graph *, Node *, Node *, FILE *);

int mainCleanUp (int ret_value, Graph *gc, Node *out, Node *in, FILE *pf) {
    if (out) node_destroy(out);
    if (in) node_destroy(in);
    if (gc) graph_destroy (gc);   
    fclose (pf);
    exit (ret_value);
}

int main (int argc, char **argv) {
    FILE *pf = NULL;
    Graph *g = NULL;
    Status flag;
    Node *out = NULL, *in = NULL;
    int from_id, to_id;
    
    if (argc != 4) exit(EXIT_FAILURE); 
    
    pf = fopen(argv[1], "r");
    //pf = fopen("g2_s.txt", "r");
    if (!pf) {
        fprintf (stderr, "%s", strerror(errno));
        return (EXIT_FAILURE);
    }
    
    g = graph_ini();
    if (!g) mainCleanUp (EXIT_FAILURE, g, out, in, pf);
    
    // lee el fichero
    flag = graph_readFromFile (pf, g);
    if (flag == ERROR) mainCleanUp (EXIT_FAILURE, g, out, in, pf);
    
    
    // imprime el grafo
    if (graph_print (stdout, g) == -1)  mainCleanUp (EXIT_FAILURE, g, out, in, pf);
    
    from_id = atoi (argv[2]);
    to_id = atoi (argv[3]);
    
    out = graph_findDeepSearch(g, from_id, to_id);
    if (out == NULL) {
        fprintf(stdout,"\nNo Es posible encontrar un camino");
    }
    else {
        fprintf(stdout,"\n Es posible encontrar un camino de ");
        in = graph_getNode(g,from_id);
        node_print(stdout, in);        
        fprintf(stdout," a ");    
        node_print(stdout, out);
        
       // Imprime el camino
       // fprintf(stdout, "\nImprime el camino\n");
       // graph_printPath(stdout, g, to_id);
    }
    
    // libera recursos
    mainCleanUp (EXIT_SUCCESS, g, out, in, pf);
    return EXIT_SUCCESS;
}

