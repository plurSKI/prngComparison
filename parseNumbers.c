#include<stdio.h>
#include<stdlib.h>

int main( int argc, char** argv )
{
   FILE* fp;
   char tmp_str[16];

   fp = fopen(argv[1], "r");
   if( fp == NULL)
   {
      fprintf(stderr, "Could not open file: %s\n", argv[1]);
      return -1;
   }

   while(fscanf(fp, "%s", tmp_str ) != EOF) 
      printf("%c",  (unsigned char)(atoi(tmp_str)));

   return 0;
}
