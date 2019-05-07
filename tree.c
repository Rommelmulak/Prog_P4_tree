#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tree.h"
#include "node.h"
#include "types.h"

#define INFO(pn) ((pn)->info)
#define LEFT(pn) ((pn)->left)
#define RIGHT(pn) ((pn)->right)
#define ROOT(t) ((t)->root)

typedef struct _NodeBT {
void* info;
struct _NodeBT* left;
struct _NodeBT* right;

} NodeBT;


struct _Tree {
 NodeBT *root;
 destroy_element_function_type destroy_element_function;
 copy_element_function_type copy_element_function;
 print_element_function_type print_element_function;
 cmp_element_function_type cmp_element_function;
};


void tree_freeRec(NodeBT* pn, destroy_element_function_type desfun);
Status bst_recInsert(NodeBT **ppn, const void *e,copy_element_function_type fcpy, cmp_element_function_type fcmp);
Status tree_preOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun);
Status tree_inOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun);
Status tree_postOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun);
int tree_depthRec(NodeBT* pn);
int tree_numNodesRec(NodeBT* pn);
NodeBT * NodeAB_ini();
void bt_node_free(NodeBT *pn, destroy_element_function_type f1);
int printNodeAB(FILE* pf, const NodeBT *pn, print_element_function_type fprint);
NodeBT * search_nodeAB(const Tree *t, const void* e);
NodeBT *search_nodeAB_rec(NodeBT *pn,const void *e,cmp_element_function_type fcmp);



Tree* tree_ini(destroy_element_function_type f1,copy_element_function_type f2,print_element_function_type f3, cmp_element_function_type f4) {
	Tree *tr;
		tr = (Tree *)malloc(sizeof(Tree));
    /*CdE*/
		if (tr == NULL) {
		return NULL;
		}

	ROOT(tr) = NULL;
	tr->destroy_element_function=f1;
	tr->copy_element_function=f2;
	tr->print_element_function=f3;
	tr->cmp_element_function=f4;

return tr;
}

Bool tree_isEmpty( const Tree *pa){

	if (pa == NULL) {
		return TRUE;
	}
	if (ROOT(pa) == NULL) {
		return TRUE;
	}

return FALSE;
}

void tree_free(Tree *pa){

  /*CdE*/
	if (pa==NULL){
		return;
	}
	tree_freeRec(pa->root, pa->destroy_element_function);
	free(pa);
	pa = NULL;
	return;
}

void tree_freeRec(NodeBT* pn, destroy_element_function_type desfun){

  /*CdE*/
  if (pn==NULL){
		return;
	}
	tree_freeRec(LEFT(pn), desfun);
	tree_freeRec(RIGHT(pn), desfun);
	bt_node_free(pn, desfun);
	return;
}


Status tree_insert(Tree *pa, const void *po){

  /*CdE*/
	if (pa == NULL || po == NULL) {
		return ERROR;
	}
return bst_recInsert(&ROOT(pa), po, pa->copy_element_function, pa->cmp_element_function );
}


Status bst_recInsert(NodeBT **ppn, const void *e,copy_element_function_type fcpy, cmp_element_function_type fcmp) {

	int compare;
	void *inf=NULL;
		if (*ppn == NULL) {
			*ppn = NodeAB_ini();

		if (*ppn == NULL) return ERROR;

		inf= fcpy(e);
		INFO(*ppn) = inf;

	return OK;
	}
		compare = fcmp(e,INFO((*ppn)));
		if(compare==0){
			return ERROR;
		}
		if (compare < 0) {
			return bst_recInsert(&(LEFT(*ppn)), e,fcpy,fcmp);
		} else if (compare > 0) {
			return bst_recInsert(&(RIGHT(*ppn)), e,fcpy,fcmp);
		}
	return ERROR;

}

Status tree_preOrder(FILE *f, const Tree *pa){

  /*CdE*/
	if (f==NULL || pa==NULL){
		return ERROR;
	}

	return tree_preOrderRec(f, pa->root, pa->print_element_function);
}

Status tree_preOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun){

  /*CdE*/
  if (f==NULL || pn==NULL){
		return ERROR;
	}
	printNodeAB(f, pn, pfun);
	tree_preOrderRec(f, LEFT(pn), pfun);
	tree_preOrderRec(f, RIGHT(pn), pfun);
	return OK;
}

