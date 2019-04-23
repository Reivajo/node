

#define INFO(pn) ((pn)->info)
#define LEFT(pn) ((pn)->left)
#define RIGHT(pn) ((pn)->right)
#define ROOT(t) ((t)->root)

typedef struct _NodeBT {
void* info;
struct _NodeBT* left;
struct _NodeBT* right;

} NodeBT;


struct _Tree {
 NodeBT *root;
 destroy_element_function_type destroy_element_function;
 copy_element_function_type copy_element_function;
 print_element_function_type print_element_function;
 cmp_element_function_type cmp_element_function;
};


Tree* tree_ini(destroy_element_function_type f1,copy_element_function_type f2,print_element_function_type f3, cmp_element_function_type f4) {
	NodeBT *pn = NULL;
		pn = (BTNode *) malloc(sizeof(BTNode));
		if (!pn) {
		return NULL;
		}
	INFO(pn) = NULL;
	LEFT(pn) = NULL;
	RIGHT(pn) = NULL;
	pn->destroy_element_function=f1;
	pn->copy_element_function=f2;
	pn->print_element_function=f3;
	pn->cmp_element_function=f4;

return pn;
}

Bool tree_isEmpty( const Tree *pa){

	if (pa == NULL) {
		return TRUE;
	}
	if (ROOT(pa) == NULL) {
		return TRUE;
	}

return FALSE;
}

void tree_free(Tree *pa){

	if (pa != NULL) {
		if (INFO(pn) != NULL) {
		element_free(INFO(pa));
		}
	free(pa);
	}
}


Bool tree_find(Tree *pa, const void *pe) {
	if(tree_isEmpty(pa) == TRUE)
		return FALSE;


}
