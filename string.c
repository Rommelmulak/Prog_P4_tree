
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void destroy_string_function(void* n){
	free((char*)n);
}

void * copy_string_function(const void* n){
	char* cadena;
	/*CdE*/
	if (n == NULL){
		return NULL;
	}
	cadena = (char*)malloc((1+strlen((char*)n))*sizeof(char));
	strcpy(cadena, (char*)n);
	return cadena;
}

int print_string_function(FILE * fichero, const void* n){
	if (fichero != NULL && n != NULL)
		return fprintf(fichero, "%s\n", (char*)n);
	return -1;
}

int cmp_string_function(const void* n1, const void* n2){
	if (n1 != NULL && n2 != NULL){
		return strcmp((char*)n1, (char*)n2);
	}
	return -1;
}
