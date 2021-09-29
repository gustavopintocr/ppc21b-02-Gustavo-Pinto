/*
 * Copyright 2021 Gustavo Pinto 
 */

#include "array_int.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

/**
 @brief  Método encargado de añadir un elemento a un arreglo de elementos.
 @param  array Arreglo de elementos tipo int.
 @param  number Numero int de 64bits Elemento que se va a añadir.
 @return Un código de error:
   0 si lo logró.
   1 si falló.
*/
int add_element(array_int_t* array, int64_t number, bool isLetter) {
  assert(array);
  if (array->counter == array->capacity) {
    if (increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  if (!isLetter) {
    start_subarray(&(array->elements[array->counter++]));
    array->elements[array->counter-1].number = number;
    array->elements[array->counter-1].letter = false;
    return EXIT_SUCCESS;
  }else{
    start_subarray(&(array->elements[array->counter++]));
    array->elements[array->counter-1].number = 0;
    array->elements[array->counter-1].letter = true;
    return EXIT_SUCCESS;
  }
}

/**
 @brief  Método encargado de añadir a un subarreglo la factorización prima.
 @param  array Subarreglo de elementos.
 @param  base Base del numero que se va a añadir.
 @param  exponent Exponente del numero que se va a añadir.
 @return Un código de error:
   0 si lo logró.
   1 si falló.
*/
int add_subarray(sub_array_t* array, int64_t base, int64_t exponent) {
  assert(array);
  if (array->counter == array->capacity) {
    if (increase_subarray(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  array->bases[array->counter++] = base;
  array->exponents[array->counter-1] = exponent;
  return EXIT_SUCCESS;
}

/**
 @brief  Método encargado de eliminar arreglos.
 @param  array Arreglo de elementos que se va a eliminar.
*/
void destroy_array(array_int_t* array) {
  assert(array);
  destroy_subarray(array);
  array->capacity = 0;
  array->counter = 0;
  free(array->elements);
}

/**
 @brief  Método encargado de eliminar subarreglos.
 @param  array Subrreglo de elementos que se va a eliminar.
*/
void destroy_subarray(array_int_t* array) {
  for (size_t i = 0; i < array->counter; i++) {
    array->elements[i].counter = 0;
    array->elements[i].capacity = 0;
    free(array->elements[i].bases);
    free(array->elements[i].exponents);
  }
}

/**
 @brief  Método encargado de incrementar el tamaño del arreglo en 1.
 @param  array Arreglo de elementos tipo int que se va a incrementar.
 @return Un código de error:
   0 si lo logró.
   1 si falló.
*/
int increase_capacity(array_int_t* array) {
  size_t new_capacity = array->capacity + 1;
  sub_array_t* new_elements = (sub_array_t*)
    realloc(array->elements, new_capacity * sizeof(sub_array_t));
  if (new_elements) {
    array->capacity = new_capacity;
    array->elements = new_elements;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

/**
 @brief  Método encargado de incrementar el tamaño de un subarreglo en 1.
 @param  array Subarreglo de elementos tipo int que se va a incrementar.
 @return Un código de error:
   0 si lo logró.
   1 si falló.
*/
int increase_subarray(sub_array_t* array) {
  size_t new_capacity = array->capacity + 1;
  int64_t* new_bases = (int64_t*)
    realloc(array->bases, new_capacity * sizeof(int64_t));
  int64_t* new_exponents = (int64_t*)
    realloc(array->exponents, new_capacity * sizeof(int64_t));
  if (new_bases && new_exponents) {
    array->capacity = new_capacity;
    array->bases = new_bases;
    array->exponents = new_exponents;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

/**
 @brief  Método encargado de factorizar el arreglo, recorriendo todos los elementos y creando un subarreglo
 con la factorizacion correspondiente.
 @param  array Arreglo de elementos que se va a imprimir.
*/
void factorize(array_int_t* vector) {
  for (size_t i = 0; i < vector->counter; i++) {
    int64_t num = vector->elements[i].number;
    if (num > 1 && num <= INT64_MAX && !(vector->elements[i].letter)) {
      for (int64_t base = 2; num > 1; base++) {
        int64_t contador = 0;
        while (num%base == 0) {
          contador++;
          num /= base;
          if (num%base != 0) {
            if (contador > 1) {
              add_subarray(&(vector->elements[i]), base, contador);
            } else if (num >= 1) {
              add_subarray(&(vector->elements[i]), base, 1);
            }
          }
        }
      }
    } else if (num != 1 && num != 0 && !(vector->elements[i].letter)) {
      add_subarray(&(vector->elements[i]), 1, 1);
    }
  }
}

/**
 @brief  Método encargado de imprimir el arreglo, con 4 condiciones importantes:
 que sea una letra -> Invalid number
 que el numero sea 0 0 1 -> NA
 que el numero sea menor que 0 -> Invalid number
 y el caso en el que haya que imprimir la factorizacion -> 9: 3^2
 @param  array Arreglo de elementos que se va a imprimir.
*/
void print(array_int_t* array) {
for (size_t i = 0; i < array->counter; i++) {
    if (array->elements[i].letter) {
        printf("invalid number\n");
    } else if (array->elements[i].number == 1
      || array->elements[i].number == 0) {
      printf("%"PRId64": NA\n", array->elements[i].number);
    } else if (array->elements[i].number < 0) {
        printf("%"PRId64": invalid number\n", array->elements[i].number);
    } else {
      printf("%"PRId64": ", array->elements[i].number);
      for (size_t j = 0; j < array->elements[i].counter; j++) {
        if (j == array->elements[i].counter-1) {
          if (array->elements[i].exponents[j] > 1) {
            printf("%"PRId64"^""%"PRId64"\n", array->elements[i].bases[j]
            , array->elements[i].exponents[j]);
          } else {
            printf("%"PRId64"\n", array->elements[i].bases[j]);
          }
        } else {
            if (array->elements[i].exponents[j] > 1) {
            printf("%"PRId64"^""%"PRId64" ", array->elements[i].bases[j]
            , array->elements[i].exponents[j]);
          } else {
            printf("%"PRId64" ", array->elements[i].bases[j]);
          }
        }
      }
    }
  }
}

/**
 @brief  Método encargado de iniciar un arreglo.
 @param  array Arreglo de elementos que se va a iniciar.
*/
void start_array(array_int_t* array) {
  assert(array);
  array->capacity = 0;
  array->counter = 0;
  array->elements = NULL;
}

/**
 @brief  Método encargado de iniciar un subarreglo.
 @param  array Subrreglo de elementos que se va a iniciar.
*/
void start_subarray(sub_array_t* array) {
  assert(array);
  array->number = 0;
  array->counter = 0;
  array->capacity = 0;
  array->bases = NULL;
  array->exponents = NULL;
}

void destroy_subarray(array_int_t* array);
int increase_capacity(array_int_t* array);
int increase_subarray(sub_array_t* array);
