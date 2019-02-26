#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"
#include "node.h"
#include "elestack.h"
#include "stack_elestack.h"

int main() {
	Stack *s= NULL;
	EleStack *ele = NULL;
	Status flag = TRUE;
	int i, max;
	double avg;

	if(argc != 2)
		return EXIT_FAILURE;
	max = atol(argv[1]);

	s = stack_ini();

	if(s == NULL)
		cleanUp(EXIT_FAILURE, ele, s);

	ele = elestack_ini();

	if(ele==NULL) 
		cleanUp(EXIT_FAILURE, ele, s);

	for(i = max; i >= 0, flag == TRUE; i--) {
		if(elestack_setInfo(ele, &i) == OK)
			flag = stack_push(s,ele);
	}
	if(flag == ERROR)
		cleanUp(EXIT_FAILURE, ele, s);

	stack_print(stdout, s);

	avg = avgEleStack(s);

	fprintf(stdout, "The average is: %lf", avg);

	stack_print(stdout, s);
		

}
