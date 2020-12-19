#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char** argv) {
   struct stat st;
   char hard[255], sym[255];
   if (argc != 2) {
      printf("Numero de argumentos incorrecto. Argumentos: <ruta al archivo para crear el enlace>\n");
      return 0;
   }
   stat(argv[1], &st);
   if ((st.st_mode & S_IFMT) == S_IFREG) {
      strcpy(hard, argv[1]);
      strcpy(sym, argv[1]);
      strcat(hard, ".hard");
      if (link(argv[1], hard) < 0)
         perror(NULL);
      strcat(sym, ".sym");
      if (symlink(argv[1], sym) < 0)
         perror(NULL);
   }
   return 0;
}
