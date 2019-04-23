#include "stdio.h"
#include "stdlib.h"
#include "errno.h"

#include "tree.h"
#include "int.h"

int main(int argc, char* argv[1]) {
	FILE* f = NULL;
	Tree* t = NULL;
	int num;

	t = tree_ini(f1, f2, f3, f4);

	f = fopen(argv[1], "r");

	if(!f)
		return NULL;

	while(fscanf(f, "%d", &num)) {
		tree_insert(t, num);
	}

	printf("Number of nodes: %d\nTree's depth: %d\n", tree_numNodes(t), tree_depth(t));

	printf("Enter an integer: ");
	scanf("%d\n", &num);

	printf("Integer entered: %d", num);

	if(tree_find(t, num))
		printf("The number %d is inside the tree.\n", num);
		return 0;

	printf("The number %d cannot be found.\n", num);
	return -1;
}