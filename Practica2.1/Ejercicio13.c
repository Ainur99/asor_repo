#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
   struct timeval *mstime;
   long int t;
   int i;
   gettimeofday(mstime, NULL);
   t = mstime->tv_usec;
   for (i = 0; i<1000000; i++) {}
   gettimeofday(mstime, NULL);
   printf("tarda %li microsegundos \n", mstime->tv_usec - t);
   return 1;
}
