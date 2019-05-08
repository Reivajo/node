#include <stdio.h>
#include <stdlib.h>
#include "int.h"
#include "types.h"


void* int_ini(){
	int *i=NULL;

	i = (int*)malloc(sizeof(int));

	if(i==NULL){
		return NULL;
	}

    return i;
}

void int_destroy (void* num){
    
    if (num != NULL){
        free(num);
    }
}

void* int_copy (const void* num){
    int *i=NULL;
    if (num == NULL){
	return NULL;
	}

    i = (int*)malloc(sizeof(int));

    if (i == NULL){
	   return NULL;
	}

    *(i) = *((int*)num);
    return i;
}

int int_print(FILE *file, const void* num){
    if (!file || !num){
    	return -1;
    }

	return fprintf(file, "[%d]", *((int*)num));
}

int int_cmp (const void* num1, const void* num2){
    if(!num1 || !num2){
    	return -1;
    }
    return *((int*)num1) - *((int*)num2);
}

void* int_setInfo (void *num, int v){
    if (!num){
        return NULL;
    }
    *((int*)num) = v;
    return num;
}
