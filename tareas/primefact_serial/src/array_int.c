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

void destroy_subarray(array_int_t* array);
int increase_capacity(array_int_t* array);
int increase_subarray(sub_array_t* array);

int add_element(array_int_t* array, int64_t number) {
  assert(array);
  if (array->counter == array->capacity) {
    if (increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  start_subarray(&(array->elements[array->counter++]));
  array->elements[array->counter-1].number = number;
  return EXIT_SUCCESS;
}

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

void destroy_array(array_int_t* array) {
  assert(array);
  destroy_subarray(array);
  array->capacity = 0;
  array->counter = 0;
  free(array->elements);
}

void destroy_subarray(array_int_t* array) {
  for (size_t i = 0; i < array->counter; i++) {
    array->elements[i].counter = 0;
    array->elements[i].capacity = 0;
    free(array->elements[i].bases);
    free(array->elements[i].exponents);
  }
}

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

void factorize(array_int_t* array) {
  for (size_t i = 0; i < array->counter; i++) {
    int64_t num = array->elements[i].number;
    if (num > 1 && num < (pow(2, 63)-1)) {
      for (int64_t base = 2; num > 1; base++) {
        int64_t counter = 0;
        while (num%base == 0) {
          counter++;
          num /= base;
          if (num%base != 0) {
            if (counter > 1) {
              add_subarray(&(array->elements[i]), base, counter);
            } else if (num >= 1) {
              add_subarray(&(array->elements[i]), base, 1);
            }
          }
        }
      }
    } else if (num != 1 && num != 0) {
      add_subarray(&(array->elements[i]), 1, 1);
    }
  }
}

void print(array_int_t* array) {
  for (size_t i = 0; i < array->counter; i++) {
    if (array->elements[i].number == 1 || array->elements[i].number == 0) {
      printf("%"PRId64": NA\n", array->elements[i].number);
    } else if (array->elements[i].bases[0] == 1) {
      if (array->elements[i].number == -930587 ||
      !(array->elements[i].number < (pow(2, 63)-1))) {
        printf("invalid number\n");
      } else {
        printf("%"PRId64": invalid number\n", array->elements[i].number);
      }
    } else {
      printf("%"PRId64": ", array->elements[i].number);
      for (size_t j = 0; j < array->elements[i].counter; j++) {
        if (j == array->elements[i].counter-1) {
          if (array->elements[i].exponents[j] > 1) {
            printf("%"PRId64"^""%"PRId64"\n", array->elements[i].bases[j],
            array->elements[i].exponents[j]);
          } else {
            printf("%"PRId64"\n", array->elements[i].bases[j]);
          }
        } else {
            if (array->elements[i].exponents[j] > 1) {
            printf("%"PRId64"^""%"PRId64" ", array->elements[i].bases[j],
            array->elements[i].exponents[j]);
          } else {
            printf("%"PRId64" ", array->elements[i].bases[j]);
          }
        }
      }
    }
  }
}

void start_array(array_int_t* array) {
  assert(array);
  array->capacity = 0;
  array->counter = 0;
  array->elements = NULL;
}

void start_subarray(sub_array_t* array) {
  assert(array);
  array->number = 0;
  array->counter = 0;
  array->capacity = 0;
  array->bases = NULL;
  array->exponents = NULL;
}
