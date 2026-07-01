#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Original Process \nPid: %d\tPPid: %d\n",getpid(),getppid());
	pid_t pid = fork();

	if(pid!=0){
		printf("Parent Process\nPid: %d\tPPid: %d\n",getpid(),getppid());
}
else{
sleep(5);
printf("Child Process\nPid:%d\t PPid:%d\n",getpid(),getppid());
}

printf("Pid %d Terminates\n",getpid());
return 0;
} 
