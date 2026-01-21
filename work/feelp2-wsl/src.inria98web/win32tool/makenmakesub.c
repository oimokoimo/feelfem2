#include <stdio.h>

void main(argc,argv)
int argc;
char *argv[];
{
    char buf[BUFSIZ];
    fgets(buf,sizeof(buf),stdin);
    printf("%s.lib :: %s",argv[1],buf);

    fgets(buf,sizeof(buf),stdin);
    printf("\tcl /c %s",buf);

    fgets(buf,sizeof(buf),stdin);
    printf("\tlib /OUT:%s.lib %s",argv[1],buf);
}

