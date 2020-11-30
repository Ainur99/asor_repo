#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
   int err;
   if (setuid(0)<0) {
      err = errno;
      printf("%i\n", err);
      printf("%s\n", strerror(err));
   }
   return 1;
}
