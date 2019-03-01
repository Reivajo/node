#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "elestack.h"
#include "stack_elestack.h"

#define DEBUG() printf("%d\n", __LINE__)

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

	if(argc != 2)
		return EXIT_FAILURE;
	max = atol(argv[1]);

	s = stack_ini();

	if(s == NULL)
		cleanUp(EXIT_FAILURE, ele, s);

	ele = EleStack_ini();

	if(ele==NULL) 
		cleanUp(EXIT_FAILURE, ele, s);

	for(i = max; i >= 0, flag == OK; i--) {
	DEBUG();

		if(EleStack_setInfo(ele, &i) == OK) {
			DEBUG();
			flag = stack_push(s,ele);
			DEBUG();
		}	
	DEBUG();

	}

	DEBUG();


	if(flag == ERROR)
		cleanUp(EXIT_FAILURE, ele, s);

	DEBUG();

	stack_print(file, s);
	DEBUG();

	avg = avgEleStack(s);
	DEBUG();

	fprintf(file, "The average is: %lf", avg);
	DEBUG();

	stack_print(file, s);

	stack_destroy(s);
		
	return 0;
}
