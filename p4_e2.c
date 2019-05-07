#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"
#include "errno.h"
#include "node.h"
#include "types.h"
#include "integer.h"


int main(int argc, char* argv[1]) {
	FILE* fichero;
	Tree* tr;
	int *entero;

	/*CdE*/
	if(argc < 2){
		printf("FALLO EN EL NUMERO DE ARGUMENTOS. Escribe --> ./p4_e2 numeros.txt\n");
		return -1;
	}
	tr = tree_ini(int_destroy, int_copy, int_print, int_cmp);
	/*CdE*/
	if(tr==NULL){
		return -1;
	}

	fichero = fopen(argv[1], "r");
	/*CdE*/
	if(fichero==NULL){
		return -1;
	}


	entero= (int *)malloc(sizeof(int));

	if(entero==NULL){
		tree_free(tr);
		return -1;
	}

	while(fscanf(fichero, "%d", entero)>0) {
		tree_insert(tr, entero);
	}
	fclose(fichero);

	printf("Numero de nodos --> %d\n",  tree_numNodes(tr));
	printf("Profundidad --> %d\n",tree_depth(tr));

	printf("Orden previo --> ");
	tree_preOrder(stdout, tr);
	printf("\n");
	printf("Orden medio --> ");
	tree_inOrder(stdout, tr);
	printf("\n");
	printf("Orden posterior --> ");
	tree_postOrder(stdout, tr);
	printf("\n");


	printf("Introduzca un numero: ");

	scanf("%d", entero);

	printf("Numero introducido --> %d\n", *entero);

	if(tree_find(tr, entero)){
		printf("El dato %d se encuentra dentro del Arbol.\n", *entero);
		return 0;
	}
	else{
		printf("El dato %d NO se encuentra dentro del Arbol.\n", *entero);
		return -1;
	}
}
