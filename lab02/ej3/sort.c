#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    /* Needs implementation */

    /* Permutes elements of a[izq..der] and returns pivot such that:
     - izq <= pivot <= der
     - elements in a[izq,pivot) all 'go_before' (according to function goes_before) a[pivot]
     - a[pivot] 'goes_before' all the elements in a(pivot,der]
    */

    unsigned int i = izq+1, j = der;
    unsigned int pivot = izq;
    while(i <= j){
        if(!goes_before(a[i],a[pivot]) && !goes_before(a[pivot],a[j])){
            swap(a, i, j);
        }
        if(goes_before(a[i], a[pivot])){
            i++;
        }
        if(goes_before(a[pivot], a[j])){
            j--;
        }
    }
    swap(a, pivot, j);
    pivot = j;

    return pivot;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
 /* needs implementation */

    /* no implementes partition, ya está implementado en sort_helpers.o
       (no se puede leer, pero en sort_helpers.h vas a encontrar información
        para saber cómo usarlo)
    */

    if(izq < der){
        unsigned int pivot = partition(a, izq, der);
        if(pivot != 0u)quick_sort_rec(a, izq, pivot-1); // I do this because 0u-1 make BOOM (because it's unsigned numbers)
        quick_sort_rec(a, pivot+1, der);
    }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

