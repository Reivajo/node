#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"
#include "node.h"
#include "elestack.h"

int main() {
	FILE *f = NULL;
	Node *n;
	Stack *s;
	EleStack *es;
	int num_chars;

	n = node_ini();
	s = stack_ini();
	es = EleStack_ini();

	f=fopen("file.txt","a");

	node_setId(n, 111);
	node_setName(n,"first");

	EleStack_setInfo(es, n);
	stack_push(stack, es);

	node_setId(n2,222);
	node_setName(n2,"second");

	EleStack_setInfo(es, n);
	stack_push(stack, es);

	fprintf(f,"Print the contents of the stack \n");
	num_chars=stack_print(f, stack);

	fprintf(f,"printed characters: %d\n",num_chars);

	fprintf(f,"Emptying stack. Elements extracted: \n")
	





	return 0;
}