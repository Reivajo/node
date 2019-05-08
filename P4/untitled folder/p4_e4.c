#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "types.h"
#include "string.h"

#define MAX 300

char* read_string_from_file(FILE* f) {
	char* str;
	char s[MAX];
	
	fscanf(f, "%s\n", s);
	str = (char*)malloc((strlen(s)+1)*sizeof(char));
	
	strcpy(str, s);
	
	return str;
}

int main(int argc, char const *argv[]){
	FILE *f = NULL;
	Tree* t = NULL;
	char* str;

	if(argc < 2){
		printf("Missing file.\n");
		return 1;
	}


	f = fopen(argv[1], "r");

	if (!f)
		return 1;

	t = tree_ini(destroy_string_function, copy_string_function, print_string_function, cmp_string_function);
	
	if (!t){
		fclose(f);
		return 1;
	}

	while(!feof(f)){
		str = read_string_from_file(f);
		
		if (tree_insert(t, str) == ERROR){
			fprintf(stdout, "Error inserting the string (%s) \n", str);			
		}

		free(str);
	}

	fclose(f);
	
	fprintf(stdout, "Number of nodes: %d\nDepth: %d\n", tree_numNodes(t), tree_depth(t));
	tree_inOrder(stdout, t);
	fprintf(stdout, "\n");

	fprintf(stdout, "Enter a string to find in the tree (using the same format):\n");
	str = (char*)calloc(MAX, sizeof(char));
	scanf("%s",str);

	if (tree_find(t, str) == TRUE){
		fprintf(stdout, "The string was found.\n");
	}else{
		fprintf(stdout, "The string was not found.\n");
	}
	free(str);
	tree_free(t);

	return 0;
}
