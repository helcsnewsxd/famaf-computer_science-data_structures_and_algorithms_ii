#include<stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "queue.h"

struct s_queue {
    /*
     * COMPLETAR para el apartado b)
     */
    struct s_node *first;
};

struct s_node {
    queue_elem elem;
    struct s_node *next;
};

static struct s_node *create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool invrep(queue q) {
    return q != NULL;
}

void debug(queue q,bool b){
	// Print a queue like an array with the size -> First element in the array correspond to the first element in the queue
	printf("======================================================================================\n");
	if(b){printf("Despues:\n");}
	else {printf("Antes:\n");}

	if(q==NULL){
		printf("No hay queue\n");
	}else{
		printf("SIZE = %u\n",queue_size(q));
		struct s_node *p=q->first;
		printf("[ ");
		while(p!=NULL){
			printf("%d ",p->elem);
			p=p->next;
		}
		printf(" ]\n");
	}
	printf("======================================================================================\n");
}

queue queue_empty(void) {
    queue q=malloc(sizeof(struct s_queue));
    q->first=NULL;
    assert(invrep(q) && queue_is_empty(q));
    return q;
}

queue queue_enqueue(queue q, queue_elem e) {
//	debug(q,0);
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    if (q->first==NULL) {
        q->first = new_node;
    } else {
    	struct s_node *p=q->first;
    	while(p->next!=NULL){ p=p->next; }
    	p->next=new_node;
    }
    assert(invrep(q) && !queue_is_empty(q));
//    debug(q,1);
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->first == NULL;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->first->elem;
}
unsigned int queue_size(queue q) {
    assert(invrep(q));
    unsigned int size=0;
    struct s_node *p=q->first;
    while(p!=NULL){
		p=p->next;
		size++;
    }
    return size;
}

queue queue_dequeue(queue q) {
//	debug(q,0);
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node * killme=q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    assert(invrep(q));
//    debug(q,1);
    return q;
}

queue queue_destroy(queue q) {
//	debug(q,0);
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
//    debug(q,1);
    return q;
}
