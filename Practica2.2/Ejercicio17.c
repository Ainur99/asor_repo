#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char** argv) {

   int sum = 0;
   char name[NAME_MAX];
   char* path;
   DIR *dir;
   struct dirent *desc;
   struct stat st;

   if (argc != 2) {
      printf("Numero de argumentos invalido. Uso: %s <directorio>\n", argv[0]);
      return 0;
   }
   if ((dir = opendir(argv[1])) == NULL) {
      printf("Ruta \"%s\" no valida\n", argv[1]);
      return 0;
   }
   while ((desc = readdir(dir))!=NULL) {
      path = malloc(sizeof(char)*(strlen(argv[1])+strlen(desc->d_name))+2);
      strcpy(path, argv[1]);
      strcat(path, "/");
      strcat(path, desc->d_name);
      if (stat(path, &st) != 0) {
         printf("Error acceso: stat %s\n", desc->d_name);
         free(path);
         return 0;
      }
      if (S_ISDIR(st.st_mode)) {
         printf("%s/\n", desc->d_name);
      }
      else if (access(desc->d_name, X_OK) == 0) {
         printf("%s*\n", desc->d_name);
         sum+=st.st_size;
      }
      else if (S_ISREG(st.st_mode)) {
         printf("%s\n", desc->d_name);
         sum+=st.st_size;
      }
      else if (S_ISLNK(st.st_mode)) {
         readlink(path, name, NAME_MAX);
         printf("%s->%s\n", desc->d_name, name);
         sum+=st.st_size;
      }
      free(path);      
   }
   printf("Total size: %.2f Kb\n", ((float)sum/1024));   
   return 0;
}
