#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "queue.h"

#define MAXQUEUE 50

extern int errno;

struct _Queue {
	void* items [MAXQUEUE];
        int front;
        int rear;
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
	
    for (i = 0; i < MAXQUEUE; i++)
        q->items[i] = NULL;

    q->front = q->rear = 0;   
    
    q->destroy_element_function = f1;
    q->copy_element_function = f2;
    q->print_element_function = f3;
    
    return q;
}

void queue_destroy(Queue *q){
    int i;
    if (q== NULL) return;
    i = q->front;
    while (i != q->rear) {
        q->destroy_element_function(q->items[i]);
        q->items[i] = NULL;
	    i = (i+1) % MAXQUEUE;
    }
    free(q);
}

Bool queue_isEmpty(const Queue *q){
    if (!q)
        return TRUE;
    if (q->front == q->rear)
        return TRUE;
    return FALSE;
}

Bool queue_isFull(const Queue* q){
    if (q == NULL) return TRUE;

    if (q->front == (q->rear +1)% MAXQUEUE)
        return TRUE;
    return FALSE;
}

Queue* queue_insert(Queue *q, const void*pElem){
    /* Control de los parametros de entrada o cola llena*/
    if (q == NULL || pElem == NULL || queue_isFull(q) == TRUE)
        return NULL;

    q->items[q->rear] = q->copy_element_function(pElem);
    if (q->items[q->rear] == NULL) {
        return NULL;
    }
    q->rear = (q->rear+1)%MAXQUEUE;
    return q;
}

void* queue_extract(Queue *q){
    void* pe;

    if (!q || queue_isEmpty(q)) {
        return NULL;
    }
    pe = q->items[q->front];
    /* IMPORTANTE: poner puntero del array a NULL, para que no siga apuntando al elemento extraído*/
    q->items[q->front]=NULL;

    /* Actualiza el front */
    q->front = (q->front+1) % MAXQUEUE;               
             
    return pe;
}

int queue_size(const Queue *q){
    if (!q) return -1;
    
    if (q->front < q->rear)
        return (q->rear - q->front);
    else 
        return (MAXQUEUE - (q->front-q->rear));
}


int queue_print(FILE *pf, const Queue *q){
    int count=0, i;
    
    if (!pf) {        
        fprintf(stderr, "Manejador de fichero incorrecto\n");
        return -1;
    }
    if (queue_isEmpty(q)) {
        return fprintf(pf, "Queue vacia.\n");
    }
    count += fprintf(pf, "Cola con %hu elementos: \n", queue_size(q));
    for (i=q->front; i!= q->rear; i=(i+1)%MAXQUEUE){
        count += q->print_element_function(pf, q->items[i]);
    }
    count += fprintf(pf, "\n");
    return count;
}
