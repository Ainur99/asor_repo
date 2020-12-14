#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main (int argc, char** argv) {
   if (argc != 2) {
      printf("Numero de argumentos incorrecto. Argumentos: <nombre del archivo a crear>");
      return 0;
   }
   open(argv[1], O_CREAT, 0645);
   return 0;
}
