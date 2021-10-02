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
#include "array_int.h"


typedef struct shared {
  int64_t count;
  int64_t position;
  array_int_t array;
  pthread_mutex_t can_access_next_position;
} shared_data_t;

typedef struct private {
  shared_data_t* shared_data;
} private_data_t;

void* routine_factorize(void* data);
int create_threads(shared_data_t* shared_data);

#endif
