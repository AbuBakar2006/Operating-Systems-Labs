#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n;
    printf("Enter the number of children: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of children must be positive.\n");
        return 1;
    }

    printf("Parent PID: %d\n", getpid());

    pid_t pid;

    for (int i = 1; i <= n; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } 
        else if (pid == 0) {
            printf("Child C%d, PID: %d, Parent PID: %d\n", i, getpid(), getppid());
            exit(0);
        }
    }

    for (int i = 0; i < n; i++)
        wait(NULL);

    return 0;
}
