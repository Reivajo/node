#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"
#include "node.h"
#include "elestack.h"
#include "stack_elestack.h"

int main() {
	FILE *f = NULL;
	Node *n;
	Stack *s;
	int num_chars=0,i;

	n = node_ini();
	if(n == NULL)
		return NULL;

	s = stack_ini(node_destroy, node_copy, node_print);
	if(!s)
		return NULL;

	f=fopen("file.txt","a");

	node_setId(n, 111);
	node_setName(n,"first");

	EleStack_setInfo(es, n);
	stack_push(s, es);

	node_setId(n,222);
	node_setName(n,"second");

	EleStack_setInfo(es, n);
	stack_push(s, es);

	fprintf(f,"Print the contents of the stack \n");
	num_chars=stack_print(f, s);

	fprintf(f,"printed characters: %d\n",num_chars);

	fprintf(f,"Emptying stack. Elements extracted: \n");
	
	while(stack_isEmpty(s)==FALSE){
		pop = stack_pop(s);
		EleStack_print(f, pop);
		fprintf(f," ");
		EleStack_destroy(pop);
	}

	fprintf(f,"\nPrint the contents of the stack after emptying: \n");

	num_chars=stack_print(f,s);

	fprintf(f,"printed characters: %d\n",num_chars);

	stack_destroy(s);
	node_destroy(n);
	EleStack_destroy(es);
	fclose(f);

	return 0;
}