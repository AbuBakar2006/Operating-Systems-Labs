#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#define N 10
#define M 5
#define RUN_TIME 30

pthread_mutex_t locks[M];

int counts[N] = {0};

time_t start_time;

void* worker(void* arg)
{
    int id = *(int*)arg;

    while(time(NULL) - start_time < RUN_TIME)
    {
        int slot = id % M;

        pthread_mutex_lock(&locks[slot]);

        counts[id]++;

        pthread_mutex_unlock(&locks[slot]);
    }

    return NULL;
}

double calculate_mean()
{
    int sum = 0;

    for(int i = 0; i < N; i++)
    {
        sum += counts[i];
    }

    return (double)sum / N;
}

double calculate_stddev(double mean)
{
    double variance = 0;

    for(int i = 0; i < N; i++)
    {
        variance += (counts[i] - mean) * (counts[i] - mean);
    }

    variance /= N;

    return sqrt(variance);
}

int main()
{
    pthread_t threads[N];
    int ids[N];

    start_time = time(NULL);

    for(int i = 0; i < M; i++)
    {
        pthread_mutex_init(&locks[i], NULL);
    }

    for(int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }

    for(int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("\nUpdate Distribution:\n");

    for(int i = 0; i < N; i++)
    {
        printf("PID %d : %d updates\n", i, counts[i]);
    }

    double mean = calculate_mean();
    double stddev = calculate_stddev(mean);

    printf("\nMean Updates        : %.2f\n", mean);
    printf("Standard Deviation  : %.2f\n", stddev);

    if(stddev < 1000)
    {
        printf("[PASS] Fair Distribution Observed\n");
    }
    else
    {
        printf("[FAIL] Starvation Detected\n");
    }

    return 0;
}
