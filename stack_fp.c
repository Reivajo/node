#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h>
#include "stack_fp.h"

#define MAXSTACK 100 
#define EMPTY_STACK -1

extern int errno;

struct _Stack { 
	int top;
	void * item[MAXSTACK];
	P_stack_ele_destroy pf_destroy; 
	P_stack_ele_copy pf_copy; 
	P_stack_ele_print pf_print;
};

Stack *stack_ini (P_stack_ele_destroy fd, P_stack_ele_copy fc, P_stack_ele_print fp) {
	Stack *s;
	int i;
	s = (Stack*)malloc(sizeof(Stack));
	if (!s) {
		fprintf(stderr, "%s", strerror(errno));
	return NULL;
	}
	/* Initialize top and assign function pointers */
	s->top = -1; 
	s->pf_copy = fc;
	s->pf_destroy = fd;
	s->pf_print = fp;
	/* assign the pointers of the elements */
	for (i=0; i< MAXSTACK; i++)
		s->item[i] = NULL;
	return s;
}
void stack_destroy(Stack* s) { 
	if (!s) 
		return;
	while (s->top != EMPTY_STACK) {
		s->pf_destroy( s->item[s->top]);
		s->top --; }
		free(s);
}

Status stack_push(Stack *s, const void *ele) {
	void *buff = NULL;

	if(!s || !ele)
		return ERROR;

	if(stack_isFull(s))
		return ERROR;
	buff = s->pf_copy(ele);
	if(buff == NULL)
		return ERROR;
	s->top++;
	s->item[s->top] = buff;

	return OK;

}

void *stack_pop(Stack *s) {
	void *ele;

	if(!s)
		return NULL;
	if(stack_isEmpty(s))
		return NULL;
	ele = s->item[s->top--];

	return ele;
}

void *stack_top(const Stack *s) {
	void *ele;

	if(s == NULL)
		return NULL;
	if(stack_isEmpty(s))
		return NULL;

	ele = s->pf_copy(s->item[s->top]);
	if(ele == NULL)
		return NULL;

	return ele;
}


Bool stack_isEmpty(const Stack *s) {
	if(s == NULL)
		return TRUE;

	if(s->top == EMPTY_STACK)
		return TRUE;
	return FALSE;

}

Bool stack_isFull(const Stack *s) {
	if(s == NULL)
		return TRUE;

	if(s->top == MAXSTACK - 1)
		return TRUE;
	return FALSE;
}

int stack_print(FILE *f, const Stack *s) {
	int i, n = 0;

	if(!f || !s)
		return -1;
	for (i = s->top; i >= 0; i--) {
		n += s->pf_print(f, s->item[i]);
		fprintf(f, "\n");
	}
	return n;
}
