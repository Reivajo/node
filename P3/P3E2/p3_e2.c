#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "int.h"
#include "list.h"

int mainCleanUp(int ret_value, List* list1, List* list2, int* info) {
	if(info)
		int_destroy(info);
	if(list1)
		list_destroy(list1);
	if(list2)
		list_destroy(list2);
	exit(ret_value);
}

int main(int argc, const char **argv) {
	FILE *f = stdout;
	int num, i, *input;
	List *l1, *l2;

	l1 = list_ini(int_destroy, int_copy, int_print, int_cmp);
	l2 = list_ini(int_destroy, int_copy, int_print, int_cmp);

	num = atoi(argv[1]);
	
	input= int_ini();

	for(i = num; i > 0; i--) {
		int_setInfo(input,i);
		if(i % 2 == 0) {
			if(list_insertFirst(l1, input) == ERROR){
				mainCleanUp(EXIT_FAILURE, l1, l2, input);
			}
		} else {
			if(list_insertLast(l1, input) == ERROR){
				mainCleanUp(EXIT_FAILURE, l1, l2, input);
			}
		}
		
		if(list_insertFirst(l2, input) == ERROR) {
			mainCleanUp(EXIT_FAILURE, l1, l2, input);
		}
	}

	printf("List 1: \n");
	list_print(f, l1);
	printf("\nList 2: \n");
	list_print(f, l2);

	mainCleanUp(EXIT_SUCCESS, l1, l2, input);

	return 0;
}
