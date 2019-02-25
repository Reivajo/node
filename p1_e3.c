#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char const *argv[]) {
	Graph *g;
	char *graphFile;
	char *filename;
	FILE *file1 = NULL;
	FILE *file2 = NULL;

	if (argc <= 2) 
		return 1;


	graphFile = strdup(argv[1]);
	filename = strdup(argv[2]);

	g = graph_ini();
	file1 = fopen(graphFile, "r");
	file2 = fopen(filename, "w");

	graph_readFromFile(file1, g);

	graph_print(file2, g);

	fclose(file2);
	fclose(file1);

	graph_destroy(g);

	free(filename);
	free(graphFile);

	return 0;
}
