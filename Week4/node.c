
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "node.h"
#include "types.h"
#include "graph.h"
#include "stack_fp.h"

#define NAME_L 64

struct _Node {
	char name[100];
	int id;
	int nConnect;
	Label etq;
	int antecessor_id;
};

/* Initialize a node, reserving memory and returning the initialized node if
* it was done correctly, otherwise return NULL and print the corresponding
* string to the error in stderror */
Node *node_ini(){
	Node *n;
	n=(Node*)calloc(1,sizeof(Node));
	if(!n)
		fprintf (stderr, "%s\n", strerror(errno));
	n->etq = WHITE;
	n->antecessor_id = -1;

	return n;
}

/* Free the dynamic memory reserved for a node */
void node_destroy(Node *n){
	if(!n){
		fprintf (stderr, "%s\n", strerror(errno));
	}
	free(n);
}

/* Returns the id of a given node, or -1 in case of error */
int node_getId(const Node *n){
	int g;
	
	if(!n->id){
		fprintf (stderr, "%s\n", strerror(errno));
	}
	g=n->id;
        
	return g;
}

/* Returns a pointer to the name of a given node, or NULL in case of error */
char* node_getName(const Node *n){
	char *t;
	if(!n){
		fprintf (stderr, "%s\n", strerror(errno));
	}
	t =(char *)calloc(100,sizeof(char));
	if(!t){return NULL;}

	strcpy(t,n->name);
	return t;
}

/* Returns the number of connections of a given node, or -1 in case of error */
int node_getConnect(const Node *n){
	
	if(!n){
		fprintf (stderr, "%s\n", strerror(errno));
	}

	return n->nConnect;
}

/* Modifies the id of a given node, returns NULL in case of error */
Node * node_setId(Node *n, const int id){
	
    	n->id=id;
        
    	if(!n){
		fprintf (stderr, "%s\n", strerror(errno));
	}

	return n;
}

/* Modifies the name of a given node, returns NULL in case of error */
Node * node_setName(Node *n, const char *name){
	
	if(!n){
		fprintf (stderr, "%s\n", strerror(errno));
	}

	strcpy(n->name, name);
	return n;
}


/* Modifies the number of connections of a given node, returns NULL in case of
error */
Node * node_setConnect(Node *n, const int cn){
	
	if(!n){
		fprintf (stderr, "%s\n", strerror(errno));
	}

	n->nConnect=cn;
	return n;
}

/* Compares two nodes by the id and then the name.
* Returns 0 when both nodes have the same id, a smaller number than
* 0 when n1 <n2 or one greater than 0 otherwise. */
int node_cmp(const Node *n1, const Node *n2){
	
	int ret;
	ret=strcmp(n1->name, n2->name);
	if(n1->id==n2->id && ret==0){
		return 0; 
	}else if(n1->id>n2->id && ret>0){
			return 2;
		}else {
			return -2;
			}

}

/* Reserves memory for a node where it copies the data from the node src.
* Returns the address of the copied node if everything went well, or NULL
otherwise */
Node * node_copy(const Node *src){
	
	Node *n;
	n=node_ini();
	if(!n){
		fprintf (stderr, "%s\n", strerror(errno));
	}
	n->id=src->id;
	strcpy(n->name, src->name);
	n->nConnect=src->nConnect;
        
	return n;
}

/* Prints in pf the data of a node with the format: [id, name, nConnect]
* Returns the number of characters that have been written successfully.
* Checks if there have been errors in the Output flow, in that case prints
* an error message in stderror*/
int node_print(FILE *pf, const Node *n){
    	
	int chars=0;
  	if(!pf){
		fprintf (stderr, "%s\n", strerror(errno));
    	};
    	chars = fprintf(pf, "[%i, %s, %i]", n->id, n->name, n->nConnect);
    	
    	return chars;
}


Label node_getLabel(const Node*n){
    return n->etq;
}

int node_getAntecesorId(const Node*n){
    return n->antecessor_id;
}

Node* node_setLabel( Node *n, Label l) {
    if (!n) return NULL;
    n->etq = l;
    return n;
}

Node* node_setAntecesorId(Node *n, int id) {
    if (!n) return NULL;
    n->antecessor_id = id;
    return n;
}

