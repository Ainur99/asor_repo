#include <stdio.h>
#include <time.h>

#define MAX_STR 64

int main() {
   char str[MAX_STR];
   time_t tim;
   struct tm *t;
   time(&tim);
   t = localtime(&tim);
   strftime(str, MAX_STR, "%A, %d de %B de %Y, %H:%M", t);
   printf("%s\n", str);
   return 1;
}
