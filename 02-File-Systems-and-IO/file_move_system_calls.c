#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
int fd1, fd2;
char buffer[1024];
int n;
fd1 = open("old.txt", O_RDONLY);
if (fd1 < 0) {
perror("Open old file");
return 1;
}
fd2 = open("new.txt", O_WRONLY | O_CREAT, 0644);
while ((n = read(fd1, buffer, sizeof(buffer))) > 0) {
write(fd2, buffer, n);
}
close(fd1);
close(fd2);
unlink("old.txt");
// Delete original file
printf("Move using system calls completed.\n");
return 0;
}
