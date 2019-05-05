#include "stdio.h"
#include "stdlib.h"
#include "errno.h"

#include "tree.h"
#include "int.h"

int main(int argc, char* argv[1]) {
	FILE* f = NULL;
	Tree* t = NULL;
	int *num=NULL;

	if(argc < 2){
		printf("Not enough arguments.");
		return -1;
	}
	t = tree_ini(int_destroy, int_copy, int_print, int_cmp);

	if(!t) return -1;

	f = fopen(argv[1], "r");

	if(!f)
		return -1;

	num = (int *)malloc(sizeof(int));

	if(num==NULL){
		tree_free(t);
		return -1;
	}

	while(fscanf(f, "%d", num)>0) {
		tree_insert(t, num);
	}
	fclose(f);

	printf("Number of nodes: %d\nTree's depth: %d\n", tree_numNodes(t), tree_depth(t));

	
	printf("Enter an integer: ");

	scanf("%d", num);
	
	printf("Integer entered: %d\n", *num);

	if(tree_find(t, num)){
		printf("The number %d is inside the tree.\n", *num);
		return 0;
	}else{

		printf("The number %d cannot be found.\n", *num);
		return -1;
	}
	free(num);
	tree_free(t);
}
