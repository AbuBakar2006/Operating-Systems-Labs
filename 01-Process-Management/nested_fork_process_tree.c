#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
    pid_t pid1;

    pid1 = fork();

    if (pid1 < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid1 == 0){
	pid_t pid2;

        printf("I'm a Child Process\n");
        printf("PID: %d, PPID: %d\n", getpid(), getppid());

        pid2 = fork();

        if (pid2 < 0) {
            printf("Fork failed\n");
            return 1;
        }

        if (pid2 == 0) {
            printf("I'm a Grandchild Process\n");
            printf("PID: %d, PPID: %d\n", getpid(), getppid());

        } else {
            wait(NULL);
            printf("Child: Grandchild Done\n");
        }

    } else {
        printf("I'm a Parent Process\n");
        printf("PID: %d, PPID: %d\n", getpid(), getppid());
        wait(NULL);
        printf("Parent: Child Done\n");
    }

    return 0;
}
