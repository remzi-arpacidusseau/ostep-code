#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

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
    
