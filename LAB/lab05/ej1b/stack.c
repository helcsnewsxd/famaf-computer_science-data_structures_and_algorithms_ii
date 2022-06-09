#include<stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct _stack_node *nodo;

struct _s_stack{
    nodo pila;
    unsigned int size;
};

struct _stack_node{
	stack_elem elem;
	nodo next;
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
	stack nuevo_stack = malloc(sizeof(struct _s_stack));
    nuevo_stack->size = 0;
    nuevo_stack->pila = NULL;
    return nuevo_stack;
}

stack stack_push(stack s, stack_elem e){
	printf("Antes\n");
	stack_debug(s);
	assert(stack_invrep(s));

    s->size++;
    nodo aux = malloc(sizeof(struct _stack_node));
	aux->elem = e;
	aux->next = s->pila;
	s->pila = aux;

	assert(stack_invrep(s));
	printf("Despues\n");
	stack_debug(s);
	return s;
}

stack stack_pop(stack s){
	assert(!stack_is_empty(s));
	assert(stack_invrep(s));
	printf("Antes\n");
	stack_debug(s);
	
    nodo aux = (s->pila)->next;
	free(s->pila);
	s->pila = aux;
	s->size--;

	printf("Despues\n");
	stack_debug(s);
	assert(stack_invrep(s));
	return s;
}

unsigned int stack_size(stack s){
	assert(stack_invrep(s));
	return s->size;
}

stack_elem stack_top(stack s){
	assert(!stack_is_empty(s));
	assert(stack_invrep(s));
	return (s->pila)->elem;
}

bool stack_is_empty(stack s){
	return s!=NULL && s->size==0;
}

stack_elem *stack_to_array(stack s){
	assert(stack_invrep(s));
	unsigned int length = stack_size(s);
	if(length == 0)return NULL;
	stack_elem *array = calloc(length,sizeof(stack_elem));
	nodo act = s->pila;
	length--;
	while(act != NULL){
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
    free(s->pila);
    free(s);
    s = NULL;
	return s;
}
