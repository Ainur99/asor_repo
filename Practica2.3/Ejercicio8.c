#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char ** argv) {
	
	if (argc != 3) {
		printf("Numero de argumentos incorrecto. Argumentos: comando de shell \"Argumentos de comando\"\n");
		return 0;
	}
	
	if (fork() == 0) {
		setsid();
		chdir("/tmp");
		/*Codigo del daemon*/
		
		dup2(open("/dev/null", O_RDONLY | O_CREAT, 0777), 0);
		dup2(open("/tmp/daemon.out", O_WRONLY | O_CREAT, 0777), 1);
		dup2(open("/tmp/daemon.err", O_WRONLY | O_CREAT, 0777), 2);		
		
		execvp(argv[1], &argv[1]);
	}
	
	return 0;
}
