#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char** argv) {

	struct addrinfo hints, *res;
	int sd, c;
	int buflen = 64;	
	char buf[buflen];

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_addrlen = 0;
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;
	
	if (argc != 3) {
		printf("Numero de argumentos invalido\n");
		return 0;
	}
	
	if (getaddrinfo(argv[1], argv[2], &hints, &res) != 0) {
		printf("Error en getaddrinfo(), compruebe que la direccion esta bien especificada\n");
		return 0;
	}
	if ((sd = socket(res->ai_family, res->ai_socktype, 0)) == -1) {
		printf("Error en socket()\n");
		return 0;
	}
	freeaddrinfo(res);

	connect(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

	c = read(0, buf, buflen);
	buf[c] = '\0';

	while (strcmp(buf, "Q\n") != 0) {
		
		send(sd, buf, strlen(buf), 0);
		
		c = recv(sd, buf, buflen, 0);
		buf[c] = '\0';
		printf("%s", buf);
		c = read(0, buf, buflen);
		buf[c] = '\0';
	}
	close(sd);
	return 0;
}
