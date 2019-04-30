#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "common.h"
#include "common_threads.h"

pthread_cond_t  c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *child(void *arg) {
    printf("child: begin\n");
    Mutex_lock(&m);
    printf("child: signal\n");
    Cond_signal(&c);
    Mutex_unlock(&m);
    return NULL;
}
int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    Pthread_create(&p, NULL, child, NULL);
    sleep(2);
    printf("parent: wait to be signalled...\n");
    Mutex_lock(&m);
    Cond_wait(&c, &m); 
    Mutex_unlock(&m);
    printf("parent: end\n");
    return 0;
}

