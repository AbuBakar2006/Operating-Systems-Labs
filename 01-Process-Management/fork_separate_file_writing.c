#include <stdio.h>
#include <unistd.h>     
#include <fcntl.h>     
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    pid_t pid;

    pid = fork();   // create child process

    if (pid < 0) {
  
        perror("Fork failed");
        return 1;
    }

 
    else if (pid == 0) {
        int fd;
        char *msg = "This is written by CHILD process.\n";

        fd = open("child.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

        if (fd < 0) {
            perror("File open failed (child)");
            return 1;
        }

        write(fd, msg, strlen(msg));
        close(fd);

        printf("Child: File 'child.txt' created and written.\n");
    }


    else {
        int fd;
        char *msg = "This is written by PARENT process.\n";

        fd = open("parent.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

        if (fd < 0) {
            perror("File open failed (parent)");
            return 1;
        }

        write(fd, msg, strlen(msg));
        close(fd);

        printf("Parent: File 'parent.txt' created and written.\n");
    }

    return 0;
}
