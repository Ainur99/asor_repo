#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv) {
	
	if (argc != 2) {
		printf("Numero de argumentos incorrecto. Uso:%s  \"comando de shell\"\n",argv[0]);
		return 0;
	}

	system(argv[1]);
	
	printf("El comando termino de ejecutarse\n");
	return 0;
}
