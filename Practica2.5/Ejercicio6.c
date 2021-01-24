#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

int main(int argc, char** argv) {

	struct addrinfo hints, *res;
	int clisd, sd, c;
	socklen_t addrlen = 64;	
	char buf[16], addr[addrlen], host[NI_MAXHOST], serv[NI_MAXSERV];
	
	int i;	

	int tlen;
	char str[64];
	time_t tim;
   	struct tm *t;

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
	bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);

	listen(sd, 16);

	while (1) {
		if ((clisd = accept(sd, (struct sockaddr *) &addr, &addrlen)) == -1) {
			printf("Error en accept()\n");
			return 0;
		}
		
		if (getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST) != 0) {
			printf("Error en getnameinfo()\n");
			return 0;
		}
		printf("Conexion desde %s %i\n", addr, serv);
		while (c = recv(sd, buf, 16, 0)) {
			buf[c] = '\0';
			send(clisd, buf, c, 0);
		}
		printf("Conexion terminada\n");
		close(clisd);
	}
	return 0;
}
