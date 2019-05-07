#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "node.h"

struct _Node {
	char* name;
	int id;
};


Node *node_ini() {
  Node *n;

  n = (Node*)malloc(sizeof(Node));
  /*CdE*/
  if (n == NULL) {
    fprintf(stderr, "FALLO AL RESERVAR MEMORIA\n");
    return NULL;
  }

	n->name = NULL;
  return n;
}

void node_destroy(void *node){
	Node* n = (Node *) node;
	/*CdE*/
	if(n==NULL){
		fprintf (stderr, "FALLO AL DESTRUIR EL NODO\n");
	}
	if(n->name)
		free(n->name);
	free(n);
}

int node_getId(const Node *n){
	int g;

	/*CdE*/
	if(n->id==-1){
		fprintf (stderr, "FALLO AL COGER EL ID DEL NODO\n");
	}
	g=n->id;

	return g;
}

char* node_getName(const Node *n){
	char *tr;
	/*CdE*/
	if(n==NULL){
		fprintf (stderr, "FALLO AL COGER EL NAME DEL NODO\n");
	}
	tr =(char *)malloc(100*sizeof(char));
	/*CdE*/
	if(tr==NULL){
	  return NULL;
	}

	strcpy(tr,n->name);
	return tr;
}

Node * node_setId(Node *n, const int id){

	n->id=id;

	/*CdE*/
	if(n==NULL){
		fprintf (stderr, "FALLO AL HACER SET DEL ID DEL NODO\n");
	}

	return n;
}

Node * node_setName(Node *n, const char *name){
	/*CdE*/
	if(n==NULL){
		fprintf (stderr, "FALLO AL HACER SET DEL NAME DEL NODO\n");
	}

	if(n->name)
		free(n->name);
		n->name = malloc(strlen (name) + 1);
		/*CdE*/
		if (n->name == NULL){
			return NULL;
		}
		strcpy(n->name, name);

	return n;
}


int node_cmp(const void *node1, const void *node2){
	Node* n1 = (Node*) node1;
	Node* n2 = (Node*) node2;

	int dev;
	dev=strcmp(n1->name, n2->name);
	if(n1->id==n2->id && dev==0){
		return 0;
	}
	else if(n1->id>n2->id && dev>0){
		return 2;
	}
	else {
		return -2;
	}

}

void * node_copy(const void *node){

	Node* source = (Node*) node;
	Node *n;
	n=node_ini();

	/*CdE*/
	if(n==NULL){
		fprintf(stderr, "FALLO AL RESERVAR MEMORIA\n");
	}
	n->id=source->id;
	n->name = malloc(strlen (source->name) + 1);
	/*CdE*/
	if (n->name == NULL){
		return NULL;
	}
	strcpy(n->name, source->name);

	return n;
}

int node_print(FILE *pf, const void *node){
	Node* n = (Node*) node;

	int dev=0;
	/*CdE*/
	if(pf==NULL){
		fprintf (stderr, "FALLO AL IMPRIMIR EL NODO\n");
  	};
  	dev = fprintf(pf, "[%i, %s]", n->id, n->name);

	return dev;
}
