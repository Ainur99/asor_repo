#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

volatile int del = 1;

void handler_sigusr1_f(int signal) {
	del = 0;
}

int main(int argc, char ** argv) {
	
	struct sigaction sigusr1_handler;
	char *rm;
	rm = strdup("rm ");
	
	if (argc != 2) {
		printf("Numero de argumentos incorrecto. Uso: %s <segundos de espera>\n", argv[0]);
		return 0;
	}
	printf("%i\n", getpid());
	sigusr1_handler.sa_handler = handler_sigusr1_f;
	sigaction(SIGUSR1, &sigusr1_handler, NULL);
	
	sleep(atoi(argv[1]));

	if (del) {
		strcat(rm, argv[0]);
		system(rm);
	}
	
	return 0;
}
