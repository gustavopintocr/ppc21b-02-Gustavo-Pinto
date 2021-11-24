/*
 * Copyright 2021 Gustavo Pinto 
 */

#ifndef ARRAY_INT_H
#define ARRAY_INT_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct sub_array {
  size_t capacity;
  size_t counter;
  int64_t number;
  int64_t* bases;
  int64_t* exponents;
  bool letter;
}sub_array_t;

typedef struct {
  size_t capacity;
  size_t counter;
  sub_array_t* elements;
} array_int_t;

int add_element(array_int_t* array, int64_t number, bool isLetter);
int add_subarray(sub_array_t* a, int64_t base, int64_t expo);
void destroy_array(array_int_t* array);
void destroy_subarray(array_int_t* array);
int increase_capacity(array_int_t* array);
int increase_subarray(sub_array_t* array);
void start_array(array_int_t* array);
void start_subarray(sub_array_t* array);
void print(array_int_t* array);

#endif  // ARRAY_INT_Hmentos[i].numero);
