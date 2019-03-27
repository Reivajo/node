/*
 * node.c
 *
 *  Created on: 10 dic. 2018
 *      Author: eduardo
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "node.h"

#define NAME_L 64

extern int errno ;

struct _Node {
    char name[NAME_L];  // nombre del nodo
    int id;             // id del nodo
    int nConnect;       // número de conexiones que parten del nodo
    
    Label etq;     // estado del nodo: typedef enum {BLANCO, NEGRO} Label;

    int antecesor_id;
};

Node * node_ini() {
    Node *pn = NULL;
    
    pn = (Node *) malloc(sizeof(Node));
    if (!pn) {
        // imprime mensaje de error
        fprintf (stderr, "%s\n", strerror(errno));
        return NULL;
    }
    
    /* inicializa campos */
    node_setId (pn, -1);
    node_setName (pn, "");
    node_setConnect (pn, 0);
    
    node_setLabel(pn, BLANCO);
    node_setAntecesorId(pn, -1);
    return pn;
}

void node_destroy(void * n) {
    if (n) free(n);
}

// getters
int node_getId(const Node * n){
    if (n)
        return n->id;
    return -1;
}

char* node_getName(const Node * n){
    if (n)
        return n->name;
    
    return NULL;
}

int node_getConnect(const Node * n){
    if (n)
        return n->nConnect;
    return -1;
}

Label node_getLabel(const Node*n){
    return n->etq;
}

int node_getAntecesorId(const Node*n){
    return n->antecesor_id;
}

// setters

Node* node_setLabel( Node *n, Label l) {
    if (!n) return NULL;
    n->etq = l;
    return n;
}

Node * node_setId(Node * n, const int id){
    if (n) {
        n->id = id;
    }
    
    return n;
}

Node* node_setAntecesorId(Node *n, int id) {
    if (!n) return NULL;
    n->antecesor_id = id;
    return n;
}

/* discutir strncpy,  
 * alternativas: 
 * strlcpy 
 *  snprintf (n->name, sizeof(n->name), %s, name) 
 * */ 
Node * node_setName(Node * n, const char* name){
    if (n) {
        strncpy(n->name, name, NAME_L);
    }
    
    return n;
}

Node * node_setConnect(Node * n, const int cn){
    if (n) {
        n->nConnect = cn;
    }

    return n;
}

int node_cmp (const Node * n1, const Node * n2){
    if (!n1 || !n2) return 0;
    
    return (n1->id - n2->id);
}

void * node_copy(const void * src){
	Node *target = NULL;
        Node * orgn = NULL;
        
        if (!src) return NULL;
        
        orgn = (Node*) src; 
	target = node_ini();
	if (target==NULL) return NULL;

	/* igualando estructura tambien ok */
	node_setId (target, orgn->id);
	node_setName(target, orgn->name);
        node_setConnect (target, orgn->nConnect);
        node_setLabel (target, orgn->etq);
        node_setAntecesorId (target, orgn->antecesor_id);
        
	return target;
}

int node_print(FILE *pf, const void * vn){
    int i;
    Node *n = NULL;
    
    if (!pf || !vn ) return -1;
    
    n = (Node*) vn;
    i  = fprintf(pf, "[%s, %d, %d]", n->name, n->id, n->nConnect);
    
    // comprueba si ha habido errores en el flujo de salida
    if (ferror (pf)) {
        fprintf(stderr, "fprintf failed\n");
    }
    
    return i;
}

