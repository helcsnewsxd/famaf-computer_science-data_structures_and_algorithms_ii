#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "strfuncs.h"

size_t string_length(const char *str){
	assert(str != NULL);
	size_t ret = 0;
	while(str[ret] != '\0'){ ret++; }
	return ret;
}

char *string_filter(const char *str, char c){
	if(str == NULL){ return NULL; }

	size_t length = string_length(str), ind = 0;
	for(unsigned int i = 0; i <= length; i++){
		if(str[i] != c){ ind++;}
	}
	char *ret = malloc(ind);
	ind = 0;
	for(unsigned int i = 0; i < length; i++){
		if(str[i] != c){
			ret[ind] = str[i];
			ind++;
		}
	}
	return ret;
}
