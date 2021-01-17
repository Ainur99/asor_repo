#include <stdio.h>
#include <signal.h>

volatile int sigint_n = 0;
volatile int sigtstp_n = 0;

void handler_sigint_f(int signal) {
	sigint_n++;
}

void handler_sigtstp_f(int signal) {
	sigtstp_n++;
}

int main() {
	
	struct sigaction sigint_handler;
	struct sigaction sigtstp_handler;

	sigint_handler.sa_handler = handler_sigint_f;
	sigtstp_handler.sa_handler = handler_sigtstp_f;

	sigaction(SIGINT, &sigint_handler, NULL);
	sigaction(SIGTSTP, &sigtstp_handler, NULL);

	printf("%i\n", getpid());
	
	while(sigint_n + sigtstp_n != 10) {}
	
	printf("Se han recibido %i señales sigint\n", sigint_n);
	printf("Se han recibido %i señales sigtstp\n", sigtstp_n);
	
	return 0;
}
