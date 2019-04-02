#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "list.h"


typedef struct _NodeListList { /* EdD privada, necesaria para imlistementar lista */
void* info;
struct _NodeListList *next;
} NodeListList; /* Tipo NodeListList privado */
struct _List {
 NodeListList *last; /*La LEC apunta al último nodo y el último al primero*/
	destroy_element_function_type destroy_element_function;
	copy_element_function_type copy_element_function;
	print_element_function_type print_element_function;
	cmp_element_function_type cmp_element_function;
};

/********************PRIVATE FUNCTIONS**************/
NodeList *NodeList_new(){
	NodeList *nl=NULL;

	nl=(NodeList *)malloc(sizeof(NodeList));

	if(!nl){
		return NULL;
	}
	nl->next=NULL;
	nl->info=NULL;

	return nl;
}

void NodeList_free(NodeList *nl){

	if(nl==NULL){
		return;
	}

	nl->next=NULL;
	nl->info=NULL;

	free(nl);

	return;
}

/*******************************************************/


List *list_new(destroy_element_function_type f1,copy_element_function_type f2,print_element_function_type f3,cmp_element_function_type f4) {
	List *list = NULL;
	list = (List *)malloc(sizeof(List));
	if (list == NULL) {
		return NULL;
	}
	list->last = NULL;
	list->destroy_element_function=f1;
	list->copy_element_function=f2;
	list->print_element_function=f3;
	list->cmp_element_function=f4;
	return list;
}

void list_free(List *list) {
	if (list == NULL) {
		return;
	}
	list_recFree(list->last);
	free(list);
}
void list_recFree(NodeList *pn) {
	if (pn == NULL) {
		return;
	}
	list_recFree(pn->next);
	list->destroy_element_function(pn);
}

Bool list_isEmpty(const List *list) {
if (list == NULL) {
return TRUE;
}
if (list->last == NULL) {
return TRUE;
}
return FALSE;
}

const void* list_get (const List* list, int index){
	NodeList *pn=NULL;
	int counter=1;
	if(!List || index<1){
		return;
	}
	list->last->next=pn;
	while(counter!=index){
		pn->next=pn;
		counter++;
	}
	return pn->info;

}

Status list_insertInOrder (List *list, const void *pelem){

}

int list_size (const List* list){
	NodeList *pn=NULL;
	int counter=0;
	if(!list){
		return -1;
	}
	list->last->next = pn;
	while(pn!=list->last){
		pn = pn->next;
		counter++;
	}
	return counter;
}


Status list_insertFirst (List* list, const void *pelem){
	NodeList *pn = NULL;
	if (list == NULL || pelem == NULL) return ERR;
	pn = NodeList_new();
	if (pn == NULL) return ERR;
	pn->info = list->copy_element_function(pelem);
	if (pn->info == NULL) {
		NodeList_free(pn);
		return ERR;
	}if (cl_isEmpty() == TRUE) {
		pn->next = pn;
		list->last = pn;
	} else {
		pn->next = list->last->next;
		list->last->next = pn;
	}
	return OK;
}

Status list_insertLast (List* list, const void *pelem){
	NodeList *pn = NULL, *qn = NULL;
	if (list == NULL || pelem == NULL) return ERR;
	pn = NodeList_new();
	if (pn == NULL) return ERR;
	pn->info = list->copy_element_function(pelem);
	if (pn->info == NULL) {
		NodeList_free(pn);
		return ERR;
	}if (list_isEmpty(list) == TRUE) {
		pn->next = pn;
		list->last = pn
	} else {
		pn->next = list->last->next;
		list->last->next = pn;
		list->last = pn;
	}
	return OK;
}

void * list_extractFirst (List* list){
	NodeList *pn = NULL;
	void *pe = NULL;
	if (list == NULL || list_isEmpty(list) == TRUE) {
		return NULL;
	}
	pn = list->last->next;
	pe = pn->info;
	pn->info = NULL;
	if (list->last->next == list->last) {
		list->last = NULL;
		NodeList_free(pn);
	} else {
		list->last->next = pn->next;
		NodeList_free(pn);
	}
	return pe;
}
void * list_extractLast (List* list){
	NodeList *pn = NULL;
	void *pe = NULL;
	if (list == NULL || list_isEmpty(list) == TRUE) {
		return NULL;
	}
	if (list->last->next == list->last) {
		pe = list->last->info;
		list->last->info = NULL;
		NodeList_free(list->last);
		list->last = NULL;
		return pe;
	}
	pn = list->last;
	while (pn->next != list->last) {
		pn = pn->next;
	}
	pe = list->last->info;
	list->last->info = NULL;
	pn->next = list->last->next;
	NodeList_free(list->last);
	list->last = pn;
	return pe;
}

int list_print(FILE *fd, const List* pl){
    NodeList *nl;
    int counter = 0;
    
    if (!pl || list_isEmpty(pl) == TRUE){
        return 0;
    }
    /* Al menos hay 1 elemento. Con el do-while al principio se sitúa en el primero de la lista*/
    nl = pl->last;
    do{
        nl = nl->next;
        count += pl->print_element_function(fd, nl->info);
        count += fprintf(fd, "\n");
    } while (nl!= pl->last);  /*el último también se imprime por el orden entre avanzar e imprimir*/
        
    return count;
}