#include <stdio.h>
#include <unistd.h>

int main() {
   printf("%li\n", pathconf("/", _PC_LINK_MAX));
   printf("%li\n", pathconf("/", _PC_PATH_MAX));
   printf("%li\n", pathconf("/", _PC_NAME_MAX));
   return 1;
}
