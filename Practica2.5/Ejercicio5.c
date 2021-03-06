#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char** argv) {

	pid_t children[10];

	struct addrinfo hints, *res;
	int sd, c;
	
	int i;	

	int tlen;
	char str[64];
	time_t tim;
   	struct tm *t;

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
	if ((sd = socket(res->ai_family, res->ai_socktype, 0)) == -1) {
		printf("Error en socket()\n");
		return 0;
	}
	bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);

	for (i=0;i<10;i++) {
		
		if (fork()==0) {
			children[i] = getpid();	
			socklen_t addrlen = 64;	
			char buf[16], addr[addrlen], host[NI_MAXHOST], serv[NI_MAXSERV];
			while (1) {
				c = recvfrom(sd, buf, 16, 0, (struct sockaddr *) &addr, &addrlen);
				buf[c] = '\0';
				if (getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST) != 0) {
					printf("Error en getnameinfo()");
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
						close(sd);
						printf("Servidor cerrado\n");
						return 0;
					default:
						printf("Comando no reconocido: %s\n", buf);
				}
			}
		}
	}
	close(sd);
	for (i=0;i<10;i++)
		wait(&children[i]);
	return 0;
}
