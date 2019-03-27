/* 
 * File:   p3_e3.c
 * Author: Profesores de PROG2
 */


#include <stdio.h>
#include <stdlib.h>
#include "entero.h"
#include "list.h"

int mainCleanUp (int ret_value, List *pl1, List *pl2, int *pe) {
    if (pe) int_destroy(pe);
    if (pl1) list_destroy (pl1);
    if (pl2) list_destroy (pl2);
    exit (ret_value);
}
int main(int argc, char** argv) {
	int* e=NULL;
	List* list=NULL, *list2=NULL;
	int n, i;

    if (argc < 2) {
        printf("Error: numero insuficiente de argumentos. Introduzca un numero\n");
        return EXIT_FAILURE;
    }
    n=atoi(argv[1]);
    
    list = list_ini(int_destroy, int_copy, int_print, int_cmp);
    if (list == NULL){
        printf ("Error al crear lista.\n");
        mainCleanUp (EXIT_FAILURE, list, list2, e);
    }
    list2 = list_ini(int_destroy, int_copy, int_print, int_cmp);
    if (list2 == NULL){
        printf ("Error al crear lista.\n");
        mainCleanUp (EXIT_FAILURE, list, list2, e);
    }
    e = int_ini();
    if (e == NULL){
        printf ("Error al crear entero.\n");
        mainCleanUp (EXIT_FAILURE, list, list2,e);
    }

    for (i=n; i>0; i--){
        int_setInfo (e, i);
	if (i % 2 == 0){
            if (list_insertFirst(list, e) == NULL){
                printf ("Error al insertar.\n");
                mainCleanUp (EXIT_FAILURE, list, list2,e);
            }
        }
	else {
            if (list_insertLast(list, e) == NULL){
                printf ("Error al insertar.\n");
                mainCleanUp (EXIT_FAILURE, list, list2, e);
            }            
        }
        if (list_insertInOrder (list2, e)==NULL){
            printf ("Error al insertar.\n");
            mainCleanUp (EXIT_FAILURE, list, list2, e);
        }            
    }
    list_print(stdout, list);
    list_print(stdout, list2); 
 
    /* lIBERA TODO*/
    mainCleanUp (EXIT_SUCCESS, list, list2, e);
    /* También se pueden poner aquí bucles que extraigan elemento a elemento hasta que las listas queden vacías*/
}
