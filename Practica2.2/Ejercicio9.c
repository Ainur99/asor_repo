#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv) {
   struct stat st;
   char* mode;
   if (argc != 2) {
      printf("Numero de argumentos incorrecto. Argumentos: <nombre del archivo a consultar>\n");
      return 0;
   }  
   stat(argv[1], &st);
   switch(st.st_mode & S_IFMT) {
      case S_IFSOCK:
         mode = "socket";
         break;
      case S_IFLNK:
         mode = "enlace simbolico";
         break;
      case S_IFREG:
         mode = "archivo regular";
         break;
      case S_IFBLK:
         mode = "bloque de dispositivo";
         break;
      case S_IFDIR:
         mode = "directorio";
         break;
      case S_IFCHR:
         mode = "character device";
         break;
      case S_IFIFO:
         mode = "FIFO";
         break;
      default:
         mode = "desconocido";
   }
   printf("Archivo: %s\n", argv[1]);
   printf("Major: %i\n", major(st.st_dev));
   printf("Minor: %i\n", minor(st.st_dev));
   printf("I-node: %i\n", st.st_ino);
   printf("Tipo: %s\n", mode);
   printf("Ultimo acceso: %i\n", st.st_atim);
   return 0;
}
