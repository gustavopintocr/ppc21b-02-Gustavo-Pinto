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
 @param  array Arreglo de elementos que se va a factorizar.
 @param  position Int que determina la posicion del elemento.
*/
void factorize(array_int_t* array, int64_t position) {
  int64_t counter = 0;
  bool esFact = false;
  int64_t num = array->elements[position].number;
  if (num > 1 && num <= INT64_MAX &&
  !(array->elements[position].letter)) {
    int64_t base = 2;
    while (num > 1) {
      counter = 0;
      esFact = false;
      while (num % base == 0) {
        counter++;
        num /= base;
        esFact = true;
      }
      if (esFact) {
          add_subarray(&(array->elements[position]), base, counter);
      }
      if (base == 2) {
        base = 1;
      }
      base+=2;
    }
  }
}

/**
 @brief  Metodo encargado de hacer que los hilos factoricen todos los numeros
 sin que haya condiciones de carrera o que uno o más hilos accedan a la misma
 posición del array
 @param  data Data.
*/
void* routine_factorize(void* data) {
  private_data_t* private_data = (private_data_t*) data;
  shared_data_t* shared_data = private_data->shared_data;
  int64_t position = 0;
  while (true) {
    pthread_mutex_lock(&shared_data->next_position);
      position = shared_data->position;
      shared_data->position++;
      if ((size_t)shared_data->position > shared_data->array.counter) {
        pthread_mutex_unlock(&shared_data->next_position);
        break;
      }
    pthread_mutex_unlock(&shared_data->next_position);
    factorize(&shared_data->array, position);
  }
  return NULL;
  return NULL;
}
