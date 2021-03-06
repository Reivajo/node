#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "queue.h"


struct _Queue {
	void *items[MAXQUEUE];
	int front;
	int rear;
	destroy_element_function_type destroy_element_function; 
	copy_element_function_type copy_element_function; 
	print_element_function_type print_element_function;
};


Queue* queue_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3) {
	int i;
    Queue* q = NULL;
    
    q = (Queue*) malloc(sizeof (Queue));
    
    if (q ==NULL)
	return NULL;
	
    for (i = 0; i < MAXQUEUE; i++)
        q->items[i] = NULL;

    q->front = q->rear = 0;   
    
    q->destroy_element_function = f1;
    q->copy_element_function = f2;
    q->print_element_function = f3;
    
    return q;
}

void queue_destroy(Queue *q) {
	int i;
    
    if (q != NULL) {
      i = q->front;
    
    	while (i != q->rear) {
			q->destroy_element_function(q->items[i]);
			q->items[i] = NULL;
			i = (i+1)%MAXQUEUE;
		}
	}
	free(q);
	return;
}

Bool queue_isEmpty(const Queue *q) {
	if (q == NULL) {
      return TRUE;
    }
    if (q->front == q->rear) {
      return TRUE;
	}
    return FALSE;
}

Bool queue_isFull(const Queue *q) {
	if (q == NULL)
	     return TRUE;

	if (q->front == (q->rear+1)% MAXQUEUE)
		return TRUE;

	return FALSE;
}

Queue* queue_insert(Queue *q, const void* pElem) {
	
    if (q == NULL || pElem == NULL || queue_isFull(q) == TRUE) {
      return NULL;
	}
    q->items[q->rear] = q->copy_element_function(pElem);
    
    if (q->items[q->rear] == NULL){
	return NULL;
	}
	q->rear = (q->rear+1)% MAXQUEUE; 
	
	return q;
}

void * queue_extract(Queue *q) {
	void *e = NULL;
	if (q == NULL || queue_isEmpty(q) == TRUE)
	    return NULL;

	e = q->items[q->front]; 
	q->items[q->front] = NULL;
	q->front = (q->front+1)% MAXQUEUE;

	return e;
}

int queue_size(const Queue *q) {
	if (q == NULL)
		return -1;
	return (q->rear - q->front + MAXQUEUE) % MAXQUEUE;
}

int queue_print(FILE *pf, const Queue *q) {
	int num = 0, i = 0;

	if(!pf || !q)
		return -1;
	for(i = q->front; i!= q ->rear; i++) {
		num += q->print_element_function(pf, q->items[i]);
		fprintf(pf, "\n");
	}
	return num;
}





