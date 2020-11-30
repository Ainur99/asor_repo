#include <stdio.h>
#include <unistd.h>

int main() {
   printf("%li\n", sysconf(_SC_ARG_MAX));
   printf("%li\n", sysconf(_SC_CHILD_MAX));
   printf("%li\n", sysconf(_SC_OPEN_MAX));
   return 1;
}
