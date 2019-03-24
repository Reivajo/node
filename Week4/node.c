
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "node.h"

#define NAME_L 64

extern int errno ;

struct _Node {
    char* name;
    int id;             
    int nConnect;      
    Label etq;     
    int antecesor_id;
};

Node * node_ini() {
    Node *n = NULL;
    
    n = (Node *) malloc(sizeof(Node));
    n->name = (char*)malloc(NAME_L*sizeof(char));

    if (!n) {
        fprintf (stderr, "%s\n", strerror(errno));
        return NULL;
    }
    node_setId (n, -1);
    node_setName (n, "");
    node_setConnect (n, 0);
    
    node_setLabel(n, WHITE);
    node_setAntecesorId(n, -1);
    return n;
}

void node_destroy(void * n) {
    if(n){
        Node *aux = (Node*)n;
        if (aux->name)
            free(aux->name);
        free(n);
    }
}

int node_getId(const Node * n){
    if (!n)
    	return -1;

    return n->id;
}

char* node_getName(const Node * n){
    if (!n)
        return n->name;
    
    return n->name;
}

int node_getConnect(const Node * n){
    if (!n)
        return -1;
    return n->nConnect;
}

Label node_getLabel(const Node*n){
	if(!n)
		return -1;

    return n->etq;
}

int node_getAntecesorId(const Node*n){
	if(!n)
		return -1;
    return n->antecesor_id;
}

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

int node_cmp(const Node *n1, const Node *n2){
	int ret;
	
	ret=strcmp(n1->name, n2->name);
	
	if(n1->id==n2->id && ret==0)
		return 0;
	else if(n1->id>n2->id && ret>0)
		return 2;
	return -2;
}

void * node_copy(const void * src){
	Node *out = NULL;
    Node * origin = NULL;
        
    if (!src) return NULL;
        
    origin = (Node*) src; 
	out = node_ini();
	if (out==NULL) return NULL;

	node_setId (out, origin->id);
	node_setName(out, origin->name);
    node_setConnect (out, origin->nConnect);
    node_setLabel (out, origin->etq);
    node_setAntecesorId (out, origin->antecesor_id);
        
	return out;
}

int node_print(FILE *pf, const void * vn){
    int num_chars;
    Node *n = NULL;
    
    if (!pf || !vn ) return -1;
    
    n = (Node*) vn;
    num_chars  = fprintf(pf, "[%s, %d, %d]", n->name, n->id, n->nConnect);
    
    
    return num_chars;
}

