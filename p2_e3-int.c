#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
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
	Status flag = OK;
	FILE *file = stdout;
	int i, max;
	double avg;

	max = atol(argv[1]);

	s = stack_ini();

	if(s == NULL)
		cleanUp(EXIT_FAILURE, ele, s);

	ele = EleStack_ini();

	if(ele==NULL) 
		cleanUp(EXIT_FAILURE, ele, s);

	for(i = max; i >= 0; i--) {
		if(EleStack_setInfo(ele, &i) == OK) {
			if(stack_push(s,ele)==ERROR)
				break;	
		}	
	}

	if(flag == ERROR)
		cleanUp(EXIT_FAILURE, ele, s);

	stack_print(file, s);

	
	avg = avgEleStack(s);

	fprintf(file, "The average is: %lf\n", avg);
	
	stack_print(file, s);

	stack_destroy(s);
		
	return 0;
}
