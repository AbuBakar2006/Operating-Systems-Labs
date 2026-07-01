#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[]) {
    int src, dest;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    if (argc != 3) {
        printf("Usage: %s source destination\n", argv[0]);
        exit(1);
    }

    src = open(argv[1], O_RDONLY);
    if (src < 0) {
        perror("Source open failed");
        exit(1);
    }

    dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (dest < 0) {
        perror("Destination open failed");
        close(src);
        exit(1);
    }

    while ((bytesRead = read(src, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(dest, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Write error");
            close(src);
            close(dest);
            exit(1);
        }
    }

    close(src);
    close(dest);

    if (unlink(argv[1]) == 0) {
        printf("Source file deleted\n");
    } else {
        perror("unlink failed");
    }

    return 0;
}
