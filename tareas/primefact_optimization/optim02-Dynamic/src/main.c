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
  error = start_threads(create_array(), thread_count);
  return error;
}
