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

	return s;
}

void stack_destroy(Stack *s){

	int i;
	for(i=0;i<top;i++){
		EleStack_destroy(s->item[i]);
	}
	free(s);

}
