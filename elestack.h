#ifndef ELESTACK_H
#define ELESTACK_H

#include "types.h"

typedef struct _EleStack EleStack;
/**------------------------------------------------------------------
Initialize a stack EleStack. Output: Pointer to the initialized EleStack or NULL in case of error
------------------------------------------------------------------*/
EleStack * EleStack_ini();
/**------------------------------------------------------------------
Remove an EleStack. Entry: EleStack to destroy.
------------------------------------------------------------------*/
void EleStack_destroy(EleStack *);
/**------------------------------------------------------------------
Modify the data of an EleStack. Entry: The EleStack to be modified and the content to be saved in that EleStack.
Output: OK or ERROR
------------------------------------------------------------------*/
Status EleStack_setInfo(EleStack *, void*);
/**------------------------------------------------------------------
Returns the EleStack content. Entry: The EleStack. Output: The content of EleStack or NULL if there has been an
error.
------------------------------------------------------------------*/
void * EleStack_getInfo(EleStack *);
/**------------------------------------------------------------------
Copy one EleStack in another, reserving memory. Input: the EleStack to copy. Output: Returns a pointer to the
copied EleStack or NULL in case of error.
------------------------------------------------------------------*/
EleStack * EleStack_copy(const EleStack *);
/**------------------------------------------------------------------
Compares two EleStack. Entry: two EleStack to compare. Output: Returns TRUE if they are the same and if not
FALSE
------------------------------------------------------------------*/
Bool EleStack_equals(const EleStack *, const EleStack *);
/**------------------------------------------------------------------
Print the EleStack in a file that is already open. Input: File in which it is printed and the EleStack to print. Output:
Returns the number of written characters.
------------------------------------------------------------------*/
int EleStack_print(FILE *, const EleStack *);

#endif
