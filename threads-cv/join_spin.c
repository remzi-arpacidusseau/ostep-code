#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "common.h"
#include "common_threads.h"

volatile int done = 0;

void *child(void *arg) {
    printf("child\n");
    sleep(5);
    done = 1;
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    Pthread_create(&p, NULL, child, NULL);
    while (done == 0) 
	; // spin
    printf("parent: end\n");
    return 0;
}
