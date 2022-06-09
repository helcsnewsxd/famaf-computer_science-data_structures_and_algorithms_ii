#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 34, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n", sizeof(messi.name),sizeof(messi.age),sizeof(messi.height),sizeof(messi));

    return EXIT_SUCCESS;
}

/**
	La suma de todos los miembros no coincide con el total (seguramente porque al guardarse como una estructura, necesita un identificador o ciertos datos que la
	prepresenten)

	El tamaño del campo name NO depende del nombre que contiene, sino que siempre tiene habilitados los 30 bytes con los que se definió. Sin embargo, no se le puede
	asignar un nombre mayor a este tamaño
**/
