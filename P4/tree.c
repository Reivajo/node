
#include "tree.h"
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
	Tree *b = NULL;
		b = (Tree *)malloc(sizeof(Tree));
		if (b == NULL) {
		return NULL;
		}

	ROOT(b) = NULL;
	b->destroy_element_function=f1;
	b->copy_element_function=f2;
	b->print_element_function=f3;
	b->cmp_element_function=f4;

return b;
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

void bt_node_free(NodeBT *pn, destroy_element_function_type f1){

	if (pa != NULL) {
		if (INFO(pn) != NULL) {
		element_free(INFO(pa));
		}
	free(pa);
	}
}

Status tree_insert(Tree *pa, const void *po){
	if (pa == NULL || po == NULL) {
		return ERROR;
	}
return bst_recInsert(&ROOT(pa), po, pa->copy_element_function, pa->cmp_element_function );
}

status bst_recInsert(NodeBT **ppn, const void *e,copy_element_function_type fcpy, cmp_element_function_type fcmp) {
	
	int cmp;
		if (*ppn == NULL) {
			*ppn = bt_node_new();
		if (*ppn == NULL) return ERROR;
			INFO(*ppn) = fcpy(e);
		if (INFO(*ppn) == NULL) {
		bt_node_free(*ppn);
	return ERROR;
	}
	return OK;
	}
		cmp = fcmp(INFO((*ppn)),e);
		if (cmp < 0) {
			return bst_recInsert(&LEFT(*ppn), e);
		} else if (cmp > 0) {
			return bst_recInsert(&RIGHT(*ppn), e);
		} else {
	return OK;
	}
}
Status tree_preOrder(FILE *f, const Tree *pa){


}