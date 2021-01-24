#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char** argv) {
	
	struct addrinfo hints, *res;
	struct addrinfo *save;

	char host[NI_MAXHOST];

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = 0;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = 0;
	hints.ai_protocol = 0;
	hints.ai_addrlen = 0;
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;
	
	if (argc != 2) {
		printf("Numero de argumentos invalido\n");
		return 0;
	}

	if (getaddrinfo(argv[1], NULL, &hints, &res) != 0) {
		printf("Error en getaddrinfo(), compruebe que la direccion esta bien especificada\n");
		return 0;
	}
	save = res;
	while (res != NULL) {
		if (getnameinfo(res->ai_addr, res->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) != 0) {
			printf("Error en getnameinfo()\n");
			return 0;
		}
		printf("%s %i  %i\n", host, res->ai_family, res->ai_socktype);
		res = res->ai_next;
	}
	freeaddrinfo(save);
	return 0;
}
