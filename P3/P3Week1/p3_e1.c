#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "graph.h"
#include "queue.h"

int mainCleanUp (int ret_value, Graph *gc, Node *out, Node *in, FILE *f) {
    node_destroy(out);
    node_destroy(in);
    graph_destroy (gc);   
    fclose (f);
    exit (ret_value);
}

int main(int argc, char **argv) {
	FILE *f = NULL;
    Graph *g = NULL;
    Status flag;
    Node *out = NULL, *in = NULL;
    int from_id, to_id;

    if (argc != 4) 
    	exit(EXIT_FAILURE); 
    
    f = fopen(argv[1], "r");

    if (!f) {
        fprintf (stderr, "%s", strerror(errno));
        return (EXIT_FAILURE);
    }
    
    g = graph_ini();
    if (!g) 
    	mainCleanUp(EXIT_FAILURE, g, out, in, f);
    
    // read file
    flag = graph_readFromFile(f, g);

    if(flag == ERROR) 
    	mainCleanUp(EXIT_FAILURE, g, out, in, f);
    
    
    // prints graph
    if (graph_print (stdout, g) == -1)  
    	mainCleanUp (EXIT_FAILURE, g, out, in, f);
    
    from_id = atoi (argv[2]);
    to_id = atoi (argv[3]);
    
   out = graph_findDeepSearch(g, from_id, to_id);

    if (out == NULL)
        fprintf(stdout,"\n\n It is not possible to find a path.");
    else {
        fprintf(stdout,"\n\n It is possible to find a path from ");
        in = graph_getNode(g,from_id);

        node_print(stdout, in);
        fprintf(stdout, " to ");
        node_print(stdout, out);
        
        // Prints path
        fprintf(stdout, "\nPath:\n");
        graph_printPath(stdout, g, to_id);
        fprintf(stdout, "\n");
    }
    
    mainCleanUp(EXIT_SUCCESS, g, out, in, f);

    return EXIT_SUCCESS;
}

