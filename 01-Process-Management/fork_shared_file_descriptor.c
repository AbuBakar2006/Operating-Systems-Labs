#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd;
    pid_t pid;


    fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        perror("Open failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        char *child_msg = "BBBBB";
        write(fd, child_msg, strlen(child_msg));
        printf("Child wrote BBBBB\n");
    }

    else {
        char *parent_msg = "AAAAA";
        write(fd, parent_msg, strlen(parent_msg));
        printf("Parent wrote AAAAA\n");

        wait(NULL); 
    }

    close(fd);

    return 0;
}
