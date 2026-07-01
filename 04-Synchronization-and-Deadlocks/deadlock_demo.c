#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 5
#define M 5

pthread_mutex_t locks[M];

time_t last_activity;

void* worker(void* arg)
{
    int id = *(int*)arg;

    int first = id % M;
    int second = (id + 1) % M;

    while(1)
    {
        pthread_mutex_lock(&locks[first]);

        sleep(1);

        pthread_mutex_lock(&locks[second]);

        printf("Process %d updated resources\n", id);

        last_activity = time(NULL);

        pthread_mutex_unlock(&locks[second]);
        pthread_mutex_unlock(&locks[first]);
    }

    return NULL;
}

void* watchdog(void* arg)
{
    while(1)
    {
        sleep(1);

        if(time(NULL) - last_activity > 5)
        {
            printf("\n[WATCHDOG] No activity for 5 seconds\n");
            printf("[ALERT] Deadlock Detected\n");

            exit(0);
        }
    }

    return NULL;
}

int main()
{
    pthread_t threads[N];
    pthread_t watch;

    int ids[N];

    last_activity = time(NULL);

    for(int i = 0; i < M; i++)
    {
        pthread_mutex_init(&locks[i], NULL);
    }

    for(int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }

    pthread_create(&watch, NULL, watchdog, NULL);

    for(int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_join(watch, NULL);

    return 0;
}
