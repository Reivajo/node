#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "list.h"


typedef struct _NodeList { /* EdD privada, necesaria para imlistementar lista */
void* info;
struct _NodeList *next;
} NodeList; /* Tipo NodeListList privado */

struct _List {
 NodeList *last; /*La LEC apunta al último nodo y el último al primero*/
	destroy_element_function_type destroy_element_function;
	copy_element_function_type copy_element_function;
	print_element_function_type print_element_function;
	cmp_element_function_type cmp_element_function;
};

/********************PRIVATE FUNCTIONS**************/
void list_recFree(NodeList *pn);


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

void NodeList_free(NodeList *nl, destroy_element_function_type f) {

	if(nl==NULL){
		return;
	}

	if(nl->info != NULL) {
		f(nl->info);
		free(nl);
	}

	return;
}

/*******************************************************/


List *list_ini(destroy_element_function_type f1,copy_element_function_type f2,print_element_function_type f3,cmp_element_function_type f4) {
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

void list_destroy(List* list){
    void *n;
    
    if (!list)
        return;
    
    while (list_isEmpty(list)==FALSE){  
        n = list_extractFirst(list);
        list->destroy_element_function(n);
    }
    free(list);
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
	if(!list || index<1){
		return NULL;
	}
	pn=list->last->next;
	while(counter!=index){
		pn=pn->next;
		counter++;
	}
	return pn->info;

}

Status list_insertInOrder (List *list, const void *pelem){
	NodeList *nl=NULL, *pn=NULL;

	if(!list || !pelem){
		return ERROR;
	}

	nl=NodeList_new();

	if(nl==NULL){
		return ERROR;
	}
	DEBUG();

	nl->info=list->copy_element_function(pelem);
	DEBUG();

	if(list_isEmpty(list)){
	DEBUG();
		
		pn->next=pn;
	DEBUG();
		list->last=pn;
	DEBUG();
		return OK;
	}
	DEBUG();

	pn=list->last->next;

	if(list->cmp_element_function(pelem, pn->info) < 0){
		NodeList_free(nl,list->destroy_element_function);

		return list_insertFirst(list,pelem);
	}

	
	while(list->cmp_element_function(pelem,pn->next->info)>0){
		pn=pn->next;

		if(pn==list->last){
			NodeList_free(nl,list->destroy_element_function);
			return list_insertLast(list,pelem);
		}
	}
	nl->next=pn->next;
	pn->next= nl;

	return OK;

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
	return counter+1;
}


Status list_insertFirst (List* list, const void *pelem){
	NodeList *pn = NULL;
	if (list == NULL || pelem == NULL) 
		return ERROR;
	pn = NodeList_new();
	if (pn == NULL) return ERROR;
	pn->info = list->copy_element_function(pelem);
	if (pn->info == NULL) {
		NodeList_free(pn, list->destroy_element_function);
		return ERROR;
	}
	if (list_isEmpty(list) == TRUE) {
		pn->next = pn;
		list->last = pn;
	} else {
		pn->next = list->last->next;
		list->last->next = pn;
	}
	return OK;
}

Status list_insertLast (List* list, const void *pelem){
	NodeList *pn = NULL;
	if (list == NULL || pelem == NULL) 
		return ERROR;
	pn = NodeList_new();
	if (pn == NULL) return ERROR;
	pn->info = list->copy_element_function(pelem);
	if (pn->info == NULL) {
		NodeList_free(pn, list->destroy_element_function);
		return ERROR;
	}
	if (list_isEmpty(list) == TRUE) {
		pn->next = pn;
		list->last = pn;
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
		NodeList_free(pn, list->destroy_element_function);
	} else {
		list->last->next = pn->next;
		NodeList_free(pn, list->destroy_element_function);
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
		NodeList_free(list->last, list->destroy_element_function);
		list->last = NULL;
		return pe;
	}
	pn = list->last;
	while (pn->next != list->last) {
		pn=pn->next;
	}
	pe = list->last->info;
	list->last->info = NULL;
	pn->next = list->last->next;
	NodeList_free(list->last, list->destroy_element_function);
	list->last = pn;
	return pe;
}

int list_print (FILE *fd, const List* list){
	NodeList *nl;
	int counter = 0;

	if (!list || list_isEmpty(list) == TRUE){
		return -1;
	}

	nl = list->last;
	do{
		nl = nl->next;
		counter += list->print_element_function(fd, nl->info);
		counter += fprintf(fd, "\n");
	}while (nl!= list->last);

	return counter;
}