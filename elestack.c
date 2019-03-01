#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "node.h"
#include "elestack.h"
#include "stack_elestack.h"  


struct _EleStack {
	int *e;
};

EleStack * EleStack_ini(){

	EleStack *ele;

	ele=(EleStack *)calloc(1,sizeof(EleStack));
	ele->e = (int*)calloc(1,sizeof(int));

	if (ele==NULL){
		return NULL;
	}
	return ele;
}

void EleStack_destroy(EleStack *ele){

	if(ele==NULL){
		return;
	}
	if(ele->e !=NULL){
		free(ele->e);
	}else
	free(ele);
	
}

Status EleStack_setInfo(EleStack *ele, int* n) {

	if(!ele || !n)
		return ERROR;
	
	if(ele->e == NULL)
		return ERROR;
	*(ele->e) = *n;
	
	return OK;
}

int* EleStack_getInfo(EleStack *ele){

	if(!ele){
		return NULL;
	}
	return ele->e;
}

EleStack* EleStack_copy(const EleStack *ele){
	int aux = 0;
	EleStack *ele2;

	ele2 = (EleStack*)calloc(1,sizeof(EleStack));

	aux = *(ele->e);
	*(ele2->e) = aux;

	return ele2;

}

Bool EleStack_equals(const EleStack *ele1, const EleStack *ele2){

	if(!ele1 || !ele2){
		return FALSE;
	}

	if(*(ele1->e) == *(ele2->e)) {
		return TRUE;
	}
	return FALSE;

}

int EleStack_print(FILE *f, const EleStack *ele){
	int num_chars;

	if(!f || !ele){
		return -1;
	}

	num_chars = fprintf(f, "%d\n", *(ele->e));

	return num_chars;

}

double avgElestack ( Stack *s){

	Stack *s2;
	EleStack *ele;
	double counter;

	s2 = stack_ini();

	if(s2==NULL){
		return -1;
	}

	while(stack_isEmpty(s)==FALSE{
		ele=stack_pop(s->item[s->top]);
		stack_push(s,ele);

	}

	return counter;
}
