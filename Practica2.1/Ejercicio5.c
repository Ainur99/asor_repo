#include <stdio.h>
#include <sys/utsname.h>

int main() {
   struct utsname buf;
   if (uname(&buf)<0) {
      perror("Error");
      return 1;
   }
   printf("%s\n", buf.sysname);
   printf("%s\n", buf.nodename);
   printf("%s\n", buf.release);
   printf("%s\n", buf.version);
   printf("%s\n", buf.machine);
   printf("%s\n", buf.domainname);
   return 1;
}
