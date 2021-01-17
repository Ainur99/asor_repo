#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
	
	pid_t pid, ppid, pgid, sid;
	int max_buf = 256;
	char buf[256];
	struct rlimit* rlim;
	
	pid  = getpid();
	ppid = getppid();
	pgid = getpgid(0);
	sid  = getsid(0);
	
	printf("PID: %i\n", pid);
	printf("PPID: %i\n", ppid);
	printf("PGID: %i\n", pgid);
	printf("SID: %i\n", sid);
	
	if (getcwd(buf, max_buf) == NULL) 
		printf("No cabe el nombre del directorio de trabajo en el buffer\n");
	else
		printf("Directorio de trabajo: %s\n", buf);
	
	getrlimit(RLIMIT_NOFILE, rlim);
	printf("Maximo numero de descriptores de archivo: %i\n", rlim->rlim_max);
	
	return 0;
}
