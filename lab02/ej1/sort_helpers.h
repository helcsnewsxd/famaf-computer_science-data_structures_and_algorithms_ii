#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdbool.h>

bool goes_before(int x, int y);
/* Abstract total order for sorting algorithms 
   This function return a bool equal to the expression abs(x)<=abs(y)
   Therefore, the order of the array isn't the common order. It's the absolute value order
*/

bool array_is_sorted(int a[], unsigned int length);
/* Checks if the array 'a' is in ascending order */

void swap(int a[], unsigned int i, unsigned int j);
/* Exchanges elements of array 'a' in the given positions 'i' and 'j'
   Array remains the same if the two positions are the same
*/

#endif
