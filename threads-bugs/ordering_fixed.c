#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"

#define PR_STATE_INIT (0)

typedef struct {
    pthread_t Tid;
    int State;
} pr_thread_t;

pr_thread_t *PR_CreateThread(void *(*start_routine)(void *)) {
    pr_thread_t *p = malloc(sizeof(pr_thread_t));
    if (p == NULL) 
	return NULL;
    p->State = PR_STATE_INIT;
    Pthread_create(&p->Tid, NULL, start_routine, NULL); 
    // turn the sleep off to avoid the fault, sometimes...
    sleep(1);
    return p;
}

void PR_WaitThread(pr_thread_t *p) {
    Pthread_join(p->Tid, NULL); 
}

pr_thread_t *mThread;

pthread_mutex_t mtLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  mtCond = PTHREAD_COND_INITIALIZER;
int mtInit = 0;

void *mMain(void *arg) {
    printf("mMain: begin\n");

    // wait for thread structure to be initialized
    Pthread_mutex_lock(&mtLock);
    while (mtInit == 0)
	Pthread_cond_wait(&mtCond, &mtLock);
    Pthread_mutex_unlock(&mtLock);

    int mState = mThread->State;
    printf("mMain: state is %d\n", mState);
    return NULL;
}


int main(int argc, char *argv[]) {
    printf("ordering: begin\n");
    mThread = PR_CreateThread(mMain);

    // signal: thread has been created, and mThread initialized
    Pthread_mutex_lock(&mtLock);
    mtInit = 1;
    Pthread_cond_signal(&mtCond);
    Pthread_mutex_unlock(&mtLock);

    PR_WaitThread(mThread);
    printf("ordering: end\n");
    return 0;
}

