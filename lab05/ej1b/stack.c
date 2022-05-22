#include<stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack{
	stack_elem elem;
	stack next;
	unsigned int size;
};

void stack_debug(stack s){
	int *a = stack_to_array(s);
	size_t length = stack_size(s);
	printf("Size = %lu\n",length);
	for(unsigned int i=0;i<length;i++){printf("(%d)-",a[i]);}
	printf("\n=========================\n\n");
	free(a);
}

bool stack_invrep(stack s){
	return stack_is_empty(s) || s->size > 0;
}

stack stack_empty(){
	return NULL;
}

stack stack_push(stack s, stack_elem e){
//	printf("Antes\n");
//	stack_debug(s);
	assert(stack_invrep(s));
	stack aux = malloc(sizeof(struct _s_stack));
	aux->elem = e;
	aux->next = s;
	s = aux;

	if(stack_is_empty(s->next)){ s->size = 1; }
	else{ s->size = (s->next)->size + 1; }
	assert(stack_invrep(s));
//	printf("Despues\n");
//	stack_debug(s);
	return s;
}

stack stack_pop(stack s){
	assert(!stack_is_empty(s));
	assert(stack_invrep(s));
//	printf("Antes\n");
//	stack_debug(s);
	stack aux = s->next;
	free(s);
	s = aux;
//	printf("Despues\n");
//	stack_debug(s);
	assert(stack_invrep(s));
	return s;
}

unsigned int stack_size(stack s){
	assert(stack_invrep(s));
	if(stack_is_empty(s))return 0;
	return s->size;
}

stack_elem stack_top(stack s){
	assert(!stack_is_empty(s));
	assert(stack_invrep(s));
	return s->elem;
}

bool stack_is_empty(stack s){
	return s==NULL;
}

stack_elem *stack_to_array(stack s){
	assert(stack_invrep(s));
	unsigned int length = stack_size(s);
	if(length == 0)return NULL;
	stack_elem *array = calloc(length,sizeof(stack_elem));
	stack act = s;
	length--;
	while(!stack_is_empty(act)){
		array[length] = act->elem;
		act=act->next;
		length--;
	}
	return array;
}

stack stack_destroy(stack s){
	assert(stack_invrep(s));
	while(!stack_is_empty(s)){
		s = stack_pop(s);
	}
	return s;
}
