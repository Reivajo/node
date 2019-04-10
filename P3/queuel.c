#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "queue.h"
#include "list.h"

#define MAXQUEUE 50

extern int errno;

struct _Queue {

	List *list;
	destroy_element_function_type destroy_element_function;
    copy_element_function_type copy_element_function;
	print_element_function_type print_element_function;
};


Queue* queue_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3){
    int i;
    Queue* q = NULL;
    
    q = (Queue*) malloc(sizeof (Queue));
    
    if (q ==NULL)
	return NULL;
	
    q->plist = list_ini(f1, f2, f3, NULL);
    
    if (!q->list) {
	  free(q);
	return NULL;
    }

    q->destroy_element_function = f1;
    q->copy_element_function = f2;
    q->print_element_function = f3;
    
    return q;
}

void queue_destroy(Queue *q) {
	
	if(q==NULL){
		return;
	}
	list_destroy(q->list);
	free(q);
	return;
}

Bool queue_isEmpty(const Queue *q) {
	if (q == NULL) {
      return TRUE;
    }
    if (list_isEmpty(q->list)==TRUE) {
      return TRUE;
	}
    return FALSE;
}

Bool queue_isFull(const Queue *q) {
	if (q == NULL)
	     return TRUE;

	return FALSE;
}

Queue* queue_insert(Queue *q, const void* pElem) {
	
    if (q == NULL || pElem == NULL || queue_isFull(q) == TRUE) {
      return NULL;
	}
    
    if(list_insertLast(q->list,pElem)==ERROR){
    	return NULL;
    }

	return q;
}

void * queue_extract(Queue *q) {
	
	void * e=NULL;
	if(q==NULL){
		return NULL;
	}

	e=list_extractFirst(q->list);

	if(e==NULL){
		return NULL;
	}
	return e;
}

int queue_size(const Queue *q) {
	
	int size=0;
	if(q==NULL){
		return -1;
	}
	size=list_size(q->list);

	return size;

}

int queue_print(FILE *pf, const Queue *q) {
	
	int chars=0;
	if(q==NULL||pf==NULL){
		return -1;
	}

	chars=list_print(q->list);

	return chars;

}
