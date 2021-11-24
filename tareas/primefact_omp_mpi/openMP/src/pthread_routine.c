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
int create_threads(array_int_t* array, int64_t thread_count) {
  int error = EXIT_SUCCESS;
  int capacity = array->counter;
  #pragma omp parallel for num_threads(thread_count) \
  schedule(dynamic) shared(array, capacity)
    for (int index = 0; index < capacity; index++) {
      factorize(array, index);
    }
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
int start_threads(array_int_t* arrayTemp, int64_t thread_count) {
  int error = EXIT_SUCCESS;
  error = create_threads(arrayTemp, thread_count);
  return error;
  return error;
}

