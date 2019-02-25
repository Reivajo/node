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

	n = node_ini();
	s = stack_ini();
	es = EleStack_ini();

	node_setId(n, 111);
	node_setName(n,"first");

	EleStack_setInfo(es, n);
	stack_push(stack, es);

	node_setId(n2,222);
	node_setName(n2,"second");

	EleStack_setInfo(es, n);
	stack_push(stack, es);

	stack_print(f, stack);



	return 0;
}