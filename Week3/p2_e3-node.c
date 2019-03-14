#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "types.h"
#include "stack_fp.h"


typedef struct _Node {
	char name[100];
	int id;
	int nConnect;
}Node;

Node *node_ini(){
	Node *n;
	n=(Node*)calloc(1,sizeof(Node));
	if(!n)
		fprintf(stderr, "%s\n", strerror(errno));
	return n;
}

void node_destroy(void *n) {
	// Node *node = (Node*)n;
	if(n)
		free(n);

}
int node_print(FILE *pf, const void *n) {
    Node *node= (Node*)n;
	int chars=0;
  	if(!pf){
		fprintf (stderr, "%s\n", strerror(errno));
    	};
    	chars = fprintf(pf, "[%i, %s, %i]", node->id, node->name, node->nConnect);
    	
    	return chars;
}
void *node_copy(const void *src) {
	Node *n;
	Node *node = (Node*)src;

	n=node_ini();
	if(!n)
		fprintf (stderr, "%s\n", strerror(errno));
	n->id = node->id;
	strcpy(n->name, node->name);
	n->nConnect = node->nConnect;
        
	return n;
}
void cleanUp (int ret_value, Node *n, Stack *s){
    node_destroy(n);
    stack_destroy(s);
    
    exit(ret_value);
}


int main(int argc, char** argv) {
    Node *n = NULL;
    Stack *s = NULL;
    int a;
    
    n = node_ini();

    if (!n) 
    	return 1;

    s = stack_ini(node_destroy, node_copy, node_print);

    if(!s)  
    	cleanUp(1, n, s);
    
    n->id = 111;
    strcpy(n->name, "first");

    if(stack_push(s, n) == ERROR) 
    	cleanUp(1, n, s);
   
	n->id = 222;
    strcpy(n->name, "second");

    if(stack_push(s, n) == ERROR)
    	cleanUp(1, n, s);        
    
    a = stack_print(stdout, s);

    node_destroy(n);
    
    while (!stack_isEmpty(s)) {
        n = (Node*)stack_pop(s);
        node_destroy(n);
    }
    
    n = NULL;
        
    a = stack_print(stdout, s);
    
    cleanUp(0, n, s);

    return (0);
}
