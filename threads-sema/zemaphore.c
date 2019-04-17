#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"

typedef struct __Zem_t {
    int value;
    pthread_cond_t  cond;
    pthread_mutex_t lock;
} Zem_t;

void Zem_init(Zem_t *z, int value) {
    z->value = value;
    Cond_init(&z->cond);
    Mutex_init(&z->lock);
}

void Zem_wait(Zem_t *z) {
    Mutex_lock(&z->lock);
    while (z->value <= 0)
	Cond_wait(&z->cond, &z->lock);
    z->value--;
    Mutex_unlock(&z->lock);
}

void Zem_post(Zem_t *z) {
    Mutex_lock(&z->lock);
    z->value++;
    Cond_signal(&z->cond);
    Mutex_unlock(&z->lock);
}


Zem_t s;

void *child(void *arg) {
    sleep(4);
    printf("child\n");
    Zem_post(&s); // signal here: child is done
    return NULL;
}

int main(int argc, char *argv[]) {
    Zem_init(&s, 0); 
    printf("parent: begin\n");
    pthread_t c;
    Pthread_create(&c, NULL, child, NULL);
    Zem_wait(&s); // wait here for child
    printf("parent: end\n");
    return 0;
}
    
