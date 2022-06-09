#include<stdio.h>
#include "mybool.h"
#include "array_helpers.h"

unsigned int array_from_file(int array[],
           unsigned int max_size,
           const char *filepath) {
    //your code here!!!
	unsigned int array_size;
	FILE *f = fopen(filepath,"r");
	fscanf(f,"%u",&array_size);
	
	if(array_size > max_size){
		//Accederia a memoria no habilitada
		array_size = max_size;
	}
	
	for(unsigned int i = 0;i<array_size;i++){
		fscanf(f,"%d",&array[i]);
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

mybool array_is_sorted(int a[],unsigned int length){
	mybool estaOrdenado = true;
	
	for(unsigned int i=1;i<length;i++){
		estaOrdenado &= a[i]>=a[i-1];
	}
	
	return estaOrdenado;
}

void array_swap(int a[],unsigned int i,unsigned int j){
	int aux = a[i];
	a[i] = a[j];
	a[j] = aux;
}

void reverse_array(int a[],unsigned int length){
	for(unsigned int i=0;i<length/2;i++){
		array_swap(a,i,length-i-1);
	}
}
