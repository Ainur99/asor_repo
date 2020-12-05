#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
   printf("uid = %i\n", getuid());
   printf("euid = %i\n", geteuid());
   return 1;
}
