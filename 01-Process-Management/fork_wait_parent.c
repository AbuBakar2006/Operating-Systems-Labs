#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
int pid,status;
pid = fork();
if(pid == -1) {
printf("fork failed\n");
exit(1);
}
if (pid == 0) {
printf("Child here!\n");
}
else {
// Parent
wait(&status);
printf("Well done kid!\n");
}
}
