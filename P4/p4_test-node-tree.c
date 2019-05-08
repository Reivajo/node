#include "stdio.h"
#include "stdlib.h"
#include "errno.h"

#include "tree.h"
#include "node.h"

#define SIZE 100

int main(int argc, char* argv[1]) {
	FILE *f = NULL;
	Tree *t = NULL;
	Node *n = NULL;
	char name[SIZE];
	int id;

	if(argc < 2) {
			printf("It is needed to include a .txt file with nodes.\n");
			return 1;
		}

	f = fopen(argv[1], "r");

	if (!f) {
		printf("File not found.\n");
		return -1;
	}

	t = tree_ini(node_destroy, node_copy, node_print, node_cmp);
	
	if (!t){
		fclose(f);
		return 1;
	}

	while (fscanf(f, "%d %s", &id, name) == 2){
		n = node_ini();
		if (node_setId(n, id) == NULL){
			node_destroy(n);
			tree_free(t);
			return 1;
		}
		if (node_setName(n, name) == NULL){
			node_destroy(n);
			tree_free(t);
			return 1;
		}
		tree_insert(t, n);
		node_destroy(n);
	}

	fclose(f);

	printf("Number of nodes: %d\nTree's depth: %d\n", tree_numNodes(t), tree_depth(t));

	printf("Pre order: ");
	tree_preOrder(stdout, t);
	printf("\nIn order: ");
	tree_inOrder(stdout, t);
	printf("\nPost order: ");
	tree_postOrder(stdout, t);
	printf("\n");
	
	tree_free(t);
	return 0;
}

