#include <stdio.h>

void main()
{
   char buf[BUFSIZ];

   while(gets(buf)) {
      printf("  SW(\"%s\");\n",buf);
   }
}
