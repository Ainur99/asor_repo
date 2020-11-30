#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
   int i;
   for (i = 1; i <= 255; i++) {
      printf("Error numero %i: %s\n", i, strerror(i));
   }
   return 1;
}
