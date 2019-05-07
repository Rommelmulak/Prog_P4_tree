#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "tree.h"
#include "node.h"
#include "types.h"

#define MAX_LINE 350
#define MAX 300

Node* read_node_from_file(FILE* fichero_entrada){
	Node* node = NULL;
	int id=-1;
	char name[MAX], buff[MAX_LINE];

	if (fgets(buff, MAX_LINE, fichero_entrada) != NULL){
		if (sscanf(buff, "%d %s", &id, name) == 2){
			/* create node */
			node = node_ini();
			if (node_setId(node, id) == NULL){
				node_destroy(node);
				return NULL;
			}
			if (node_setName(node, name) == NULL){
				node_destroy(node);
				return NULL;
			}
		}
	}

	return node;
}

int compare(const void* a, const void* b) {
    Node **e1, **e2;
    e1 = (Node **) a;
    e2 = (Node **) b;
    return node_cmp(*e1, *e2);
}

int getNumberLines(FILE* pf) {
    char line[MAX_LINE];
    int n = 0;
    while (fgets(line, MAX_LINE, pf) != NULL) {
        n++;
    }
    return n;
}

void loadDataFromFile(FILE* pf, Node*** ndata) {
    Node** naux = *ndata;
    Node* n;

	while(!feof(pf)){
		n = read_node_from_file(pf);
		if (n != NULL){
			*naux = node_copy(n);
			naux++;
			node_destroy(n);
		}
	}
}

void balance(Node** data, Tree *t, int first, int last) {
    int middle = (first + last) / 2;
    Node* n;

    if (first <= last) {
        n = *(&(data[0]) + middle);
		if (tree_insert(t, n) == ERROR){
			fprintf(stdout, "Node ");
			node_print(stdout, n);
			fprintf(stdout, " not inserted!\n");
		}

        balance(data, t, first, middle - 1);
        balance(data, t, middle + 1, last);
    }
}

Tree* loadBalancedTreeFromData(Node** data, int n) {
	Tree* t;

	t = tree_ini(node_destroy, node_copy, node_print, node_cmp);

    balance(data, t, 0, n - 1);

    return t;
}

Tree* loadTreeFromData(Node** data, int n) {
	Tree* t;
	Node* node;
	int i;

	t = tree_ini(node_destroy, node_copy, node_print, node_cmp);

	for (i=0; i<n; i++){
		node = data[i];
		if (tree_insert(t, node) == ERROR){
			fprintf(stdout, "Node ");
			node_print(stdout, node);
			fprintf(stdout, " not inserted!\n");
		}
	}

    return t;
}

int main(int argc, char const *argv[]){
	FILE *fichero_entrada, *fichero_salida;
	Tree* tree=NULL;
	Node **n_source=NULL, *n_aux=NULL;
	int i ,lineas;
  time_t time;
  double tiempo_segs;

	/*CdE*/
	if(argc < 3){
		printf("FALLO EN EL NUMERO DE ARGUMENTOS. Escribe --> ./p4_e3 <fichero.dat> N\n");
		return -1;
	}

	fichero_entrada = fopen(argv[1], "r");
	/*CdE*/
	if (fichero_entrada==NULL){
		return 1;
	}

	fichero_salida = stdout;

    lineas = getNumberLines(fichero_entrada);
    fclose(fichero_entrada);
    fprintf(fichero_salida, "%d líneas leídas\n", lineas);
    n_source = (Node**) malloc(lineas * sizeof (Node*));
    fichero_entrada = fopen(argv[1], "r");
    loadDataFromFile(fichero_entrada, &n_source);
    fclose(fichero_entrada);

	if (strcmp("N", argv[2]) == 0)  {
		time = clock();
		tree = loadTreeFromData(n_source, lineas);
		time = clock() - time;
		tiempo_segs = ((float) time) / CLOCKS_PER_SEC;
	} else if (strcmp("B", argv[2]) == 0)  {
		qsort(n_source, lineas, sizeof(Node*), &compare);
		fprintf(fichero_salida, "Datos ordenados\n");
		time = clock();
		tree = loadBalancedTreeFromData(n_source, lineas);
		time = clock() - time;
		tiempo_segs = ((float) time) / CLOCKS_PER_SEC;
	}

    for (i=0; i<lineas; i++){
    	node_destroy(n_source[i]);
    }
    free(n_source);

    fprintf(fichero_salida, "\nTiempo de creacion del Arbol: %.5ld ticks (%f segundos)\n", (long) time, tiempo_segs);
		fprintf(fichero_salida, "Numero de nodos: %d\n", tree_numNodes(tree));
		fprintf(fichero_salida, "Profundidad: %d\n", tree_depth(tree));

	while(n_aux == NULL){
		fprintf(stdout, "Introduce un nodo para buscar en el Arbol (siguiendo el mismo formato que en el fichero de entrada):\n");
		n_aux = read_node_from_file(stdin);
	}
	time = clock();
	if (tree_find(tree, n_aux) == TRUE){
		fprintf(stdout, "Elemento encontrado!\n");
	}
	else{
		fprintf(stdout, "Elemento NO encontrado!\n");
	}
	time = clock() - time;
	tiempo_segs = ((float) time) / CLOCKS_PER_SEC;
	node_destroy(n_aux);
    fprintf(fichero_salida, "\nTiempo de busqueda en el Arbol: %ld ticks (%f segundos)\n", (long) time, tiempo_segs);

	tree_free(tree);

	return 0;
}
