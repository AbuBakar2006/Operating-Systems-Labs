#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUFSIZE 100

int main() {
    int fd[2];
    pid_t pid;
    char *message = "This is a long string that will be split by the tee redirector.\n";
    char buffer[BUFSIZE];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        /* PARENT: The Writer */
        close(fd[0]); // Close unused read end

        write(fd[1], message, strlen(message) + 1);
        
        close(fd[1]); // Finished writing
        wait(NULL);   // Wait for child to finish
    } 
    else {
        /* CHILD: The Tee Redirector */
        close(fd[1]); // Close unused write end

        // 1. Open the file for writing (create if not exists, truncate if it does)
        int file_fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (file_fd == -1) {
            perror("open");
            exit(1);
        }

        // 2. Read from the pipe
        ssize_t n = read(fd[0], buffer, BUFSIZE);
        if (n > 0) {
            // 3. Write to the terminal (stdout)
            write(STDOUT_FILENO, buffer, n);

            // 4. Write to the file simultaneously
            write(file_fd, buffer, n);
        }

        close(fd[0]);
        close(file_fd);
        exit(0);
    }

    return 0;
}
