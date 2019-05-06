
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


/*************************PRIVATE FUNCTIONS*************************/

void tree_freeRec(NodeBT* pn, destroy_element_function_type desfun);
Status bst_recInsert(NodeBT **ppn, const void *e,copy_element_function_type fcpy, cmp_element_function_type fcmp);
Status tree_preOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun);
Status tree_inOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun);
Status tree_postOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun);
int tree_depthRec(NodeBT* pn);
int tree_numNodesRec(NodeBT* pn);
NodeBT * NodeAB_ini();
void bt_node_free(NodeBT *pn, destroy_element_function_type f1);
int printNodeAB(FILE* pf, const NodeBT *pn, print_element_function_type fprint);
NodeBT * search_nodeAB(const Tree *t, const void* e);
NodeBT *search_nodeAB_rec(NodeBT *pn,const void *e,cmp_element_function_type fcmp);

/*******************************************************************/
/*Initialices a tree*/
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

/*Returns 1 if the tree is Empty, 0 otherwise*/
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
	if (!pa){
		return;
	}
	tree_freeRec(pa->root, pa->destroy_element_function);
	free(pa);
	pa = NULL;
	return;
}

void tree_freeRec(NodeBT* pn, destroy_element_function_type desfun){
	if (!pn){
		return;
	}
	tree_freeRec(LEFT(pn), desfun);
	tree_freeRec(RIGHT(pn), desfun);
	bt_node_free(pn, desfun);
	return;
}


Status tree_insert(Tree *pa, const void *po){
	if (pa == NULL || po == NULL) {
		return ERROR;
	}
return bst_recInsert(&ROOT(pa), po, pa->copy_element_function, pa->cmp_element_function );
}


Status bst_recInsert(NodeBT **ppn, const void *e,copy_element_function_type fcpy, cmp_element_function_type fcmp) {
	
	int cmp;
	void *info=NULL;
		if (*ppn == NULL) {
			*ppn = NodeAB_ini();

		if (*ppn == NULL) return ERROR;

		info= fcpy(e);
		INFO(*ppn) = info;

	return OK;
	}
		cmp = fcmp(e,INFO((*ppn)));
		if(cmp==0){
			return ERROR;
		}
		if (cmp < 0) {
			return bst_recInsert(&(LEFT(*ppn)), e,fcpy,fcmp);
		} else if (cmp > 0) {
			return bst_recInsert(&(RIGHT(*ppn)), e,fcpy,fcmp);
		} 
	return ERROR;
	
}

/*Traverses a tree in pre-order*/
Status tree_preOrder(FILE *f, const Tree *pa){
	if (!f || !pa){
		return ERROR;
	}

	return tree_preOrderRec(f, ROOT(pa), pa->print_element_function);
}

Status tree_preOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun){
	if (!f || !pn){
		return ERROR;
	}
	printNodeAB(f, pn, pfun);
	tree_preOrderRec(f, LEFT(pn), pfun);
	tree_preOrderRec(f, RIGHT(pn), pfun);
	return OK;
}

/*Traverses a tree in in-order*/
Status tree_inOrder(FILE *f, const Tree *pa){
	if (!f || !pa){
		return ERROR;
	}

	return tree_inOrderRec(f, ROOT(pa), pa->print_element_function);
}

Status tree_inOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun){
	if (!f || !pn){
		return ERROR;
	}
	tree_inOrderRec(f, LEFT(pn), pfun);
	printNodeAB(f, pn, pfun);
	tree_inOrderRec(f, RIGHT(pn), pfun);
	return OK;	
}

/*Traverses a tree in post-order*/
Status tree_postOrder(FILE *f, const Tree *pa){
	if (!f || !pa){
		return ERROR;
	}

	return tree_postOrderRec(f, pa->root, pa->print_element_function);
}

Status tree_postOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun){
	if (!f || !pn){
		return ERROR;
	}
	tree_postOrderRec(f, LEFT(pn), pfun);
	tree_postOrderRec(f, RIGHT(pn), pfun);
	printNodeAB(f, pn, pfun);

	return OK;
}

/*Calculates the depth of a tree*/
int tree_depth(const Tree *pa){
	if (!pa || tree_isEmpty(pa) == TRUE){
		return -1;
	}

	return tree_depthRec(ROOT(pa));
}

int tree_depthRec(NodeBT* pn){
	int r_depth=0, l_depth=0;

	if (!pn){
		return -1;
	}
	if (RIGHT(pn) == NULL && LEFT(pn) == NULL){
		return 0;
	}
	r_depth = 1 + tree_depthRec(RIGHT(pn));
	l_depth = 1 + tree_depthRec(LEFT(pn));
	if (r_depth > l_depth){
		return r_depth;
	}
	return l_depth;
}

/*Calculates the number of nodes in a tree*/
int tree_numNodes(const Tree *pa){
	if (!pa || tree_isEmpty(pa) == TRUE){
		return 0;
	}
	return tree_numNodesRec(ROOT(pa));
}

int tree_numNodesRec(NodeBT* pn){
	if (!pn){
		return 0;
	}
	return 1 + tree_numNodesRec(LEFT(pn)) + tree_numNodesRec (RIGHT(pn));
}

/*finds an element in a tree*/
Bool tree_find(Tree* pa, const void* pe){

	if(!pa || !pe) return FALSE;

	if(search_nodeAB(pa,pe) != NULL){
		return TRUE;
	}else{
		return FALSE;
	}
}


/***************** NODE_BT Functions ***************/

/*Initialices a node*/
NodeBT * NodeAB_ini(){
	NodeBT* pn = NULL;

	pn = malloc(sizeof(NodeBT));
	if (!pn){
		return NULL;
	}
	LEFT(pn) = RIGHT(pn) = NULL;
	INFO(pn) = NULL;
	return pn;
}

/*destroys a node*/
void bt_node_free(NodeBT *pn, destroy_element_function_type f1){

	if (pn != NULL) {
		f1(INFO(pn));
		free(pn);
	}
	return;
}

/*Prints the info of a given node*/
int printNodeAB(FILE* pf, const NodeBT *pn, print_element_function_type fprint){
	if (!pf || !pn){
		return 0;
	}
	return fprint(pf, pn->info);
}

NodeBT * search_nodeAB(const Tree *t, const void* e){

	if(!t || !e){
		return NULL;
	}

	return search_nodeAB_rec(ROOT(t),e,t->cmp_element_function);
}

NodeBT *search_nodeAB_rec(NodeBT *pn,const void *e,cmp_element_function_type fcmp){

	int cmp=0;

	if(!pn || !e){
		return NULL;
	}

	cmp= fcmp(e,INFO(pn));

	if(cmp==0){
		return pn;
	}
	else if(cmp>0){
		return search_nodeAB_rec(RIGHT(pn),e,fcmp);
	}else{
		return search_nodeAB_rec(LEFT(pn),e,fcmp);
	} 	
}

/**************************************************/