Status tree_inOrder(FILE *f, const Tree *pa){

  /*CdE*/
  if (f==NULL || pa==NULL){
		return ERROR;
	}

	return tree_inOrderRec(f, pa->root, pa->print_element_function);
}

Status tree_inOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun){

  /*CdE*/
  if (f==NULL || pn==NULL){
		return ERROR;
	}
	tree_inOrderRec(f, LEFT(pn), pfun);
	printNodeAB(f, pn, pfun);
	tree_inOrderRec(f, RIGHT(pn), pfun);
	return OK;
}

Status tree_postOrder(FILE *f, const Tree *pa){

  /*CdE*/
	if (f==NULL || pa==NULL){
		return ERROR;
	}

	return tree_postOrderRec(f, pa->root, pa->print_element_function);
}

Status tree_postOrderRec(FILE* f, NodeBT* pn, print_element_function_type pfun){

  /*CdE*/
  if (f==NULL || pn==NULL){
		return ERROR;
	}
	tree_postOrderRec(f, LEFT(pn), pfun);
	tree_postOrderRec(f, RIGHT(pn), pfun);
	printNodeAB(f, pn, pfun);

	return OK;
}

int tree_depth(const Tree *pa){

  /*CdE*/
	if (tree_isEmpty(pa) == TRUE || pa==NULL){
		return -1;
	}

	return tree_depthRec(ROOT(pa));
}

int tree_depthRec(NodeBT* pn){
	int right=0, left=0;

  /*CdE*/
	if (pn==NULL){
		return -1;
	}
	if (RIGHT(pn) == NULL && LEFT(pn) == NULL){
		return 0;
	}
	right = 1 + tree_depthRec(RIGHT(pn));
	left = 1 + tree_depthRec(LEFT(pn));
	if (right > left){
		return right;
	}
	return left;
}

int tree_numNodes(const Tree *pa){

  /*CdE*/
	if (pa==NULL || tree_isEmpty(pa) == TRUE){
		return 0;
	}
	return tree_numNodesRec(ROOT(pa));
}

int tree_numNodesRec(NodeBT* pn){

  /*CdE*/
	if (pn==NULL){
		return 0;
	}
	return 1 + tree_numNodesRec(LEFT(pn)) + tree_numNodesRec (RIGHT(pn));
}

Bool tree_find(Tree* pa, const void* pe){

  /*CdE*/
	if(pa==NULL || pe==NULL){
    return FALSE;
  }

	if(search_nodeAB(pa,pe) != NULL){
		return TRUE;
	}
  else{
		return FALSE;
	}
}

NodeBT * NodeAB_ini(){
	NodeBT* nAux;

	nAux = malloc(sizeof(NodeBT));
  /*CdE*/
  if (nAux==NULL){
		return NULL;
	}
	LEFT(nAux) = RIGHT(nAux) = NULL;
	INFO(nAux) = NULL;
	return nAux;
}

void bt_node_free(NodeBT *pn, destroy_element_function_type f1){

	if (pn != NULL) {
		f1(INFO(pn));
		free(pn);
	}
	return;
}

int printNodeAB(FILE* pf, const NodeBT *pn, print_element_function_type fprint){
  /*CdE*/
  if (pf==NULL || pn==NULL){
		return 0;
	}
	return fprint(pf, pn->info);
}

NodeBT * search_nodeAB(const Tree *t, const void* e){

  /*CdE*/
	if(t==NULL || e==NULL){
		return NULL;
	}

	return search_nodeAB_rec(ROOT(t),e,t->cmp_element_function);
}

NodeBT *search_nodeAB_rec(NodeBT *pn,const void *e,cmp_element_function_type fcmp){

	int compare=0;

  /*CdE*/
	if(pn==NULL || e==NULL){
		return NULL;
	}

	compare= fcmp(e,INFO(pn));

	if(compare==0){
		return pn;
	}
	else if(compare>0){
		return search_nodeAB_rec(RIGHT(pn),e,fcmp);
	}else{
		return search_nodeAB_rec(LEFT(pn),e,fcmp);
	}
}
