#include <stdio.h>

char *from[] = { "oimo","koimo","TANEIMO" };
char *to  [] = { "XXX","YYY","ZZZ" };
int  terms = 3;
int main()
{
   char buf[BUFSIZ];
   char *term_convert();

   while(gets(buf)) {
	printf("%s\n",term_convert(buf,from,to,terms));
   }
}

print_yylineno() {}
