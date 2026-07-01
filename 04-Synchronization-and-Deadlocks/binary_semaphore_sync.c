// Synchronization using a binary semaphore to control access to a critical section.

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

sem_t binary_semaphore;

void *worker(void *arg) {
    int thread_id = *(int *)arg;

    printf("Thread %d is waiting to enter the critical section\n", thread_id);
    sem_wait(&binary_semaphore);

    printf("Thread %d entered the critical section\n", thread_id);
    sleep(1);
    printf("Thread %d leaving the critical section\n", thread_id);

    sem_post(&binary_semaphore);
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    if (sem_init(&binary_semaphore, 0, 1) != 0) {
        perror("sem_init");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, worker, &thread_ids[i]) != 0) {
            perror("pthread_create");
            sem_destroy(&binary_semaphore);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&binary_semaphore);
    printf("All threads have finished execution\n");
    return EXIT_SUCCESS;
}