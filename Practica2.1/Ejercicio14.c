#include <stdio.h>
#include <time.h>

int main() {
   int year;
   time_t tim;
   struct tm *t;
   time(&tim);
   t = localtime(&tim);
   year = t->tm_year;
   printf("año: %i\n", year+1900);
   return 1;
}
