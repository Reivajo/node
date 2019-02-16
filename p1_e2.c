#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "types.h"
#include "node.h"
#include "graph.h"

int main(){

  Node *n1;
  Node *n2;
  Graph *g;

  n1=node_ini();
  n2=node_ini();
  node_setId(n1,111);
  node_setName(n1,"first");
  node_setId(n2,222);
  node_setName(n2,"second");
  g=graph_ini();
  graph_insertNode(g, n1);
  graph_insertNode(g, n2);
  graph_insertEdge(g, node_getId(n1), node_getId(n2));


  return 0;
}

