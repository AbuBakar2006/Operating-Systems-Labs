#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open failed");
        exit(1);
    }

    dup2(fd, STDOUT_FILENO);

    printf("This text should go into the file, not the terminal.\n");

    close(fd);

    return 0;
}
