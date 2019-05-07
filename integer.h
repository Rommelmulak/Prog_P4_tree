#ifndef INTEGER_H_
#define INTEGER_H_

void* int_ini();

void int_destroy(void *e);

void *int_copy(const void *e);

int int_print(FILE *f, const void *e);

int int_cmp(const void *e1, const void *e2);

void* int_setInfo (void *e, int v);

#endif /* INTEGER_H_ */
