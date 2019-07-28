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

typedef struct _rwlock_t {
    sem_t writelock;
    sem_t lock;
    int readers;
} rwlock_t;

void rwlock_init(rwlock_t *lock) {
    lock->readers = 0;
    Sem_init(&lock->lock, 1); 
    Sem_init(&lock->writelock, 1); 
}

void rwlock_acquire_readlock(rwlock_t *lock) {
    Sem_wait(&lock->lock);
    lock->readers++;
    if (lock->readers == 1)
	Sem_wait(&lock->writelock);
    Sem_post(&lock->lock);
}

void rwlock_release_readlock(rwlock_t *lock) {
    Sem_wait(&lock->lock);
    lock->readers--;
    if (lock->readers == 0)
	Sem_post(&lock->writelock);
    Sem_post(&lock->lock);
}

void rwlock_acquire_writelock(rwlock_t *lock) {
    Sem_wait(&lock->writelock);
}

void rwlock_release_writelock(rwlock_t *lock) {
    Sem_post(&lock->writelock);
}

int read_loops;
int write_loops;
int counter = 0;

rwlock_t mutex;

void *reader(void *arg) {
    int i;
    int local = 0;
    for (i = 0; i < read_loops; i++) {
	rwlock_acquire_readlock(&mutex);
	local = counter;
	rwlock_release_readlock(&mutex);
	printf("read %d\n", local);
    }
    printf("read done: %d\n", local);
    return NULL;
}

void *writer(void *arg) {
    int i;
    for (i = 0; i < write_loops; i++) {
	rwlock_acquire_writelock(&mutex);
	counter++;
	rwlock_release_writelock(&mutex);
    }
    printf("write done\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
	fprintf(stderr, "usage: rwlock readloops writeloops\n");
	exit(1);
    }
    read_loops = atoi(argv[1]);
    write_loops = atoi(argv[2]);
    
    rwlock_init(&mutex); 
    pthread_t c1, c2;
    Pthread_create(&c1, NULL, reader, NULL);
    Pthread_create(&c2, NULL, writer, NULL);
    Pthread_join(c1, NULL);
    Pthread_join(c2, NULL);
    printf("all done\n");
    return 0;
}
    

