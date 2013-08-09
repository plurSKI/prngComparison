#include<stdio.h>
#include<time.h>

#define TICKS_TO_WAIT 32

int main( int argc, char** argv)
{
   int i;
   int bytes = 1024;
   unsigned long long counter = 1;
   clock_t tick_old, tick_new;
       
   if(argc > 1) bytes = atoi(argv[1]);
   for( i = 0; i < bytes; i ++ )
   {
      tick_old = clock();
      while(clock() < tick_old + TICKS_TO_WAIT) counter ++;
           printf("%c", counter % 256);
   }
   return 0;
}

