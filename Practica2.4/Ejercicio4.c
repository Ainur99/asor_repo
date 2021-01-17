#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv) {
	
	int fd;
	
	if (argc != 3) {
		printf("Numero de argumentos incorrecto. Uso: %s <nombre tuberia> <texto>\n", argv[0]);
		return 0;
	}
	
	fd = open(argv[1], O_WRONLY);
	write(fd, argv[2], strlen(argv[2]));
	close(fd);
	
	return 0;
}
