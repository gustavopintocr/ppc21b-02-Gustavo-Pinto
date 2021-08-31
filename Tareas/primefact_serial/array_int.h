#ifndef ARRAY_INT_H
#define ARRAY_INT_H
#include <stddef.h>
#include <stdint.h>

typedef struct {
  size_t capacidad;
  size_t contador;
  int64_t* elementos;
} array_int_t;

void array_init(array_int_t* a);
void array_destroy(array_int_t* a);
int array_append(array_int_t*a , int64_t elm);
int array_increase_capacity(array_int_t* a);

#endif  // ARRAY_INT_H
