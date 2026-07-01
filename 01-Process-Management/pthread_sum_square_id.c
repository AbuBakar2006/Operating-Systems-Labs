#include <stdio.h>
#include <pthread.h>

// Structure to pass data to threads
struct data {
    int num1;
    int num2;
};

// Thread 1: Calculate sum
void* calculate_sum(void* arg) {
    struct data* d = (struct data*)arg;
    int sum = d->num1 + d->num2;

    printf("Thread 1\n");
    printf("Sum of %d and %d = %d\n", d->num1, d->num2, sum);

    pthread_exit(NULL);
}

// Thread 2: Calculate square
void* calculate_square(void* arg) {
    struct data* d = (struct data*)arg;
    int square = d->num1 * d->num1;

    printf("Thread 2\n");
    printf("Square of %d = %d\n", d->num1, square);

    pthread_exit(NULL);
}

// Thread 3: Print message with thread ID
void* print_message(void* arg) {
    printf("Thread 3\n");
    printf("Hello from thread ID: %lu\n", pthread_self());

    pthread_exit(NULL);
}

int main() {

    pthread_t t1, t2, t3;

    struct data d;
    d.num1 = 5;
    d.num2 = 10;

    // Create threads
    pthread_create(&t1, NULL, calculate_sum, &d);
    pthread_create(&t2, NULL, calculate_square, &d);
    pthread_create(&t3, NULL, print_message, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}
