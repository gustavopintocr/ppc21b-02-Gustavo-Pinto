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
  array_int_t array;
} shared_data_t;

typedef struct private {
  shared_data_t* shared_data;
  int64_t number;
  int64_t first;
  int64_t last;
} private_data_t;

int create_threads(shared_data_t* shared_data);
int64_t start_block(int64_t thread_number, shared_data_t* shared_data);
int start_threads(array_int_t arrayTemp, int64_t count);

#endif
