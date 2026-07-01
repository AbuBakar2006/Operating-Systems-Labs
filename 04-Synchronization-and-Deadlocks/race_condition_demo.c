#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 20
#define M 2
#define ITERATIONS 1000

int slots[M] = {0};

void* worker(void* arg)
{
    for(int i = 0; i < ITERATIONS; i++)
    {
        int slot = i % M;
        slots[slot]++;
    }

    return NULL;
}

int main()
{
    pthread_t threads[N];

    for(int i = 0; i < N; i++)
    {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    for(int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    int actual = 0;

    for(int i = 0; i < M; i++)
    {
        actual += slots[i];
    }

    int expected = N * ITERATIONS;

    printf("\n[ASSERT] Expected Updates : %d\n", expected);
    printf("[ASSERT] Actual Updates   : %d\n", actual);

    if(expected == actual)
    {
        printf("[PASS] No Race Condition\n");
    }
    else
    {
        printf("[FAIL] Race Condition Detected\n");
    }

    return 0;
}
