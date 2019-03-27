/* 
 * File:   p3_testqueue.c
 * Author: Profesores de PROG2
 */


#include <stdio.h>
#include <stdlib.h>
#include "queuel.h"
#include "node.h"

#define MAX 255

int mainCleanUp (int ret_value, Queue *q1, Queue *q2, Queue *q3, Node *pn, FILE *pf) {
    if (pn) node_destroy(pn);
    if (q1) queue_destroy (q1);
    if (q2) queue_destroy (q2);
    if (q3) queue_destroy (q3);
    if (pf) fclose (pf);
    exit (ret_value);
}

int main(int argc, char** argv) {

    FILE *pf=NULL;
    Queue *q1=NULL, *q2=NULL, *q3=NULL;
    Node *pn=NULL;
    int id, i, npoints, middle;
    char name[MAX];
    char s[MAX];

    if (argc < 2) {
        printf("Error: numero insuficiente de argumentos. Se espera como argumento el nombre del fichero que contiene informacion sobre los nodos.\n");
        return EXIT_FAILURE;
    }

    pf = fopen(argv[1], "r");
    if (pf==NULL){
        printf ("Error: no se ha podido abrir el fichero,\n");
        return EXIT_FAILURE;
    }
    fgets(s, MAX, pf);
    sscanf(s, "%d\n", &npoints);
    
    pn = node_ini();
    if (pn==NULL) {
        printf("Error: inicializacion de nodo.\n");
	mainCleanUp (EXIT_FAILURE, q1, q2, q3, pn, pf);
    }
    q1 = queue_ini(node_destroy, node_copy, node_print);
    q2 = queue_ini(node_destroy, node_copy, node_print);
    q3 = queue_ini(node_destroy, node_copy, node_print);
    
    if (!q1 || !q2 || !q3) {
        printf("Error: inicializacion de cola.\n");
	mainCleanUp (EXIT_FAILURE, q1, q2, q3, pn, pf);
    }
    printf("Inicialmente:\n");
    printf("Cola 1: ");queue_print(stdout, q1);
    printf("Cola 2: ");queue_print(stdout, q2);
    printf("Cola 3: ");queue_print(stdout, q3);

    printf("Añadiendo %d elementos a q1:\n", npoints);

    for (i=0; i<npoints; i++){
	fgets(s, MAX, pf);
	sscanf(s, "%d %s \n", &id, name);

	node_setId(pn, id);
	node_setName(pn, name);

	if (queue_insert(q1, pn) == NULL) {
            printf("Error: inserción en cola.\n");
            mainCleanUp (EXIT_FAILURE, q1, q2, q3, pn, pf);
        }
        printf("Cola 1: ");queue_print(stdout, q1);
	printf("Cola 2: ");queue_print(stdout, q2);
	printf("Cola 3: ");queue_print(stdout, q3);
        printf("\n");
    }
    fclose(pf);
    node_destroy(pn); pn = NULL;

    printf("\n<<<Pasando la primera mitad de Cola 1 a Cola 2\n");

    npoints = queue_size(q1);
    middle = npoints/2;
    for(i=0; i< middle; i++){
	pn = queue_extract(q1);
	if (queue_insert(q2, pn)== NULL) {
           printf("Error: inserción en cola 2.\n");
           mainCleanUp (EXIT_FAILURE, q1, q2, q3, pn, pf);
        }
	node_destroy(pn); pn = NULL;
	printf("Cola 1: ");queue_print(stdout, q1);
	printf("Cola 2: ");queue_print(stdout, q2);
	printf("Cola 3: ");queue_print(stdout, q3);
        printf("\n");
    }
    printf("\n<<<Pasando la segunda mitad de Cola 1 a Cola 3\n");
    for(i=npoints/2; i< npoints; i++){
	pn = queue_extract(q1);
	if (queue_insert(q3, pn) == NULL) {
            printf("Error: inserción en cola 3.\n");
            mainCleanUp (EXIT_FAILURE, q1, q2, q3, pn, pf);
        }
	node_destroy(pn); pn = NULL;
	printf("Cola 1: ");queue_print(stdout, q1);
	printf("Cola 2: ");queue_print(stdout, q2);
	printf("Cola 3: ");queue_print(stdout, q3);
        printf("\n");
    }
    /* Liberar todo*/
    mainCleanUp (EXIT_SUCCESS, q1, q2, q3, pn, pf);    
}
