#include <stdio.h>

int main() {
   if (setuid(0)<0) {
      perror("Error");
      return 1;
   }
   return 1;
}

