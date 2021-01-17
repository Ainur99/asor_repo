#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	
	char* slp;
	
	sigset_t set, set1, pen;
	
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTSTP);
	
	sigprocmask(SIG_BLOCK, &set, NULL);
	slp = getenv("SLEEP_SECS");
	
	printf("%i\n", getpid());
	if (slp == NULL)
		sleep(60);
	else
		sleep(atoi(slp));
	
	sigemptyset(&pen);
	sigpending(&pen);
	if (sigismember(&pen, SIGINT)) {
		printf("Recibido SIGINT\n");
	}
	if (sigismember(&pen, SIGTSTP)) {
		printf("Recibido SIGTSTP\n");
		sigemptyset(&set1);
		sigaddset(&set1, SIGTSTP);
		sigprocmask(SIG_UNBLOCK, &set1, NULL);
	}
	
	printf("end program\n");
	return 0;
}
