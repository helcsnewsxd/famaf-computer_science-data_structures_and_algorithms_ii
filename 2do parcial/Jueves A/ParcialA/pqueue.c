#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

#define asserting false
    /**
     * @brief Para que no ande lento el programa
     * Se pone false si se quiere ejecutar los assert
     * Se pone true en caso contrario
     */

typedef struct s_node * node;

struct s_pqueue {
    node queue;
    unsigned int size;
};

struct s_node {
    pqueue_elem elem;
    unsigned int priority;
    node next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    bool inv = true;
    if(q->queue != NULL){
        unsigned int ant_priority = q->queue->priority;
        node act = q->queue->next;
        while(act != NULL){
            inv &= ant_priority <= act->priority;
            act = act->next;
        }
    }
    return inv;
}

pqueue pqueue_empty(void) {
    pqueue q = malloc(sizeof(struct s_pqueue));
    q->queue = NULL;
    q->size = 0;
    assert(asserting || (invrep(q) && pqueue_is_empty(q)));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(asserting || invrep(q));
    struct s_node *new_node = create_node(e, priority);
    if(q->queue == NULL || priority < q->queue->priority){
        node aux = q->queue;
        q->queue = new_node;
        new_node->next = aux;
    }else{
        node act = q->queue;
        while(act->next != NULL && priority >= act->next->priority){
            act = act->next;
        }
        node aux = act->next;
        act->next = new_node;
        new_node->next = aux;
    }
    q->size++;
    assert(asserting || (invrep(q) && !pqueue_is_empty(q)));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(asserting || invrep(q));
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(asserting || (invrep(q) && !pqueue_is_empty(q)));
    return q->queue->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(asserting || (invrep(q) && !pqueue_is_empty(q)));
    return q->queue->priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(asserting || invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(asserting || (invrep(q) && !pqueue_is_empty(q)));
    node node_to_erase = q->queue;
    q->queue = node_to_erase->next;
    node_to_erase = destroy_node(node_to_erase);
    q->size--;
    assert(asserting || invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(asserting || invrep(q));
    if(q->queue != NULL){
        node node_to_erase, next_node_to_erase;
        node_to_erase = q->queue;
        next_node_to_erase = node_to_erase->next;
        while(next_node_to_erase != NULL){
            node_to_erase = destroy_node(node_to_erase);
            node_to_erase = next_node_to_erase;
            next_node_to_erase = next_node_to_erase->next;
        }
        node_to_erase = destroy_node(node_to_erase);
    }
    free(q);
    q = NULL;
    assert(asserting || q == NULL);
    return q;
}
