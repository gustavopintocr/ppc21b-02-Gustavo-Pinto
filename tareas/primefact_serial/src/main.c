/*
 * Copyright 2021 Gustavo Pinto 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <errno.h>
#include "array_int.h"

/**
 @brief Lee un archivo, factoriza su contenido y lo imprime
*/
int main(void) {
  array_int_t array;
  start_array(&array);
  int64_t number;
  char* error_char = malloc(100);
  while (fgets(error_char, 100, stdin) ){
    if (sscanf(error_char, "%"SCNd64, &number) && !errno) {
      add_element(&array, number, false);
       errno = 0;
    } else {
       add_element(&array, number, true);
       errno = 0;
    }
  }
  free(error_char);
  factorize(&array);
  print(&array);
  destroy_array(&array);
  return EXIT_SUCCESS ;
}
