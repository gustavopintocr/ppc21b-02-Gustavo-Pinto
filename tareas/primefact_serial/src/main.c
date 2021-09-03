/*
 * Copyright 2021 Gustavo Pinto 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include "array_int.h"

/**
 @brief Lee un archivo, factoriza su contenido y lo imprime
*/
int main(void) {
  array_int_t array;
  start_array(&array);
  int64_t number;
  int64_t error_flag = -930587;
  char *error_char = malloc(100);
  int error_handling = 0;
  while (scanf("%" SCNd64, &number) == 1 || (error_handling = scanf("%s",
  error_char)) == 1) {
    if (error_handling == 1) {
      add_element(&array, error_flag);
      error_handling = 0;
    } else {
      add_element(&array, number);
    }
  }
  free(error_char);
  factorize(&array);
  print(&array);
  destroy_array(&array);
}
