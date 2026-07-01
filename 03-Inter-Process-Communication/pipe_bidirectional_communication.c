#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUFSIZE 10

int main(void) {
    char bufin[BUFSIZE] = "empty";
    char p_msg[] = "hello";
    char c_msg[] = "world";
    int bytesin;
    pid_t childpid;
    
    int p1[2]; // Parent to Child
    int p2[2]; // Child to Parent

    if (pipe(p1) == -1 || pipe(p2) == -1) {
        perror("Failed to create pipes");
        return 1;
    }

    childpid = fork();

    if (childpid == -1) {
        perror("Failed to fork");
        return 1;
    }

    if (childpid > 0) { 
        /* PARENT */
        close(p1[0]); // Close unused read end of pipe 1
        close(p2[1]); // Close unused write end of pipe 2

        // 1. Write "hello" to child
        write(p1[1], p_msg, strlen(p_msg) + 1);

        // 2. Read "world" from child
        bytesin = read(p2[0], bufin, BUFSIZE);
        fprintf(stderr, "Parent [%ld]: received {%s}\n", (long)getpid(), bufin);

        close(p1[1]);
        close(p2[0]);
    } 
    else { 
        /* CHILD */
        close(p1[1]); // Close unused write end of pipe 1
        close(p2[0]); // Close unused read end of pipe 2

        // 1. Read "hello" from parent
        bytesin = read(p1[0], bufin, BUFSIZE);
        fprintf(stderr, "Child  [%ld]: received {%s}\n", (long)getpid(), bufin);

        // 2. Write "world" back to parent
        write(p2[1], c_msg, strlen(c_msg) + 1);

        close(p1[0]);
        close(p2[1]);
    }

    return 0;
}
