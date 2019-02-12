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
  node_print(file, n1);
  node_print(file, n2);
  if(node_cmp(n1,n2)==0){
   fprintf(file,"Are they equal? Yes");
  
  }else {
    fprintf(file,"Are they equal? No");
  }
  fprintf(file,"Id of the first node: %d",node_getId(n1));
  fprintf(file,"The name of the second node is: %s",node_getName(n2));

  node_print(file, n1);
  node_print(file, node_copy(n1));

  if(node_cmp(n1,n2)==0){
   fprintf(file,"Are they equal? Yes");
  
  }else {
    fprintf(file,"Are they equal? No");
  }
  node_destroy(n1);
  node_destroy(n2);

}
