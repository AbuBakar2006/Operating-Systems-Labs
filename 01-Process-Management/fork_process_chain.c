#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    pid_t pid;

    for (int i = 1; i <= n; i++) {
        printf("Process P%d, PID: %d, Parent PID: %d\n", i, getpid(), getppid());

        if (i == n)
            break;

        pid = fork();

        if (pid < 0)
            exit(1);
        else if (pid == 0)
            continue;
        else
            break;
    }
    return 0;
}
