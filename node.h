#ifndef NODE_H_
#define NODE_H_
#include <stdio.h>
#include "types.h"
typedef struct _Node Node;
/* Initialize a node, reserving memory and returning the initialized node if
 * it was done correctly, otherwise return NULL and print the corresponding
 * string to the error in stderror */
Node * node_ini();
/* Free the dynamic memory reserved for a node */
void node_destroy(Node * n);
/* Returns the id of a given node, or -1 in case of error */
int node_getId(const Node * n);
/* Returns a pointer to the name of a given node, or NULL in case of error */
char* node_getName(const Node * n);
/* Returns the number of connections of a given node, or -1 in case of error */
int node_getConnect(const Node * n);
/* Modifies the id of a given node, returns NULL in case of error */
Node * node_setId(Node * n, const int id);
/* Modifies the name of a given node, returns NULL in case of error */
Node * node_setName(Node * n, const char* name);
/* Modifies the number of connections of a given node, returns NULL in case of
error */
Node * node_setConnect(Node * n, const int cn);
/* Compares two nodes by the id and then the name.
 * Returns 0 when both nodes have the same id, a smaller number than
 * 0 when n1 <n2 or one greater than 0 otherwise. */
int node_cmp (const Node * n1, const Node * n2);
/* Reserves memory for a node where it copies the data from the node src.
 * Returns the address of the copied node if everything went well, or NULL
otherwise */
Node * node_copy(const Node * src);
/* Prints in pf the data of a node with the format: [id, name, nConnect]
 * Returns the number of characters that have been written successfully.
 * Checks if there have been errors in the Output flow, in that case prints
 * an error message in stderror*/
int node_print(FILE *pf, const Node * n);
#endif /* NODE_H_ */