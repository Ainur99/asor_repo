#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char** argv) {

   int fd;   

   if (argc != 2) {
      printf("Numero de argumentos invalido. Uso: %s <fichero>\n", argv[0]);
      return 0;
   }
   if ((fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1) {
      printf("Error al abrir %s\n", argv[1]);
      return 0;
   }
   if (dup2(fd,1) == -1) {
      printf("Error al duplicar la salida estandar\n");
      close(fd);
      return 0;
   }
   if (dup2(fd,2) == -1) {
      printf("Error al duplicar la salida de error\n");
      close(fd);
      return 0;
   }
   printf("Hello world!\n");
   printf("Esto es una prueba\n");
   fprintf(stderr, "Error: Hello world!\n");
   fprintf(stderr, "Error: Esto es una prueba\n");
   close(fd);
   return 0;
}
