#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "types.h"
#include "stack_fp.h"

int print_int(FILE *f, const void* a) {
	int sum = 0;

	if(!f || !a)
		return -1;

	sum = fprintf(f, "%d\n", *(int*)a);

	if (ferror(f)) {
        fprintf(stderr, "ERROR\n");
        return -1;
    }
    return sum;

}

void *copy_int (const void *a) {
    int *b;
    
    b =  (int*) malloc(sizeof(int));

    if (b == NULL) {
        fprintf(stderr,"%s\n", strerror(errno));
        return NULL;
    }    

    *b = *(int*) a;
    
    return b ; 
}

int cleanUp (int ret_value, Stack *s){
   stack_destroy(s);

   exit(ret_value);
}

double avgStack(Stack *s) {
	int sum = 0, i = 0;
	void *ele;
	double avg;

	Stack *a;
	a = stack_ini(free, copy_int, print_int);

	while(stack_isEmpty(s)==FALSE) {
		ele = stack_pop(s);
		stack_push(a, ele);
		sum += *((int*)ele);
		i++;
		free(ele);
	}
	while(stack_isEmpty(a)==FALSE) {
		ele = stack_pop(a);
		stack_push(s, ele);
		free(ele);
	}
	stack_destroy(a);
	avg = sum*1./i;

	return avg;

}

int main(int argc, char **argv) {
	Stack *s= NULL;
	Status flag = OK;
	FILE *file = stdout;
	int i, max;
	double avg;

	max = atol(argv[1]);

	s = stack_ini(free, copy_int, print_int);

	if(s == NULL)
		cleanUp(EXIT_FAILURE, s);

	for(i = max; i >= 0; i--) {
			if(stack_push(s,&i)==ERROR)
				break;	
	}

	if(flag == ERROR)
		cleanUp(EXIT_FAILURE, s);

	stack_print(file, s);

	
	avg = avgStack(s);

	fprintf(file, "The average is: %lf\n", avg);
	
	stack_print(file, s);

	stack_destroy(s);
		
	return 0;
}
