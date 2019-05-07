#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tree.h"
#include "errno.h"
#include "node.h"
#include "types.h"


int main(int argc, char* argv[1]) {
	FILE *fichero;
	Tree *tr;
	Node *nodo;
	char name[99];
	int id;

	if(argc < 2) {
		printf("FALLO DE ARGUMENTOS, Introduce --> Un fichero de nodos.\n");
		return 1;
	}

	/*Abrimos el fichero*/
	fichero = fopen(argv[1], "r");

	tr = tree_ini(node_destroy, node_copy, node_print, node_cmp);

	/*CdE*/
	if (tr==NULL){
		fclose(fichero);
		return 1;
	}

	while (fscanf(fichero, "%d %s", &id, name) == 2){
		nodo = node_ini();
		if (node_setId(nodo, id) == NULL){
			node_destroy(nodo);
			return 1;
		}
		if (node_setName(nodo, name) == NULL){
			node_destroy(nodo);
			return 1;
		}
		tree_insert(tr, nodo);
		node_destroy(nodo);
	}

	fclose(fichero);

	printf("Numero de nodos: %d\n", tree_numNodes(tr));
	printf("Profundidad: %d\n", tree_depth(tr));


	printf("Orden previo: \n");
	tree_preOrder(stdout, tr);
	printf("Orden medio: \n");
	tree_inOrder(stdout, tr);
	printf("Orden posterior: \n");
	tree_postOrder(stdout, tr);

	return 0;
}
