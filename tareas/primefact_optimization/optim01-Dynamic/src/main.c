/*
 * Copyright 2021 Gustavo Pinto 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <errno.h>
#include <pthread.h>
#include "array_int.h"
#include "pthread_routine.h"
#include "factorizer.h"

/**
 @brief Metodo Main. Lee un archivo, factoriza su contenido y lo imprime
 @return Un código de error:
   0 si lo logró.
   1 si falló o presentó problemas.
*/
int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  int64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  if (argc == 2) {
    if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
    } else {
      fprintf(stderr, "error: invalid thread count\n");
      return EXIT_FAILURE;
    }
  }
  array_int_t array;
  start_array(&array);
  int64_t number;
  char* error_char = malloc(100);
  while ( fgets(error_char, 100, stdin ) ) {
    if (sscanf(error_char, "%"SCNd64, &number) && !errno) {
      add_element(&array, number, false);
       errno = 0;
    } else {
       add_element(&array, number, true);
       errno = 0;
    }
  }
  free(error_char);
  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
  if (shared_data) {
    errno = 0;
    start_array(&shared_data->array);
    shared_data->array = array;
    shared_data->position = 0;
    shared_data->count = thread_count;

    error = pthread_mutex_init(&shared_data->can_access_next_position, NULL);
    if (!errno) {
      error = create_threads(shared_data);

      print(&shared_data->array);
      pthread_mutex_destroy(&shared_data->can_access_next_position);
      destroy_array(&shared_data->array);
    } else {
      fprintf(stderr, "Error: could not init mutex\n");
      error = EXIT_FAILURE;
    }
    free(shared_data);
  } else {
    fprintf(stderr, "error: could not allocate shared memory\n");
    error = 11;
  }
  return error;
}
