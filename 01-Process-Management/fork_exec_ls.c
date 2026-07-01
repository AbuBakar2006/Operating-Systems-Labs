#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
	pid_t childpid = fork();
	if (childpid == 0) {
		execl("/bin/ls", "ls", "-l", NULL);
	}
	wait(NULL);
	return 0;
}
