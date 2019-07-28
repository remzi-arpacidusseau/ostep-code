#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"

typedef struct {
    int pid;
} proc_t;

typedef struct {
    proc_t *proc_info;
} thread_info_t; 

proc_t p;
thread_info_t th;
thread_info_t *thd;

void *thread1(void *arg) {
    printf("t1: before check\n");
    if (thd->proc_info) {
	printf("t1: after check\n");
	sleep(2);
	printf("t1: use!\n");
	printf("%d\n", thd->proc_info->pid);
    }
    return NULL;
}

void *thread2(void *arg) {
    printf("                 t2: begin\n");
    sleep(1); // change to 5 to make the code "work"...
    printf("                 t2: set to NULL\n");
    thd->proc_info = NULL;
    return NULL;
}

int main(int argc, char *argv[]) {                    
    if (argc != 1) {
	fprintf(stderr, "usage: main\n");
	exit(1);
    }
    thread_info_t t;
    p.pid = 100;
    t.proc_info = &p;
    thd = &t;

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

