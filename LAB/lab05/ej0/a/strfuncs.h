#ifndef _STRFUNCS_
#define _STRFUNCS_

size_t string_length(const char *str);
// PRE: str != NULL
// Calcula la longitud de la cadena apuntada por str

char *string_filter(const char *str, char c);
// Devuelve una cadena en memoria dinámica que se obtiene tomando los carácteres de str que son distintos de c

#endif
