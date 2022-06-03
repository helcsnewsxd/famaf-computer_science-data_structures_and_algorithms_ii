#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

#define asserting false
    // Para que ande más o menos rápido el programa
    // Si asserting es true, no se evalúan los assert
    // Si asserting es false, se evalúan todos los assert

typedef struct s_node * node;

struct s_pstack {
    node stack;
    unsigned int size;
};

struct s_node {
    priority_t priority;
    pstack_elem elem;
    node next;

};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    
    assert(new_node!=NULL);
    
    new_node->priority = priority;
    new_node->elem = e;
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


static bool invrep(pstack s) {
    bool inv = true;
    if(s->size == 0){
        inv = s->stack == NULL;
    }else{
        priority_t ant_priority = s->stack->priority;
        node act = s->stack->next;
        while(act != NULL){
            inv = ant_priority >= act->priority;
            ant_priority = act->priority;
            act = act->next;
        }
    }
    return inv;
}

pstack pstack_empty(void) {
    pstack s = malloc(sizeof(struct s_pstack));
    s->size = 0;
    s->stack = NULL;
    assert(asserting || (invrep(s) && pstack_is_empty(s)));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(asserting || invrep(s));
    struct s_node *new_node = create_node(e, priority);
    
    if(s->stack == NULL || priority >= s->stack->priority){
        node aux = s->stack;
        s->stack = new_node;
        new_node->next = aux;
    }else{
        node act = s->stack;
        while(act->next != NULL && act->next->priority > priority){
            act = act->next;
        }
        node aux = act->next;
        act->next = new_node;
        new_node->next = aux;
    }
    s->size++;

    assert(asserting || (invrep(s) && !pstack_is_empty(s)));
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(asserting || invrep(s));
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(asserting || (invrep(s) && !pstack_is_empty(s)));
    return s->stack->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(asserting || (invrep(s) && !pstack_is_empty(s)));
    return s->stack->priority;
}

unsigned int pstack_size(pstack s) {
    assert(asserting || invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(asserting || (invrep(s) && !pstack_is_empty(s)));
    node node_to_erase = s->stack;
    s->stack = node_to_erase->next;
    node_to_erase->next = NULL;
    node_to_erase = destroy_node(node_to_erase);
    s->size--;
    assert(asserting || invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(asserting || invrep(s));
    if(s->stack != NULL){
        node node_to_erase, next_node_to_erase;
        node_to_erase = s->stack;
        next_node_to_erase = node_to_erase->next;
        while(next_node_to_erase != NULL){
            node_to_erase = destroy_node(node_to_erase);
            node_to_erase = next_node_to_erase;
            next_node_to_erase = next_node_to_erase->next;
        }
        node_to_erase = destroy_node(node_to_erase);
    }
    free(s);
    s = NULL;
    assert(asserting || s == NULL);
    return s;
}

