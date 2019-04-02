#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include "types.h"
typedef struct _Graph Graph;
/* Initializes a graph, reserving memory and returns the graph address
* if it has done it correctly, otherwise it returns NULL and prints the string
* associated with error in stderror */
Graph * graph_ini();
/* Frees the dynamic memory reserved for the graph */
void graph_destroy(Graph * g);
/* Adds a node to the graph (reserving new memory for that node) only
* when there was no other node with the same id in the graph. It updates
* the necessary graph’s attributes. Returns OK or ERROR. */
Status graph_insertNode(Graph * g, const Node* n);
/* Adds an edge between the nodes of id "nId1" and "nId2".
* Updates the necessary graph’s attributes.
* Returns OK or ERROR. */
Status graph_insertEdge(Graph * g, const int nId1, const int nId2);
/* Returns a copy of the node of id "nId"*/
Node *graph_getNode (const Graph *g, int nId);
/* Actualize the graph node with the same id */
Status graph_setNode (Graph *g, const Node *n);
/* Returns the address of an array with the ids of all nodes in the graph.
* Reserves memory for the array. */
int * graph_getNodesId (const Graph * g);
/* Returns the number of nodes in the graph. -1 if there have been errors */
int graph_getNumberOfNodes(const Graph * g);
/* Returns the number of edges of the graph. -1 if there have been errors */
int graph_getNumberOfEdges(const Graph * g);
/* Determines if two nodes are connected */
Bool graph_areConnected(const Graph * g, const int nId1, const int nId2);
/* Returns the number of connections from the id node fromId */
int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId);
/* Returns the address of an array with the ids of all nodes in the graph.
* Reserves memory for the array.*/
int* graph_getConnectionsFrom(const Graph * g, const int fromId);
/* Prints in the flow pf the data of a graph, returning the number of printed
characters.
* Checks if there have been errors in the Output flow. If so, prints Error
* message Error in stderror and returns the value -1.
 * * The format to be followed is: print a line by node with the information
associated with the node and
* the id of their connections. The Output for the graph of the EXERCISE 2.3 of
*part 1 is:
* [1, a, 2] 2 3
* [2, b, 2] 1 3
* [3, c, 2]] 1 2 */
int graph_print(FILE *pf, const Graph * g);
/* Read from the stream fin the graph information */
Status graph_readFromFile (FILE *fin, Graph *g);
Node *graph_findDeepSearch (Graph *g, int from, int to);
void graph_printPath (FILE *pf, Graph *g, int id);
#endif /* GRAPH_H */
