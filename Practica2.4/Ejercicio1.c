#include <unistd.h>
#include <stdio.h>

void hijo(int pipe, char* command, char* args) {
	dup2(pipe, 0);
	execlp(command, command, args, NULL);
}

void padre(int pipe, char* command, char* args) {
	dup2(pipe, 1);
	execlp(command, command, args, NULL);
}

int main(int argc, char** argv) {
	
	int pipe_fd[2];
	
	if (argc != 5) {
		printf("Numero de argumentos incorrecto. Uso: %s comando1 arg1 comando2 arg2\n", argv[0]);
		return 0;
	}
	
	pipe(pipe_fd);
	
	switch (fork()) {
		case -1:
			perror("fork");
			break;
		case 0:
			close(pipe_fd[1]);
			hijo(pipe_fd[0], argv[3], argv[4]);
			break;
		default:
			close(pipe_fd[0]);
			padre(pipe_fd[1], argv[1], argv[2]);
	}
	
	return 0;
}
