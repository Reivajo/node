#include <stdio.h>
#include <stdlib.h>
#include "types.h"
/* 
 * En este fichero se definen las funciones de destrucción, copia e impresión de elementos enteros
 */

/* Las siguientes funciones se usarán cuando se quieran guardar enteros en la pila. Ojo! Estas funciones reciben un puntero a entero, no una estructura con un puntero a entero (como en el ejercicio P2_E1) */
void int_destroy (void* e){
    if (e)
        free((int*)e);
}
void * int_ini (){
    int *e =NULL;
    e = (int*)malloc(sizeof(int));
    return e;
}
void * int_setInfo (void *e, int v){
    if (!e)
        return NULL;
    *(int*)e = v;
    return e;
}
void * int_copy (const void* e){
    int * dst=NULL;
    if (e == NULL)
	return NULL;
    dst = (int*)malloc(sizeof(int));
    /*Copiamos el contenido */
    *(dst) = *((int*)e);
    return dst;
}

int    int_print(FILE * f, const void* e){
    if (f != NULL && e != NULL)
	return fprintf(f, "[%d]", *((int*)e));
    return -1;
}

int    int_cmp (const void* e1, const void* e2){
    if (e1 != NULL && e2 != NULL){
    	return *((int*)e1) - *((int*)e2);
    }
    return -1;
}
