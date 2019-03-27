#ifndef LIST_H
#define	LIST_H

#include "types.h"

typedef struct _List List;

/* Tipos de los punteros a funci�n soportados por la lista */
typedef void (*destroy_element_function_type)(void*);
typedef void (*(*copy_element_function_type)(const void*));
typedef int (*print_element_function_type)(FILE *, const void*);
typedef int (*cmp_element_function_type)(const void*, const void*);


List* list_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4);
void list_destroy(List* list);

List* list_insertFirst(List* list, const void*elem);
List* list_insertLast(List* list, const void*elem);
List* list_insertInOrder(List *list, const void*pElem);

void* list_extractFirst(List* list);
void* list_extractLast(List* list);

Bool list_isEmpty(const List* list);

const void* list_get(const List* list, int index);
int list_size(const List* list);

int list_print(FILE *fd, const List* list);

#endif