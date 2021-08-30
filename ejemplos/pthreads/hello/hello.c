//Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC -BY 4.0

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>

void* greet(void* data);

// procedure main
int main(void) {
    // create_thread(greet)
    pthread_t thread;
    int error = pthread_create(&thread,/*attr*/ NULL,greet, /*arg*/NULL);
    if(error == EXIT_SUCCESS){
        // print('Hello from main thread')
        printf("Hello from main thread\n");
    }else{
        fprintf(stderr, "Error: could no create secondary thread\n");
    }
    return error;
    // end procedure
}

// procedure greet
void* greet(void* data){
    (void)data;
    printf("Hello from secondary thread\n");
    return NULL;
    // end procedure
}