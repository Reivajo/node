#ifndef INT_H
#define INT_H

void* int_ini();

void int_destroy (void* num);

void* int_copy (const void* num);

int int_print(FILE *file, const void* num);

int int_cmp (const void* num1, const void* num2);

void* int_setInfo (void *num, int v);

#endif
