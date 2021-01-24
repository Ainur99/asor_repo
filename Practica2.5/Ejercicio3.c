#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char** argv) {

	struct addrinfo hints, *res;
	int sd, c;
	socklen_t addrlen = 64;
	char buf[32], addr[addrlen], host[NI_MAXHOST], serv[NI_MAXSERV];

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = 0;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = 0;
	hints.ai_addrlen = 0;
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;
	
	if (argc != 4) {
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
	if (sendto(sd, argv[3], strlen(argv[3]), 0, res->ai_addr, res->ai_addrlen) == -1) {
		printf("Error en sendto()\n");
		return 0;
	}
	freeaddrinfo(res);
	if ((strcmp(argv[3], "t") == 0) || (strcmp(argv[3], "d") == 0)) {
		c = recvfrom(sd, buf, 32, 0, NULL, NULL);
		buf[c] = '\0';
		printf("%s\n", buf);
	}
   return 0;
}
