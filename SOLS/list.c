#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct _NodeList {
    void* info; 
    struct _NodeList *next;
} NodeList;

struct _List {
    NodeList *last;  /*En LEC la lista apunta al último nodo, y el último al primero*/
    destroy_element_function_type destroy_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
    cmp_element_function_type cmp_element_function;
};

/* Funciones privadas */
NodeList* nodelist_ini();
void nodelist_free(NodeList* pn, destroy_element_function_type f);


NodeList* nodelist_ini(){
    NodeList *pn;
    
    if ((pn = (NodeList*) malloc(sizeof(NodeList))) ==NULL) 
        return NULL;    
    
    pn->info = pn->next = NULL;
    
    return pn;
}

void nodelist_free(NodeList *pn, destroy_element_function_type f){
    if (pn != NULL){
        if (pn->info != NULL)
            f(pn->info);
        free(pn);
    }
}

/*Funciones públicas*/

List* list_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4){
    List* l;
    
    if ((l = (List *) malloc(sizeof(List))) ==NULL) 
        return NULL;    
    
    l->last = NULL;

    l->destroy_element_function = f1;
    l->copy_element_function = f2;
    l->print_element_function = f3;
    l->cmp_element_function = f4;
    
    return l;
}

void list_destroy(List* pl){
    void *extracted;
    
    if (!pl)
        return;
    
    while (list_isEmpty(pl)==FALSE){  /*Tmb se puede hacer con node_free recorriendo lista con paux*/
        extracted = list_extractFirst(pl);
        pl->destroy_element_function(extracted);
    }
    free(pl);
}

List* list_insertFirst(List* pl, const void*pElem){
    NodeList *pn;
    
    if (!pl || !pElem)
        return NULL;
    
    if ((pn = nodelist_ini()) == NULL)
        return NULL;
    
    pn->info = pl->copy_element_function(pElem); /*CdE*/

    // Caso 1: lista vacía
    if (list_isEmpty(pl) == TRUE) {
	pn->next = pn;		// El next del nodo apunta a sí mismo
	pl->last = pn;
    } 
    // Caso 2: lista no vacía
    else {
	pn->next = pl->last->next;	// El next del nodo apunta al primer nodo
	pl->last->next = pn; 	// El next del último nodo apunta al nuevo
    }
    
    return pl;
}

List* list_insertLast(List* pl, const void*pElem){
    NodeList *pn;
    
    if (!pl || !pElem)
        return NULL;
    
    if ((pn = nodelist_ini()) == NULL)
        return NULL;
    
    pn->info = pl->copy_element_function(pElem); //CdE

    //Caso 1: lista vacía
    if (list_isEmpty(pl)){
        pn->next = pn;
        pl->last = pn;
        return pl;
    }
    //Caso 2: lista con elementos
    pn->next = pl->last->next;	// El next de pn apunta al primer nodo
    pl->last->next = pn; 	// El next del que era el último nodo apunta a pn
    pl->last = pn;
    
    return pl;
}

List* list_insertInOrder(List *pl, const void*pElem){
    NodeList *pn, *aux;
    
    if (!pl || !pElem)
        return NULL;
    
    if ((pn = nodelist_ini()) == NULL)
        return NULL;

    pn->info = pl->copy_element_function(pElem);
    
    if (list_isEmpty(pl)){
        pn->next = pn;
        pl->last = pn;
        return pl;
    }
    aux=pl->last->next; /* Apunta al primer nodo de la lista*/
    
    /*Si hay que insertar al principio:*/
    if (pl->cmp_element_function(pElem, aux->info) < 0){
        nodelist_free (pn, pl->destroy_element_function);
        return list_insertFirst (pl, pElem);
    }
    while ((aux != pl->last) && (pl->cmp_element_function(pElem,aux->next->info) > 0)) 
        aux = aux->next;
    
    if (aux == pl->last){
        pl->last = pn;
    }

    pn->next = aux->next;
    aux->next = pn;
    
    return pl;
}

void* list_extractFirst(List* pl){
    NodeList *paux;
    void*pElem;
    
    if (!pl || list_isEmpty(pl))
        return NULL;
            
    pElem = pl->last->next->info;
    pl->last->next->info = NULL;
       
    // Caso 1: lista de un nodo
    if (pl->last->next == pl->last) {
	nodelist_free (pl->last, pl->destroy_element_function); // Se libera el nodo
	pl->last = NULL; 		// Se deja la lista vacía
    } 
    // Caso 2: lista de varios nodos
    else {
	paux = pl->last->next;		// paux apunta al primer nodo
	pl->last->next = paux->next; 	// El next del último nodo apunta al segundo nodo
	nodelist_free (paux, pl->destroy_element_function); // Se libera pn
    }
    return pElem;
}

void* list_extractLast(List* pl){
    NodeList *paux;
    void*pElem;
    
    if (!pl || list_isEmpty(pl))
        return NULL;

    pElem = pl->last->info;
    pl->last->info = NULL; /*Importante!*/
    
    // Caso 1: lista de un nodo
    if (pl->last->next == pl->last) {
	nodelist_free (pl->last, pl->destroy_element_function); // Se libera el nodo
	pl->last = NULL; 		// Se deja la lista vacía
	return pElem;
    } 

    // Caso 2: lista de varios nodos
    for (paux=pl->last; paux->next!=pl->last; paux=paux->next);  // Se sitúa pn en el penúltimo nodo

    paux->next = pl->last->next;  // El next de pn apunta al primer nodo
    nodelist_free(pl->last, pl->destroy_element_function); //Se libera el último nodo
    pl->last = paux;            //Ahora el último nodo es paux	
    return pElem;
}

Bool list_isEmpty(const List* pl){
    if (!pl || pl->last == NULL)
	return TRUE;
    return FALSE;
}

const void* list_get(const List* pl, int index){
    NodeList *aux;
    int i=0;
    if (!pl || list_isEmpty(pl) || index > list_size(pl)){
	return NULL;
    }
    aux = pl->last;
    do{
        i++;
        aux = aux->next;
    } while ((aux != pl->last) && (i<index));
    if (i==index)
        return aux->info;
    else
        return NULL;
}


int list_size(const List* pl){
    NodeList *aux = pl->last;
    int i = 0;
    if (aux == NULL)  /*Lista vacía*/
        return i;
    //Si no está vacía, al menos tiene 1 elemento
    do {
        i++;
        aux = aux->next;
    }while (aux != pl->last);
    return i;
}

int list_print(FILE *fd, const List* pl){
    NodeList *paux;
    int count = 0;
    
    if (!pl || list_isEmpty(pl) == TRUE)
        return 0;
    
    count += fprintf (fd, "Lista con %hu elementos: \n", list_size(pl));
    /* Al menos hay 1 elemento. Con el do-while al principio se sitúa en el primero de la lista*/
    paux = pl->last;
    do{
        paux = paux->next;
        count += pl->print_element_function(fd, paux->info);
        count += fprintf(fd, "\n");
    } while (paux!= pl->last);  /*el último también se imprime por el orden entre avanzar e imprimir*/
        
    return count;
}
