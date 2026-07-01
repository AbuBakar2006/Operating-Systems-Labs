#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == 0) {
        printf("Child A: PID = %d, Parent PID = %d\n", getpid(), getppid());
        exit(0);
    }

    pid2 = fork();

    if (pid2 == 0) {
        printf("Child B executing command \"ls -l\"\n");
        execlp("ls", "ls", "-l", NULL);

        perror("execlp failed");
        exit(1);
    }
    wait(NULL);
    wait(NULL);

    printf("Parent: All children have exited\n");

    return 0;
}
