#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int main() {
	sigset_t newset;

	sigemptyset(&newset);
	sigaddset(&newset, SIGINT);

	printf("Blocking SIGINT...\n");
	sigprocmask(SIG_BLOCK, &newset, NULL);

	sleep(5);

	printf("Unblocking SIGINT...\n");
	sigprocmask(SIG_UNBLOCK, &newset, NULL);

	return 0;
}
