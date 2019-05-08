
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void destroy_string_function(void* e){
	free((char*)e);
}

void * copy_string_function(const void* e){
	char* dst;
	if (e == NULL)
		return NULL;
	dst = (char*)malloc((1+strlen((char*)e))*sizeof(char));
	/*Copiamos el elemento*/
	strcpy(dst, (char*)e);
	return dst;
}

int    print_string_function(FILE * f, const void* e){
	if (f != NULL && e != NULL)
		return fprintf(f, "%s\n", (char*)e);
	return -1;
}

int    cmp_string_function(const void* e1, const void* e2){
	if (e1 != NULL && e2 != NULL){
		return strcmp((char*)e1, (char*)e2);
	}
	return -1;
}

