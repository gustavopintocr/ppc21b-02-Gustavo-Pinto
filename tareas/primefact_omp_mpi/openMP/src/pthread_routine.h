/*
 * Copyright 2021 Gustavo Pinto 
 */

#ifndef PTHREAD_ROUTINE_H
#define PTHREAD_ROUTINE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <unistd.h>
#include <omp.h>
#include "array_int.h"


typedef struct shared {
  int64_t count;
  int64_t position;
  pthread_mutex_t next_position;
  array_int_t array;
} shared_data_t;

typedef struct private {
  shared_data_t* shared_data;
} private_data_t;

int create_threads(array_int_t* array,int64_t thread_count);
int start_threads(array_int_t* array, int64_t thread_count);

#endif
