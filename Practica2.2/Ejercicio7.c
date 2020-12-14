#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main (int argc, char** argv) {
   mode_t mask;
   if (argc != 2) {
      printf("Numero de argumentos incorrecto. Argumentos: <nombre del archivo a crear>");
      return 0;
   }
   mask = umask(0);
   umask(mask & 0730);
   open(argv[1], O_CREAT);
   umask(mask);
   return 0;
}
