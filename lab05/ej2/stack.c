#include<stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

void stack_debug(stack s){
	printf("Size: %u\nCapacity: %u\n\n",s->size,s->capacity);
	for(unsigned int i=0;i<s->capacity;i++){
		printf("(%d)-",s->elems[i]);
	}printf("\n==================================================\n\n");
}

bool stack_invrep(stack s){
	return s != NULL && s->capacity >= s->size;
}

stack stack_empty(){
	stack s = malloc(sizeof(struct _s_stack));
	s->elems = malloc(sizeof(stack_elem));
	s->size = 0;
	s->capacity = 1;
	assert(stack_invrep(s));
	return s;
}

stack stack_push(stack s,stack_elem e){
//	printf("Antes:\n");stack_debug(s);
	assert(stack_invrep(s));
	if(s->size == s->capacity){
		s->elems = realloc(s->elems,s->capacity*2*sizeof(stack_elem));
		s->capacity *= 2;
	}
	s->elems[s->size] = e;
	s->size++;
//	printf("Despues:\n");stack_debug(s);
	assert(stack_invrep(s));
	return s;
}

stack stack_pop(stack s){
	assert(stack_invrep(s));
	assert(!stack_is_empty(s));
	s->size--;
//	printf("Despues:\n");stack_debug(s);
	assert(stack_invrep(s));
	return s;
}

unsigned int stack_size(stack s){
	assert(stack_invrep(s));
	return s->size;
}

stack_elem stack_top(stack s){
	assert(stack_invrep(s));
	return s->elems[s->size-1];
}

bool stack_is_empty(stack s){
	assert(stack_invrep(s));
	return s->size == 0;
}

stack_elem *stack_to_array(stack s){
	assert(stack_invrep(s));
	stack_elem *array = calloc(s->size,sizeof(stack_elem));
	for(unsigned int i=0;i<s->size;i++){
		array[i] = s->elems[i];
	}
	return array;
}

stack stack_destroy(stack s){
	assert(stack_invrep(s));
	free(s->elems);
	s->size = 0;
	s->capacity = 0;
//	printf("Despues:\n");stack_debug(s);
	return s;
}
