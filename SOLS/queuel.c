#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "queuel.h"
#include "list.h"

#define MAXQUEUE 50

extern int errno;

struct _Queue {
	List *plist;
        
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
    
    if (!q->plist) {
	free(q);
	return NULL;
    }

    q->destroy_element_function = f1;
    q->copy_element_function = f2;
    q->print_element_function = f3;
    
    return q;
}

void queue_destroy(Queue *q){
    if (q== NULL) return;
    list_destroy(q->plist);
    free(q);
}

Bool queue_isEmpty(const Queue *q){
    if (!q)
        return TRUE;
    return list_isEmpty (q->plist);
}

Bool queue_isFull(const Queue* q){
    if (q == NULL) return TRUE;

    return FALSE;
}

Queue* queue_insert(Queue *q, const void*pElem){
    /* Control de los parametros de entrada o cola llena*/
    if (q == NULL || pElem == NULL )
        return NULL;
    if (list_insertLast (q->plist, pElem) ==NULL)
        return NULL;
    return q;
}

void* queue_extract(Queue *q){
    if (!q || queue_isEmpty(q)) {
        return NULL;
    }
    return (list_extractFirst (q->plist));
}

int queue_size(const Queue *q){
    if (!q) return -1;
    return (list_size (q->plist));
}

int queue_print(FILE *pf, const Queue *q){
    if (!q || !pf)
        return -1;
    return list_print (pf, q->plist);
}
