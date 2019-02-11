#include <stdio.h>
#include <stderror.h>
#include <string.h>
#include "types.h"
#include "node.h"

int main(){
  Node *n1;
  Node *n2;
  n1=Node * node_ini();
  n2=Node * node_ini();
  node_setId(Node * n1, const int 111);
  node_setName(Node * n1, const char* "first");
  node_setId(Node * n2, const int 222);
  node_setName(Node * n2, const char* "second");
  printf("%s %d _ %s %d\n",n1->name,n1->id,n2->name,n2->id);
  int cmp;
  cmp=node_cmp (const Node * n1, const Node * n2);
  if(cmp==0){
    printf("El id de los nodos son iguales")
  }
  else if(cmp=1){
    printf("El id del nodo 1 es mayor que el id del nodo 2");
  }
  else if(cmp=-1){
    printf("El id del nodo 2 es mayor que el id del nodo 1")
  }
}
