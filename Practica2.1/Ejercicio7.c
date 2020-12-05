#include <stdio.h>
#include <unistd.h>

int main() {
   printf("maximo enlaces: %li\n", pathconf("/", _PC_LINK_MAX));
   printf("maximo de ruta: %li\n", pathconf("/", _PC_PATH_MAX));
   printf("maximo nombre de fichero: %li\n", pathconf("/", _PC_NAME_MAX));
   return 1;
}
