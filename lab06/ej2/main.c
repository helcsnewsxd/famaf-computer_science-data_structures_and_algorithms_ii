#include<stdio.h>
#include "string.h"

//------ Main de Testing ---------

int main(void){
	string a = string_create("hola pa");
	string b = string_create("xd");
	if(string_less(a,b))printf("a<b\n");
	else printf("b<a\n");
	b = string_destroy(b);
	b = string_create("hola pa ");
	if(string_eq(a,b))printf("a=b\n");
	else printf("a!=b\n");
	printf("%u %u\n",string_length(a),string_length(b));
	string_dump(a,stdout);
	printf("\n");
	string_dump(b,stdout);
	a=string_destroy(a);
	b=string_destroy(b);
	return 0;
}
