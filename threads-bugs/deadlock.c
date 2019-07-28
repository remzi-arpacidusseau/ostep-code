#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"

pthread_mutex_t L1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t L2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *arg) {
    printf("t1: begin\n");
    printf("t1: try to acquire L1...\n");
    Pthread_mutex_lock(&L1);
    printf("t1: L1 acquired\n");
    printf("t1: try to acquire L2...\n");
    Pthread_mutex_lock(&L2);
    printf("t1: L2 acquired\n");
    Pthread_mutex_unlock(&L1);
    Pthread_mutex_unlock(&L2);
    return NULL;
}

void *thread2(void *arg) {
    printf("                           t2: begin\n");
    printf("                           t2: try to acquire L2...\n");
    Pthread_mutex_lock(&L2);
    printf("                           t2: L2 acquired\n");
    printf("                           t2: try to acquire L1...\n");
    Pthread_mutex_lock(&L1);
    printf("                           t2: L1 acquired\n");
    Pthread_mutex_unlock(&L1);
    Pthread_mutex_unlock(&L2);

    return NULL;
}

int main(int argc, char *argv[]) {                    
    if (argc != 1) {
	fprintf(stderr, "usage: main\n");
	exit(1);
    }
    pthread_t p1, p2;
    printf("main: begin\n");
    Pthread_create(&p1, NULL, thread1, NULL); 
    Pthread_create(&p2, NULL, thread2, NULL);
    // join waits for the threads to finish
    Pthread_join(p1, NULL); 
    Pthread_join(p2, NULL); 
    printf("main: end\n");
    return 0;
}

