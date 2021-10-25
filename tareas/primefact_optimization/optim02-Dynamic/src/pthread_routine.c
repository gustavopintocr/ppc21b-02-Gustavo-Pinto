/*
 * Copyright 2021 Gustavo Pinto 
 */

#include "pthread_routine.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include "array_int.h"
#include "factorizer.h"


/**
 @brief  Método encargado de crear los hilos de concurrencia.
 @param  shared_data Pointer a typedef struct.
 @return Un código de error:
   0 si lo logró.
   1 si falló.
*/
int create_threads(shared_data_t* shared_data) {
  int error = EXIT_SUCCESS;

  pthread_t* threads = (pthread_t*)
    malloc(shared_data->count * sizeof(pthread_t));

  private_data_t* private_data = (private_data_t*)
    calloc(shared_data->count, sizeof(private_data_t));

  if (threads && private_data) {
    for (int64_t thread_number = 0; thread_number < shared_data->count
        ; thread_number++) {
      private_data[thread_number].shared_data = shared_data;

      error = pthread_create(&threads[thread_number], NULL,
      routine_factorize, &private_data[thread_number]);
      if (error == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "Error: could no create secondary thread\n");
        error = 23;
        break;
      }
    }
    for (int64_t thread_number = 0; thread_number < shared_data->count
        ; ++thread_number) {
      pthread_join(threads[thread_number], /*value_ptr*/ NULL);
    }
    free(private_data);
    free(threads);
  }
  print(&shared_data->array);
  return error;
}

/**
 * @brief Inicia los valores del struct shared para luego llamar al metodo
 * create_threads, imprimir los resultados de las factotizaciones y eliminar
 * o liberar toda la memoria utilizada en punteros y demas.
 * 
 * @param arrayTemp 
 * @param thread_count 
 * @return int 
 */
int start_threads(array_int_t arrayTemp, int64_t count) {
  int error = EXIT_SUCCESS;
  shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
  if (shared_data) {
    errno = 0;
    start_array(&shared_data->array);
    shared_data->array = arrayTemp;
    shared_data->position = 0;
    shared_data->count = count;
    error = pthread_mutex_init(&shared_data->next_position, NULL);
    if (!errno) {
      error = create_threads(shared_data);
      pthread_mutex_destroy(&shared_data->next_position);
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

