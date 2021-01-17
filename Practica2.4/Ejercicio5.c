#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	
	int fd1, fd2;
	int n, s, max;
	fd_set rfd;
	char buf[256];
	
	if (argc != 3) {
		printf("Numero de argumentos incorrecto. Uso: %s <nombre tuberia 1> <nombre tuberia 2>\n", argv[0]);
		return 0;
	}
	while (1) {
		fd1 = open(argv[1], O_RDONLY | O_NONBLOCK);
		fd2 = open(argv[2], O_RDONLY | O_NONBLOCK);
		
		if (fd1 > fd2)
			max = fd1 + 1;
		else
			max = fd2 + 1;
		
		FD_ZERO(&rfd);
		FD_SET(fd1, &rfd);
		FD_SET(fd2, &rfd);
		
		s = select(max, &rfd, NULL, NULL, NULL);
		
		if (FD_ISSET(fd1, &rfd)) {
			n = read(fd1, buf, 256);
			buf[n] = '\0';
			printf("Leido desde tuberia 1: %s\n", buf);
		}
		if (FD_ISSET(fd2, &rfd)) {
			n = read(fd2, buf, 256);
			buf[n] = '\0';
			printf("Leido desde tuberia 2: %s\n", buf);
		}

		close(fd1);
		close(fd2);
	}
	
	return 0;
}
