#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"
#include "node.h"
#include "elestack.h"
#include "stack_elestack.h"

int main() {
	Node *n=NULL;
	Stack *s=NULL;
	int i=0;

	n = node_ini();
	if(!n)
		return NULL;

	s = stack_ini(node_destroy, node_copy, node_print);
	if(!s)
		return NULL;

	node_setId(node_setName(n,"first"), 111);

	if(stack_push(s, es)==ERROR)
		cleanUp(EXIT_FAILURE,n,s);

	node_setId(node_setName(n,"second"),222);
	if(stack_push(s, es)==ERROR)
		cleanUp(EXIT_FAILURE,n,s);

	i=stack_print(stdout,s);

	node_destroy(n);
	
	while(stack_isEmpty(s)==FALSE){
		n= (Node *) stack_pop(s);
		node_destroy(n);
	}

	n=NULL;

	i=stack_print(stdout,s);

	stack_destoy(s);

	return 0;
}