#ifndef _LIST_
#define _LIST_

#include<stdbool.h>

typedef struct _list * list;

typedef int list_elem;

//~ Constructores
list list_empty();
/**
 * Crea una lista vacía
**/

list list_addl(list l,list_elem e);
/**
 * Agrega un elemento al inicio de la lista
**/


//~ Operaciones
bool list_is_empty(list l);
/**
 * Devuelve true si la lista es vacía
**/

list_elem list_head(list l);
/**
 * Devuelve el primer elemento de la lista
 * PRE: !list_is_empty(l)
**/

list list_tail(list l);
/**
 * Elimina el primer elemento de la lista
 * PRE: !list_is_empty(l)
**/

unsigned int list_length(list l);
/**
 * Devuelve el tamaño de la lista
**/

list_elem list_index(list l,unsigned int n);
/**
 * Devuelve el n-ésimo elemento de la lista
 * PRE: n < list_length(l)
**/

list list_addr(list l,list_elem e);
/**
 * Agrega un elemento a la derecha de la lista
**/

list list_concat(list l0,list l1);
/**
 * Coloca en l0 los elementos de l1 al final y en el mismo orden
**/

list list_copy(list l);
/**
 * Devuelve una nueva lista copia de la dada
**/

list list_take(list l,unsigned int n);
/**
 * Toma los primeros n elementos de la lista y borra los demás
**/

list list_drop(list l,unsigned int n);
/**
 * Elimina los primeros n elementos de la lista
**/

list list_print(list l);
/**
 * Muestra por pantalla la lista resultante
**/

//~ Destructores
list list_destroy(list l);
/**
 * Libera memoria en caso que sea necesario
**/

#endif
