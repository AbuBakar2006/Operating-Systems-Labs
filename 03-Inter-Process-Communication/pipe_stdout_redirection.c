#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t pid;

    // 1. Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 2. fork() a child
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* CHILD PROCESS (ls) */
        // The child needs to WRITE to the pipe, so it redirects stdout (1)
        // 3. Redirect stdout (1) to the write-end of the pipe
        dup2(fd[1], STDOUT_FILENO);

        // Close both ends of the original pipe descriptors (no longer needed after dup2)
        close(fd[0]);
        close(fd[1]);

        // Exec the ls command
        execlp("ls", "ls", NULL);
        
        // If execlp fails
        perror("execlp ls");
        exit(EXIT_FAILURE);
    } else {
        /* PARENT PROCESS (wc -l) */
        // The parent needs to READ from the pipe, so it redirects stdin (0)
        // 4. Redirect stdin (0) to the read-end of the pipe
        dup2(fd[0], STDIN_FILENO);

        // Close both ends
        close(fd[0]);
        close(fd[1]);

        // Exec the wc -l command
        execlp("wc", "wc", "-l", NULL);

        // If execlp fails
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    return 0;
}
