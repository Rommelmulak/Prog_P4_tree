#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tree.h"
#include "errno.h"
#include "node.h"
#include "types.h"
#include "integer.h"
#include "string.h"

#define DIM 300

char* read_string_from_file(FILE* fichero) {
	char* cadena;
	char aux[DIM];

	fscanf(fichero, "%s\n", aux);
	cadena = (char*)malloc((strlen(aux)+1)*sizeof(char));

	strcpy(cadena, aux);

	return cadena;
}

int main(int argc, char const *argv[]){
	FILE *fichero;
	Tree* tr;
	char* cadena;

	/*CdE*/
	if(argc < 2){
		printf("FALLO EN EL NUMERO DE ARGUMENTOS. Escribe --> ./p4_e4 cadenas.txt\n");
		return 1;
	}

	fichero = fopen(argv[1], "r");

	if (fichero==NULL){
		return 1;
	}

	tr = tree_ini(destroy_string_function, copy_string_function, print_string_function, cmp_string_function);
	/*CdE*/
	if (tr==NULL){
		fclose(fichero);
		return 1;
	}

	while(!feof(fichero)){
		cadena = read_string_from_file(fichero);

		if (tree_insert(tr, cadena) == ERROR){
			fprintf(stdout, "FALLO AL INSERTAR LA CADENA \n");
		}

		free(cadena);
	}

	fclose(fichero);

	printf("Numero de nodos --> %d\n",  tree_numNodes(tr));
	printf("Profundidad --> %d\n",tree_depth(tr));

	tree_inOrder(stdout, tr);
	fprintf(stdout, "\n");

	fprintf(stdout, "Introduce un nodo para buscar en el Arbol (siguiendo el mismo formato que en el fichero de entrada):\n");
	cadena = (char*)malloc(DIM* sizeof(char));
	scanf("%s",cadena);

	if (tree_find(tr, cadena) == TRUE){
		fprintf(stdout, "Elemento encontrado.\n");
	}else{
		fprintf(stdout, "Elemento NO encontrado.\n");
	}
	free(cadena);
	tree_free(tr);

	return 0;
}
