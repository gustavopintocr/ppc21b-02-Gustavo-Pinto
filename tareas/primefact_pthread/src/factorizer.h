/*
 * Copyright 2021 Gustavo Pinto 
 */


#ifndef FACTORIZER_H
#define FACTORIZER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <unistd.h>
#include "array_int.h"

void factorize(array_int_t* vector, int64_t position);
void* routine_factorize(void* data);

#endif
