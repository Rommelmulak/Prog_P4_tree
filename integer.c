#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "types.h"


void* int_ini(){
	int *i=NULL;

	i = (int*)malloc(sizeof(int));

	/*CdE*/
	if(i==NULL){
		return NULL;
	}

    return i;
}

void int_destroy (void* e){

	/*CdE*/
    if (e==NULL){
      free((int*)e);
    }
}

void* int_copy (const void* e){
  int *i;
  if (e == NULL){
		return NULL;
	}

  i = (int*)malloc(sizeof(int));

	/*CdE*/
  if (i == NULL){
   return NULL;
}

  *(i) = *((int*)e);
	  return i;
}

int int_print(FILE *file, const void* e){
	/*CdE*/
	if (file==NULL || e==NULL){
  	return -1;
  }

	return fprintf(file, "[%d]", *((int*)e));
}

int int_cmp (const void* e1, const void* e2){
	/*CdE*/
  if(e1==NULL || e2==NULL){
  	return -1;
  }
  return *((int*)e1) - *((int*)e2);
}

void* int_setInfo (void *e, int v){
	/*CdE*/
  if (e==NULL){
      return NULL;
  }
  *((int*)e) = v;
  return e;
}
