#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv) {
	
	if (argc != 3) {
		printf("Numero de argumentos incorrecto. Argumentos: comando de shell \"Argumentos de comando\"\n");
		return 0;
	}
	
	execvp(argv[1], &argv[1]);
	
	printf("El comando termino de ejecutarse\n");
	return 0;
}
