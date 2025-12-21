#include <stdio.h>
#include "FEM_FORT77.h"


FILE *ReadOpen(),*OpenFile();


main(argc,argv) 
int argc;
char *argv[];
{
    FILE *fp_read,*fp_write;

    char buf[BUFSIZ];

    fp_read  = fopen(argv[1],"r");
    fp_write = fopen(argv[2],"w");

    while(fgets(buf,BUFSIZ,fp_read)) {
	if(buf[0] == '*' ||
	   buf[0] == 'c' ||
	   buf[0] == 'C' ) {
	    fprintf(fp_write,"%s",buf);
	    continue;
	}

	buf[strlen(buf)-1] = '\0';
	setF77string(fp_write,buf);
	putF77(fp_write);
    }

    fclose(fp_read);
    fclose(fp_write);
}

