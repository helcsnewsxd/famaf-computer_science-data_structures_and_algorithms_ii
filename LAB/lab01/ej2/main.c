/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

unsigned int array_from_file(int array[],
           unsigned int max_size) {
    //your code here!!!
	unsigned int array_size;
	scanf("%u",&array_size);
	
	if(array_size > max_size){
		//Accederia a memoria no habilitada
		array_size = max_size;
	}
	
	for(unsigned int i = 0;i<array_size;i++){
		scanf("%d",&array[i]);
	}
	
	return array_size;
}

void array_dump(int a[], unsigned int length) {
    //your code here!!!!!
    printf("[");
    for(unsigned int i=0;i<length;i++){
    	if(i!=0){
    		printf(",");
    	}
    	printf(" %d",a[i]);
    }
    printf("]\n");
}


int main() {
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    unsigned int length = array_from_file(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
