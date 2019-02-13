#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"
#include "node.h"

extern int errno;

struct _Node{
	char name[100];
	int id;
	int nConnect;
};

Node * node_ini(){
	Node *f;
	f= (Node*)malloc(sizeof(Node));

	if(f==NULL){
		fprintf(stderr,"%s\n",strerror(errno));
		return NULL;
	}
	return f;
}
void node_destroy(Node * n){
	free(n);
}
/* Devuelve el id de un nodo dado, o -1 en caso de error */
int node_getId(const Node * n){
	if(n==NULL){
		return -1;
	}
	return n->id;

}
/* Devuelve un puntero al nombre de un nodo dado, o NULL en caso de error */
char* node_getName(const Node * n){
	if(n==NULL){
		return NULL;
	}
	return n->name;
}
/* Devuelve el n�mero de conexiones de un nodo dado, o -1 en caso de error */
int node_getConnect(const Node * n){
	if(n==NULL){
		return -1;
	}
	return n->nConnect;
}
/* Modifica el id de un nodo dado, devuelve NULL en caso de error */
Node * node_setId(Node * n, const int id){
	if(n==NULL){
		return NULL;
	}
	n->id=id;

}

/* Modifica el nombre de un nodo dado, devuelve NULL en caso de error */
Node * node_setName(Node * n, const char* name){
	if(n==NULL){
		return NULL;
	}
	strcpy(n->name, name);

}
/* Modifica el n�mero de conexiones de un nodo dado, devuelve NULL en caso de
error */
Node * node_setConnect(Node * n, const int nc){
	if(n==NULL){
		return NULL;
	}
	n->nConnect=nc;
}
/* Compara dos nodos por el id y despu�s el nombre.
 * Devuelve 0 cuando ambos nodos tienen el mismo id, un n�mero menor que
 * 0 cuando n1 < n2 o uno mayor que 0 en caso contrario. */
int node_cmp (const Node * n1, const Node * n2){
	if(n1->id==n2->id) {
		return 0;
	}
	else if(n1->id<n2->id){
		return -1;
	}
	else{
		return 1;
	}


}
/* Reserva memoria para un nodo en el que copia los datos del nodo src.
 * Devuelve la direcci�n del nodo copia si todo ha ido bien, o NULL en otro caso
*/
Node * node_copy(const Node * src){
	Node *f;
	f=(Node*)malloc(sizeof(Node));
	if(f==NULL){
		return NULL;
	}
	strcpy(f->name,src->name);
	f->id=src->id;
	f->nConnect=src->nConnect;

	if((f->name==NULL)||(f->id==NULL)||(f->nConnect==NULL)){
		return NULL;  
	}
	return f;

}
/* Imprime en pf los datos de un nodo con el formato: [id, name, nConnect]
 * Devuelve el n�mero de caracteres que se han escrito con �xito.
 * Comprueba si ha habido errores en el flujo de salida, en ese caso imprime
 * mensaje de error en stderror*/
int node_print(FILE *pf, const Node * n){
  	fopen(pf,"w");
	int num_Char=0;
	if(n==NULL){
		fprintf(stderr,"%s\n",strerror(errno));
		return NULL;
	}
	char nameCopied[100];
	pf=fopen(pf,"a");
	num_Char = fprintf(pf, "%n, %s, %n,\n",n->id,n->name,n->nConnect);

	if(num_Char==0){
		fprintf(stderr,"%s\n",strerror(errno));
	}

	pf=fclose(pf);
	return num_Char;
}
