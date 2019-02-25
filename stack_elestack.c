#include <stdio.h>
#include <stdlib.h>
#include "stack_elestack.h"

# define MAXSTACK 1024
struct _Stack {
 int top;
 EleStack * item[MAXSTACK];
};

Stack * stack_ini(){
	Stack *s;
	int i;

	s=(Stack *)calloc(1,sizeof(Stack));

	if(s==NULL){
		return NULL;
	}
	for (i=0; i<MAXSTACK; i++) {
		s->item[i] = NULL;
	}
	s->top = -1;
	return s;
}

void stack_destroy(Stack *s){

	int i;
	if(s !=NULL){
	for(i=0;i<s->top;i++){
		EleStack_destroy(s->item[i]);
		s->item[i]=NULL;
	}
	free(s);
}

}

Status stack_push(Stack *s, const EleStack *ele) {

	EleStack *aux = NULL;
	 if (s == NULL || ele == NULL || stack_isFull(s) == TRUE) {
		return ERROR;
	}
	aux = EleStack_copy(ele);

	if (aux == NULL) {
		return ERROR;
	}
	s->top++;
	s->item[s->top] = aux;
	return OK;
}


EleStack * stack_pop(Stack *s){
	EleStack *ele;
	if (s == NULL || stack_isEmpty(s) == TRUE) {
		return NULL;
	}
	ele = s->item[s->top];
	s->item[s->top] = NULL;
	s->top--;
	
	return ele;
}

Bool stack_isEmpty(const Stack *s){

	if(s==NULL){
		return TRUE;
	}
	if(s->top == -1){
		return TRUE;
	}
	return FALSE;

}

Bool stack_isFull(const Stack *s){

	if(s==NULL){
		return TRUE;
	}
	if(s->top == MAXSTACK-1){
		return TRUE;
	}
	return FALSE;

}

int stack_print(FILE *f, const Stack *s){

	int i=0;
	int num_chars = 0;

	if(!f || !s){
		return -1;
	}

	for(i=s->top;i>-1;i--){

		num_chars+=EleStack_print(f,s->item[i]);
	}

	return num_chars;

}