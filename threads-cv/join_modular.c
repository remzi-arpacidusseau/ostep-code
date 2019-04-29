#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "common.h"
#include "common_threads.h"

//
// Simple sync "object"
//

typedef struct {
    pthread_cond_t c;
    pthread_mutex_t m;
    int done;
} synchronizer_t;

synchronizer_t s;

void sync_init(synchronizer_t *s) {
    s->done = 0;
    Mutex_init(&s->m);
    Cond_init(&s->c);
}

void sync_signal(synchronizer_t *s) {
    Mutex_lock(&s->m);
    s->done = 1;
    Cond_signal(&s->c);
    Mutex_unlock(&s->m);
}

void sync_wait(synchronizer_t *s) {
    Mutex_lock(&s->m);
    while (s->done == 0) 
	Cond_wait(&s->c, &s->m); 
    s->done = 0; // reset for next use
    Mutex_unlock(&s->m);
}


//
// Main threads
//

void *child(void *arg) {
    printf("child\n");
    sleep(1);
    sync_signal(&s);
    return NULL;
}
int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    sync_init(&s);
    Pthread_create(&p, NULL, child, NULL);
    sync_wait(&s);
    printf("parent: end\n");
    return 0;
}

