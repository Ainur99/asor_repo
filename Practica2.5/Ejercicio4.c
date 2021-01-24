#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>

int main(int argc, char** argv) {

	struct addrinfo hints, *res;
	int sd, c;
	socklen_t addrlen = 64;
	char buf[16], addr[addrlen], host[NI_MAXHOST], serv[NI_MAXSERV];

	int tlen;
	char str[64];
	time_t tim;
   	struct tm *t;

	fd_set rfd;
	int max, s;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
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
	
	while(1) {	
	
		if ((sd = socket(res->ai_family, res->ai_socktype, 0)) == -1) {
			printf("Error en socket()\n");
			return 0;
		}
		bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

		if (sd > 0)
			max = sd + 1;
		else
			max = 0 + 1;

		FD_ZERO(&rfd);
		FD_SET(sd, &rfd);
		FD_SET(0, &rfd);		
		
		s = select(max, &rfd, NULL, NULL, NULL);

		if (FD_ISSET(sd, &rfd)) {
			c = recvfrom(sd, buf, 16, 0, (struct sockaddr *) &addr, &addrlen);
			buf[c] = '\0';
			if (getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST) != 0) {
				printf("Error en getnameinfo()\n");
				return 0;
			}
			printf("Mensaje recibido. Cliente: %s Puerto %s\n", host, serv);
		
			time(&tim);
   			t = localtime(&tim);

			switch (buf[0]) {
				case 't':
					tlen = strftime(str, 64, "%H:%M", t);
					sendto(sd, str, tlen, 0, (struct sockaddr *) &addr, addrlen);
					break;
				case 'd':
					tlen = strftime(str, 64, "%d de %B de %Y", t);
					sendto(sd, str, tlen, 0, (struct sockaddr *) &addr, addrlen);
					break;
				case 'q':
					freeaddrinfo(res);
					close(sd);
					printf("Servidor cerrado\n");
					return 0;
				default:
					printf("Comando no reconocido: %s\n", buf);
			}
		}
		
		if (FD_ISSET(0, &rfd)) {
			c = read(0, buf, 16);
			buf[c] = '\0';

			printf("Mensaje recibido. Entrada estandar\n");

			time(&tim);
   			t = localtime(&tim);

			switch (buf[0]) {
				case 't':
					tlen = strftime(str, 64, "%H:%M", t);
					printf("%s\n", str);
					break;
				case 'd':
					tlen = strftime(str, 64, "%d de %B de %Y", t);
					printf("%s\n", str);
					break;
				case 'q':
					freeaddrinfo(res);
					close(sd);
					printf("Servidor cerrado\n");
					return 0;
				default:
					printf("Comando no reconocido: %s\n", buf);
			}
		}

		close(sd);
	}
	freeaddrinfo(res);
	close(sd);
	return 0;
}
