#include <stdio.h>
main(argc,argv)
int argc;
char *argv[];
{
    FILE *fp,*fpw;
    int   array_size;
    int ret;
    char buf[BUFSIZ];
    
    if(argc != 2) {
	fprintf(stderr,"Usage: %s [FEEL ARRAY SIZE]\n",argv[0]);
	exit(1);
    }
    array_size = atoi(argv[1]);

    if(array_size == 0) {
	fprintf(stderr,"Usage: %s [FEEL ARRAY SIZE]\n",argv[0]);
	exit(1);
    }

    fp = fopen("feel_main.f","r");
    if(fp == NULL) {
	fprintf(stderr,"No FEEL/FORT77 sources\n");
	exit(1);
    }

    fpw = fopen("#feel_main.f#","w");
    if(fpw == NULL) {
	fprintf(stderr,"Cannot open temporary file\n");
	exit(1);
    }
    
    while(fgets(buf,BUFSIZ,fp) && !strindex(buf,"(MAX_FEEL =")) {
	fputs(buf,fpw);
    }

    fprintf(fpw,"      parameter (MAX_FEEL = %d)\n",array_size);


    while(fgets(buf,BUFSIZ,fp)) {
	fputs(buf,fpw);
    }

    fclose(fp); fclose(fpw);

    system("mv \\#feel_main.f\\# feel_main.f");
    
    exit(0);
}





