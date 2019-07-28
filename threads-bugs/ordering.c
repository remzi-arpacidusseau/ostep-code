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

void *mMain(void *arg) {
    printf("mMain: begin\n");
    int mState = mThread->State;
    printf("mMain: state is %d\n", mState);
    return NULL;
}


int main(int argc, char *argv[]) {
    printf("ordering: begin\n");
    mThread = PR_CreateThread(mMain);
    PR_WaitThread(mThread);
    printf("ordering: end\n");
    return 0;
}

