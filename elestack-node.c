#include "node.h"
#include "elestack.h"
#include "stack_elestack.h"  

struct _EleStack {
	Node* info;
};

EleStack * EleStack_ini(){

	EleStack *ele;

	ele=(EleStack *)calloc(1,sizeof(EleStack));

	if (ele==NULL){
		return NULL;
	}
	return ele;
}

void EleStack_destroy(EleStack *ele){

	if(ele==NULL){
		return NULL;
	}
	node_destroy(ele->info);

	free(ele);
}

Status EleStack_setInfo(EleStack *ele, void* n){

	if(!ele || !n){
		return ERROR;
	}
	if(ele->info){  
		node_destroy(ele->info);
	}

	ele->info=node_copy ((Node*) n);
	if(ele->info ==NULL){
		return ERROR;
	}

	return OK;
}

void * EleStack_getInfo(EleStack *ele){

	if(!ele){
		return NULL;
	}
	return ele->info;
}

EleStack * EleStack_copy(const EleStack *ele){
	
	EleStack *ele2;

	ele2->info=node_copy(ele->info);

	return ele2;

}

Bool EleStack_equals(const EleStack *ele1, const EleStack *ele2){

	if(!ele1 || !ele2){
		return NULL;
	}

	if(node_cmp(ele1->info,ele2->info)==0){
		return TRUE;
	}
	return FALSE;

}

int EleStack_print(FILE *f, const EleStack *ele){
	int num_chars;

	if(!f || !ele){
		return NULL;
	}

	num_chars=node_printf(f, ele->info);

	return num_chars;

}