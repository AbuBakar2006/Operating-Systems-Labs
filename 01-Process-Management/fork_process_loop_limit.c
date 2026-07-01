#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    for (int i = 0; i < 5; i++) {
        pid = fork();

        if (pid < 0) {
            // Fork failed
            perror("Fork failed");
            return 1;
        } 
        else if (pid == 0) {
            // Child process
            printf("Child %d: PID = %d\n", i+1, getpid());
            sleep(10);
            return 0;  // Important: stop child from creating more children
        }
        // Parent continues loop to create next child
    }

    // Parent waits for all 5 children
    for (int i = 0; i < 5; i++) {
        wait(NULL);
    }

    printf("Parent: All children finished.\n");
    return 0;
}
