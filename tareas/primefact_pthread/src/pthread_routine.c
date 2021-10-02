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
#include "array_int.h"


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
  return error;
}


void* routine_factorize(void* data) {
  private_data_t* private_data = (private_data_t*) data;
  shared_data_t* shared_data = private_data->shared_data;
  int64_t my_position = 0;
  array_int_t arrayTemp = shared_data->array;
  while (true) {
    pthread_mutex_lock(&shared_data->can_access_next_position);
      my_position = shared_data->position;
      shared_data->position++;
      if ((size_t)shared_data->position > arrayTemp.counter) {
        pthread_mutex_unlock(&shared_data->can_access_next_position);
        break;
      }
    pthread_mutex_unlock(&shared_data->can_access_next_position);

    factorize(&arrayTemp, my_position);
  }
  return NULL;
}

void* routine_factorize(void* data);