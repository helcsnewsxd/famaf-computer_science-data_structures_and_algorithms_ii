/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

//------- HARDCODEO DE LAS OPERACIONES --------------
abb operations(abb tree,int op){
	if(op==1){
		printf("El árbol en una lista es el siguiente:\n");
		abb_dump(tree);
	}else if(op==2){
		printf("Ingrese el elemento a agregar\n");
		abb_elem e;
		scanf("%d",&e);
		tree=abb_add(tree,e);
	}else if(op==3){
		printf("Ingrese el elemento a eliminar\n");
		abb_elem e;
		scanf("%d",&e);
		tree=abb_remove(tree,e);
	}else if(op==4){
		printf("Ingrese el elemento a agregar\n");
		abb_elem e;
		scanf("%d",&e);
		if(abb_exists(tree,e)){ printf("Existe el elemento %d en el ABB\n",e); }
		else { printf("No existe el elemento %d en el ABB\n",e); }
	}else if(op==5){
		printf("La longitud del ABB es de %u\n",abb_length(tree));
	}else if(op==6){
		printf("La raíz del ABB es %d\n",abb_root(tree));
		printf("El máximo del ABB es %d\n",abb_max(tree));
		printf("El mínimo del ABB es %d\n",abb_min(tree));
	}else if(op!=7){
		printf("Puso mal el número de operación, pruebe nuevamente\n");
	}
	printf("\n");
	return tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

	char *s = "Bienvenido al programa de modificación de árboles. Dado el ya cargado, ¿qué desea hacer?\n"
			"Las opciones son:\n"
			"1 - Mostrar el árbol por pantalla\n"
			"2 - Agregar un elemento\n"
			"3 - Eliminar un elemento\n"
			"4 - Chequear la existencia de un elemento\n"
			"5 - Mostrar la longitud del árbol\n"
			"6 - Mostrar raíz, máximo y mínimo del árbol\n\n"
			"7 - Salir del programa\n\n";
	printf(s);

	int op=0;
	while(op!=7){
		printf("================================================\n");
		printf("Ingrese su consulta\n");
		scanf("%d",&op);
		tree=operations(tree,op);
	}

    tree = abb_destroy(tree);
    return (EXIT_SUCCESS);
}
