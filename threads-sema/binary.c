#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"

#ifdef linux
#include <semaphore.h>
#elif __APPLE__
#include "zemaphore.h"
#endif

sem_t mutex;
volatile int counter = 0;

void *child(void *arg) {
    int i;
    for (i = 0; i < 10000000; i++) {
	Sem_wait(&mutex);
	counter++;
	Sem_post(&mutex);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    Sem_init(&mutex, 1); 
    pthread_t c1, c2;
    Pthread_create(&c1, NULL, child, NULL);
    Pthread_create(&c2, NULL, child, NULL);
    Pthread_join(c1, NULL);
    Pthread_join(c2, NULL);
    printf("result: %d (should be 20000000)\n", counter);
    return 0;
}
    
