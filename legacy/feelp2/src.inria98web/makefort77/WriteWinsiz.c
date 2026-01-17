#include <stdio.h>

extern int web_exec;

WriteWinsiz( fp , size )
FILE *fp;
int   size;
{
   if(web_exec) size = 100;

   fprintf(fp,"* Window Size\n");
   fprintf(fp,"      IWW = %d\n",size);
   fprintf(fp,"      IWH = %d\n",size);
   fprintf(fp,"*\n");

   return;
}
