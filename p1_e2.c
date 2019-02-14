#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "types.h"
#include "node.h"
#include "graph.h"

int main(){

  Node *n1;
  Node *n2;
  n1=node_ini();
  n2=node_ini();
  node_setId(n1,111);
  node_setName(n1,"first");
  node_setId(n2,222);
  node_setName(n2,"second");
  Graph *g;
  g=graph_ini();


}