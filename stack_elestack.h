
#ifndef STACK_H
#define STACK_H

#include "elestack.h"
#include "types.h"

typedef struct _Stack Stack;
/**------------------------------------------------------------------
Initialize the stack reserving memory. Output: NULL if there was an error or the stack if it went well
----------------------------------------------------*/
Stack * stack_ini();
/**------------------------------------------------------------------
Remove the stack Input: the stack to be removed
------------------------------------------------------------------*/
void stack_destroy(Stack *);
/**------------------------------------------------------------------
Insert an EleStack in the stack. Input: an EleStack and the stack where to insert it. Output: ERROR if you can not
insert it or OK if it succeeds
------------------------------------------------------------------*/
Status stack_push(Stack *, const EleStack *);
/**------------------------------------------------------------------
Extract an EleStack in the stack. Input: the stack from which to extract it. Output: NULL if you can not extract it
or the extracted EleStack if it succeeds. Note that the stack will be modified
------------------------------------------------------------------*/
EleStack * stack_pop(Stack *);
/**------------------------------------------------------------------
Check if the stack is empty. Input: stack. Output: TRUE if it is empty or FALSE if it is not
------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack *);
/**------------------------------------------------------------------
Check if the stack is full. Input: stack. Exit: TRUE if it is full or FALSE if it is not
------------------------------------------------------------------*/
Bool stack_isFull(const Stack *);
/**------------------------------------------------------------------
Print the entire stack, placing the EleStack on top at the beginning of printing (and one EleStack per line). Input:
stack and file where to print it. Output: Returns the number of written characters.
------------------------------------------------------------------*/
int stack_print(FILE*, const Stack*);
#endif 
