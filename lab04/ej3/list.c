#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include<stdlib.h>
#include "list.h"

struct _list{
	list_elem elem;
	list next;
};

list list_empty(){
	return NULL;
}

list list_addl(list l,list_elem e){
	list q = malloc(sizeof(struct _list));
	q->elem=e;
	q->next=l;
	l=q;
	return l;
}

bool list_is_empty(list l){
	return l==list_empty();
}

list_elem list_head(list l){
	assert(!list_is_empty(l));
	return l->elem;
}

list list_tail(list l){
	assert(!list_is_empty(l));
	list q = l->next;
	l->next = list_empty();
	l=list_destroy(l);
	l = q;
	return l;
}

unsigned int list_length(list l){
	unsigned int c = 0;
	list q = l;
	while(!list_is_empty(q)){
		c++;
		q=q->next;
	}
	return c;
}

list_elem list_index(list l,unsigned int n){
	assert(n<list_length(l));
	unsigned int c=0;
	list q=l;
	while(c!=n){
		c++;
		q=q->next;
	}
	return q->elem;
}

list list_addr(list l,list_elem e){
	if(list_is_empty(l)){
		l=list_addl(l,e);
	}else{
		list q = l;
		while(!list_is_empty(q->next)){
			q=q->next;
		}
		q->next=malloc(sizeof(struct _list));
		(q->next)->elem=e;
		(q->next)->next=list_empty();
	}
	return l;
}

list list_concat(list l0,list l1){
	list q = l1;
	while(!list_is_empty(q)){
		l0=list_addr(l0,q->elem);
		q=q->next;
	}
	return l0;
}

list list_copy(list l){
	list lc = list_empty(),q = l;
	while(!list_is_empty(q)){
		lc=list_addr(lc,q->elem);
		q=q->next;
	}
	return lc;
}

list list_take(list l,unsigned int n){
	if(n >= list_length(l)){
		return l;
	}else if(n==0){
		l=list_destroy(l);
		l = list_empty();
		return l;
	}else{
		list q=l;
		while(n!=1){
			q=q->next;
			n--;
		}
		list k = q->next;
		q->next = list_empty();
		l=list_destroy(k);
		return l;
	}
}

list list_drop(list l,unsigned int n){
	while(n!=0 && !list_is_empty(l)){
		l=list_tail(l);
		n--;
	}
	return l;
}

list list_print(list l){
	list k = list_copy(l);
	printf("[");
	while(!list_is_empty(k)){
		printf(" %d",list_head(k));
		k=list_tail(k);
	}
	printf("]\n\n");
	k=list_destroy(k);
	return l;
}

//~ Destructores
list list_destroy(list l){
	if(!list_is_empty(l)){
		list q=l;
		while(!list_is_empty(q)){
			list k=q->next;
			free(q);
			q=k;
		}
	}
	return l;
}
