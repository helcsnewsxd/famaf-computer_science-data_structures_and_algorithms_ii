#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

typedef struct s_node * pqnode;
typedef pqnode * parr;

struct s_pqueue {
    parr priority_arr;
    size_t size;
    priority_t min_priority;
    priority_t max_using_priority;
};

struct s_node {
    pqnode next;
    pqueue_elem elem;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->next = NULL;
    new_node->elem = e;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}


static bool invrep(pqueue q) {
	size_t size = 0;
	priority_t min_priority = q->min_priority;
	priority_t max_using_priority = 0;
	
	while(q->priority_arr[max_using_priority] == NULL && max_using_priority <= min_priority){
		max_using_priority++;
	}
	for(unsigned int i = 0; i <= min_priority; i++){
		pqnode act = q->priority_arr[i];
		while(act != NULL){
			size++;
			act = act->next;
		}
	}
	
	// Campos de la pqueue
	bool inv = size == q->size && max_using_priority == q->max_using_priority;
	
	// PQueue vacía
	if(size == 0){
		inv = inv && max_using_priority == q->min_priority + 1;
	}
	
    return inv;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->priority_arr = calloc(sizeof(struct s_node), min_priority+1);
    q->size = 0;
    q->min_priority = min_priority;
    q->max_using_priority = min_priority+1;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
	if(priority < q->max_using_priority){
		q->max_using_priority = priority;
	}
	pqnode queue = q->priority_arr[priority];
	if(queue == NULL){
		q->priority_arr[priority] = create_node(e);
	}else{
		while(queue->next != NULL){
			queue = queue->next;
		}
		queue->next = create_node(e);
	}
	q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->priority_arr[q->max_using_priority]->elem;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->max_using_priority;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqnode aux = q->priority_arr[q->max_using_priority];
    q->priority_arr[q->max_using_priority] = aux->next;
    aux = destroy_node(aux);
    if(q->priority_arr[q->max_using_priority] == NULL){
		while(q->priority_arr[q->max_using_priority]==NULL && q->max_using_priority <= q->min_priority){
			q->max_using_priority++;
		}
	}
	q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    while(q->size != 0){
		q = pqueue_dequeue(q);
	}
	free(q->priority_arr);
	free(q);
	q = NULL;
    return q;
}

