#include <unistd.h>
#include <string.h>
#include <stdio.h>

void hijo(int h_p, int p_h) {
	char buf[32],h_p_buf[32];
	int max_buf = 32, n, count = 0; 
	while (count < 10) {
		n = read(p_h, buf, max_buf);
		buf[n] = '\0';
		printf("Hijo: %s\n", buf);
		count++;
		sleep(1);
		if (count < 10) {
			write(h_p, "1", strlen("1"));
		}
		else {
			write(h_p, "q", strlen("q"));
		}
	}
	close(h_p);
	close(p_h);
}

void padre(int p_h, int h_p) {
	char buf[32],h_p_buf[32];
	int max_buf = 32, n;
	while (strcmp(h_p_buf, "q")) {
		n = read(0, buf, max_buf);
		buf[n] = '\0';
		write(p_h, buf, n);
		n = read(h_p, h_p_buf, max_buf);
		h_p_buf[n] = '\0';
	}
	close(h_p);
	close(p_h);
}

int main() {
	
	int p_h[2], h_p[2];
	
	pipe(p_h);
	pipe(h_p);
	
	switch (fork()) {
		case -1:
			perror("fork");
			break;
		case 0:
			close(h_p[0]);
			close(p_h[1]);
			hijo(h_p[1], p_h[0]);
			break;
		default:
			close(h_p[1]);
			close(p_h[0]);
			padre(p_h[1], h_p[0]);
	}
	
	return 0;
}
