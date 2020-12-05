#include <stdio.h>
#include <unistd.h>

int main() {
   printf("longitud maxima de argumentos: %li\n", sysconf(_SC_ARG_MAX));
   printf("numero maximo de hijos: %li\n", sysconf(_SC_CHILD_MAX));
   printf("numero maximo de ficheros: %li\n", sysconf(_SC_OPEN_MAX));
   return 1;
}
