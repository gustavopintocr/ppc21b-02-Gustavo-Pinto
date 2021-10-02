/*
 * Copyright 2021 Gustavo Pinto 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <unistd.h>
#include "factorizer.h"
#include "array_int.h"
#include "pthread_routine.h"


/**
 @brief  Método encargado de factorizar el arreglo, recorriendo todos los elementos y creando un subarreglo
 con la factorizacion correspondiente.
 @param  array Arreglo de elementos que se va a imprimir.
*/
void factorize(array_int_t* vector, int64_t position) {
  int64_t num = 0;
  num = vector->elements[position].number;
  if (num > 1 && num <= INT64_MAX &&
  !(vector->elements[position].letter)) {
    for (int64_t base = 2; num > 1; base++) {
      int64_t counter = 0;
      while (num%base == 0) {
        counter++;
        num /= base;
        if (num%base != 0) {
          if (counter > 1) {
            add_subarray(&(vector->elements[position]), base,
            counter);
          } else if (num >= 1) {
            add_subarray(&(vector->elements[position]), base, 1);
          }
        }
      }
    }
  }
}

/**
 @brief  Método encargado de eliminar subarreglos.
 @param  array Subrreglo de elementos que se va a eliminar.
*/
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
