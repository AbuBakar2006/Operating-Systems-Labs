#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void* signal_listener(void* arg)
{
    sigset_t *set = (sigset_t*)arg;
    int sig;

    while (1)
    {
        sigwait(set, &sig);

        if (sig == SIGINT)
        {
            printf("\nSIGINT received by Signal Listener Thread!\n");
        }
    }

    return NULL;
}

void* worker_thread(void* arg)
{
    int count = 0;

    while (1)
    {
        printf("Worker Thread Running: %d\n", count++);
        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t listener, worker;
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    pthread_sigmask(SIG_BLOCK, &set, NULL);
    pthread_create(&listener, NULL, signal_listener, (void*)&set);

    pthread_create(&worker, NULL, worker_thread, NULL);

    pthread_join(listener, NULL);
    pthread_join(worker, NULL);

    return 0;
}
