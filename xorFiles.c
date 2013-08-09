#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TILL_EOF -1

typedef enum { FALSE, TRUE } boolean; 

struct file_list 
{
   FILE* fp;
   struct file_list* next;
};
typedef struct file_list file_item;


int main( int argc, char** argv )
{
   file_item *head = NULL;
   file_item *curr = NULL;
   int i;
   char x, c;
   int bytesOut = TILL_EOF; // Number of bytes to output
   boolean printableOnly = FALSE;
   boolean foundEOF = FALSE;
 
   for( i = 0; i < argc; i ++ )
   {
      // Handle command line options
      if ( strstr( argv[i], "-p") ==  argv[i] ) 
      {
         printableOnly = TRUE;
      }
      else if ( strstr( argv[i], "--help") ==  argv[i] )
      {
         printf("Usage: %s [-p] [-n=####] file1 file2 ... fileN\n-p == only display printable characters\n-n=#### number of bytes to output, if not specified then it will go till the first EOF is encountered\n");
         return 0;
      }
      else if ( strstr( argv[i], "-n=" ) == argv[i] )
      {
         bytesOut = atoi(argv[i]+3);
      } 
      else 
      {
         // Open the file and store it in the linked list
         curr = (file_item*) malloc(sizeof(file_item));
         curr->fp = fopen(argv[i], "r");
         if( curr->fp == NULL)
         {
            fprintf(stderr, "Could not open file: %s\n", argv[i]);
            return -1;
         }
         curr->next = head;
         head = curr;
      }
   }

   // Start the xor of the files
   while ( bytesOut != 0 )
   {
      if(bytesOut != TILL_EOF) bytesOut --;

      // Step through every file
      x = 0;
      curr = head;
      while(curr != NULL && curr->next != NULL)
      {
         // Must store in integer to catch EOF
         i = fgetc(curr->fp);
	 c = (char)i;
         if( i == EOF )
         {
            // If only going to the EOF quit
            if( bytesOut == TILL_EOF ) 
            {
              curr = NULL;
              bytesOut = 0;
	      foundEOF = TRUE; // Don't want to put the EOF it will screw up the filesize
              continue;
            } 
            else 
            {
               rewind( curr->fp ); // Go back to the file's beginning
            }
         } 
         else
         {
            x ^= c;
         }
         curr = curr->next;
      }

      if( printableOnly == TRUE)
      {
         if( x >= 0x20 && x <= 0x7E) printf("%c", x);
         else bytesOut ++; // Will need another byte
      }
      else if( foundEOF == FALSE )
      {
         printf("%c", x);
      }

   }

   // Close open files
   curr = head;
   while( curr != NULL && curr->next != NULL )
   {
     fclose(curr->fp);
     curr = curr->next;
   }
   return 0;
}
