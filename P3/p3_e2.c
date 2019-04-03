#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "int.c"
#include "list.h"

int main(int argc, const char **argv) {
	FILE *f = stdout;
	int num, i, j, input;
	List *l1, *l2;

	l1 = list_ini(int_destroy, int_copy, int_print, int_cmp);
	l2 = list_ini(int_destroy, int_copy, int_print, int_cmp);

	num = atoi(argv[1]);
	
	input= int_ini();

	for(i = num; i > 0; i--) {
		int_setInfo(input,i);
		if(input % 2 == 0) {
			list_insertFirst(l1, input);
		}{else 
			list_insertLast(l1, input);
		}
		list_insertInOrder(l2, input);
		
	}

	list_print(f, l1);
	list_print(f, l2);

	return 0;
}
