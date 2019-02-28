#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"
#include "node.h"
#include "elestack.h"
#include "stack_elestack.h"

int cleanUp (int ret_value, EleStack *ele, Stack *s){

	EleStack_destroy(ele);
	stack_destroy(s);

	return ret_value;
}


int main(int argc, char **argv) {
	Stack *s= NULL;
	EleStack *ele = NULL;
	Bool flag = TRUE;
	FILE *file = stdout;
	int i, max;
	double avg;

	
	if(argc != 2)
		return EXIT_FAILURE;
	max = atol(argv[1]);

	s = stack_ini();

	if(s == NULL)
		cleanUp(EXIT_FAILURE, ele, s);

	ele = Elestack_ini();

	if(ele==NULL) 
		cleanUp(EXIT_FAILURE, ele, s);

	for(i = max; i >= 0, flag == TRUE; i--) {
		if(Elestack_setInfo(ele, &i) == OK)
			flag = stack_push(s,ele);
	}
	if(flag == ERROR)
		cleanUp(EXIT_FAILURE, ele, s);

	stack_print(file, s);

	avg = avgEleStack(s);

	fprintf(file, "The average is: %lf", avg);

	stack_print(file, s);

	stack_destroy(s);
		
	return 0;
}
