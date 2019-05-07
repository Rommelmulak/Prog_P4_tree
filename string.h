#ifndef STRING_H
#define STRING_H

void destroy_string_function(void* n);

void *copy_string_function(const void* n);

int print_string_function(FILE * fichero, const void* n);

int cmp_string_function(const void* n1, const void* n2);

#endif
