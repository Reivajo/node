#ifndef STRING_H
#define STRING_H

void destroy_string_function(void* e);

void * copy_string_function(const void* e);

int    print_string_function(FILE * f, const void* e);

int    cmp_string_function(const void* e1, const void* e2);

#endif
