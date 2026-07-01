#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;
    char input[100];

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {
        close(fd[0]);

        printf("Enter a string: ");
        fflush(stdout);

        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        write(fd[1], input, strlen(input) + 1);
        close(fd[1]);

        wait(NULL);
    }
    else {
        close(fd[1]);

        char buffer[100] = {0};

        int n = read(fd[0], buffer, sizeof(buffer));
        if (n <= 0) {
            perror("read failed");
            exit(1);
        }

        for (int i = 0; buffer[i]; i++) {
            buffer[i] = toupper(buffer[i]);
        }

        printf("Uppercase: %s\n", buffer);

        close(fd[0]);
    }

    return 0;
}
