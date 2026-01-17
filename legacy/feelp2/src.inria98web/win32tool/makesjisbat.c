#include <stdio.h>
void main(argc,argv)
int argc;
char *argv[];
{
    int i;
    for(i=1;i<argc;i++) {
	changeslash(argv[i]);
	printf("nkf -s <%s >ooo.tmp\n",argv[i]);
	printf("copy ooo.tmp %s\n",argv[i]);
    }
}
changeslash(s)
char *s;
{
  while(*s) {
    if(*s == '/') *s = '\\';
    s++;
  }
}
