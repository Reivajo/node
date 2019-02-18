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
  FILE *file;
  file=fopen("file.txt","w");
  n1=node_ini();
  n2=node_ini();
  node_setId(n1,111);
  node_setName(n1,"first");
  node_setId(n2,222);
  node_setName(n2,"second");
  g=graph_ini();
  fprintf(file,"Inserting node 1 ... result ...: ");
  if(graph_insertNode(g, n1)==ERROR){
  	fprintf(file,"0");
  }else{
  	fprintf(file,"1");
  }
  fprintf(file,"Inserting node 2 ... result ...: ");
  if(graph_insertNode(g, n2)==ERROR){
  	fprintf(file,"0");
  }else{
  	fprintf(file,"1");
  }
  graph_insertEdge(g, node_getId(n2), node_getId(n1));
  fprintf(file,"Connected node 1 and node 2: ");
  if(graph_areConnected(g,node_getId(n1), node_getId(n2))==TRUE){
  	fprintf(file,"Yes");
  }else{
  	fprintf(file,"No");
  }
  
  fprintf(file,"Connected node 2 and node 1: ");

  if(graph_areConnected(g,node_getId(n2), node_getId(n1))==TRUE){
  	fprintf(file,"Yes");
  }else{
  	fprintf(file,"No");
  }
  fprintf(file,"Inserting node 2 ... result ...: ");
  if(graph_insertNode(g, n2)==ERROR){
  	fprintf(file,"0");
  }else{
  	fprintf(file,"1");
  }
  fprintf(file,"Graph");

  graph_print(file,g);

  fclose(file);
  return 0;
}

