#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main() {
   uid_t id;
   struct passwd *pass;
   id = getuid();
   pass = getpwuid(id);
   printf("uid = %i\n", id);
   printf("euid = %i\n", geteuid());
   printf("nombre de usuario: %s\n", pass->pw_name);
   printf("directorio home: %s\n", pass->pw_dir);
   printf("descripcion de usuario: %s\n", pass->pw_gecos);
   return 1;
}
