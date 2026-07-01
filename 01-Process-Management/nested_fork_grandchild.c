#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t child1, child2;
    child1 = fork();

    if (child1 != 0) {
        printf("Parent Process\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());

    }
    else {
        child2 = fork();

        if (child2 == 0) {
            printf("Second Child Process\n");
            printf("PID: %d\n", getpid());
            printf("PPID: %d\n", getppid());
        }
        else {
            printf("First Child Process\n");
            printf("PID: %d\n", getpid());
            printf("PPID: %d\n", getppid());
        }
    }
    return 0;
}
