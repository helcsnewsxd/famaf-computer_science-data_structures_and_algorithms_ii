#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

char *parse_filepath(int argc,char *argv[]){
	char *result = NULL;
	
	if(argc != 2){
		printf("Parametros invalidos\n");
		exit(EXIT_FAILURE);
	}
	
	result = argv[1];
	
	return result;
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size){
	FILE *f = fopen(path,"r");
	
	if(f == NULL){
		fprintf(stderr, "File does not exists.\n");
		exit(EXIT_FAILURE);
	}
	
	unsigned int ind = 0u;
	while(!feof(f) && ind < max_size){
		fscanf(f,"%u '%c'\n",&indexes[ind],&letters[ind]);
		ind++;
	}
	
	fclose(f);
	return ind;
}

void acomodar(unsigned int indexes[],char letters[],char sorted[],unsigned int max_size,unsigned int length){
	for(unsigned int i = 0u; i < length; i++){
		if(indexes[i] < max_size){
			sorted[indexes[i]] = letters[i];
		}
	}
}

int main(int argc, char *argv[]) { 
    char *filepath = parse_filepath(argc,argv);
    
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0;
    
	length = data_from_file(filepath,indexes,letters,MAX_SIZE);

	acomodar(indexes,letters,sorted,MAX_SIZE,length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

