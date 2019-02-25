# define MAXSTACK 1024
struct _Stack {
 int top;
 EleStack * item[MAXSTACK];
};

Stack * stack_ini(){

	Stack *s;
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

STATUS stack_push(Stack *s, const EleStack *ele) {

	EleStack *aux = NULL;
	 if (s == NULL || e == NULL || stack_isFull(s) == TRUE) {
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

	if (s == NULL || stack_isEmpty(s) == TRUE) {
		return NULL;
	}
	  ele = s->item[s->top];
	  s->item[s->top] = NULL;
	  s->top--;
	return e;
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
	int num_chars;

	if(!f || !s){
		return NULL;
	}

	for(i=s->top;i>-1;i--){

		num_chars+=EleStack_print(f,s->item[i]);
	}

	return num_chars;

}