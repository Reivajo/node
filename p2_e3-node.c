#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "node.h"
#include "stack_fp.h"


void cleanUp (int ret_value, Node *n, Stack *s){
    node_destroy(n);
    stack_destroy(s);
    
    exit(ret_value);
}


int main(int argc, char** argv) {
    Node *n = NULL;
    Stack *s = NULL;
    int a;
    
    n = node_ini();

    if (!n) 
    	return 1;

    s = stack_ini(node_destroy, node_copy, node_print);

    if(!s)  
    	cleanUp(1, n, s);
    
    node_setId(node_setName(n, "first"), 111);
    if(stack_push(s, n) == ERROR) 
    	cleanUp(1, n, s);
   
    node_setId(node_setName(n, "second"), 22);
    if(stack_push(s, n) == ERROR)
    	cleanUp(1, n, s);        
    
    a = stack_print(stdout, s);

    node_destroy(n);
    
    while (!stack_isEmpty(s)) {
        n = (Node*)stack_pop(s);
        node_destroy(n);
    }
    
    n = NULL;
        
    a = stack_print(stdout, s);
    
    cleanUp(0, n, s);

    return (0);
}
