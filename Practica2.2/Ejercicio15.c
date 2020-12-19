#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char** argv) {
   int init, end, fd, off;
   time_t t;
   struct tm *clk;
   if (argc != 4) {
      printf("Numero de argumentos incorrecto. Argumentos: <ruta al archivo consultado> <inicio de region> <fin de region>\n");
      return 0;
   }
   if (argv[2] > argv[3]) {
      init = atoi(argv[3]);
      end = atoi(argv[2]);
   }
   else {
      init = atoi(argv[2]);
      end = atoi(argv[3]);
   }
   fd = open(argv[1], O_RDWR);
   off = lseek(fd, init, SEEK_SET);
   if (lockf(fd, F_TLOCK, end)!=-1) {
      printf("Cerrojo desbloqueado\n");
      time(&t);
      clk = gmtime(&t);
      printf("%i:%i\n",clk->tm_hour, clk->tm_min);
      sleep(30);
      lockf(fd, F_ULOCK, end);
   }
   else {
      printf("Cerrojo bloqueado\n");
   }
   close(fd);
   return 0;
}
