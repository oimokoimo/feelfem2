#include <stdio.h>

main(argc,argv)
     int argc;
     char *argv[];
{
    FILE *fp;
    char buf[BUFSIZ];
    char *name ;
    char fname[BUFSIZ];

    if(argc != 2) {
	fprintf(stderr,"usage: %s fortran subroutine name\n",argv[0]);
	exit(1);
    }

    name = argv[1];

    sprintf(fname,"%s.c",name);
    
    fp = fopen(fname ,"w");
    if(fp == NULL) {
	fprintf(stderr,"cannot open %s to write.\n",fname);
	exit(1);
    }
    
    fprintf(fp,"/*\n");
    fprintf(fp,"   FEEL p2  MAKE FORTRAN LIBRARY   %s\n",name);
    fprintf(fp," */\n\n");

    fprintf(fp,"#include <stdio.h>\n");
    fprintf(fp,"#include \"../feel_def/feel_def.h\"\n");
    fprintf(fp,"#include \"../system/system.h\"\n\n");

    fprintf(fp,"#define FNAME \"%s.f\"\n",name);

    fprintf(fp,"lib_%s()\n",name);
    fprintf(fp,"{\n");

    fprintf(fp,"   FILE *fp;\n");
    fprintf(fp,"   StoreMakefile(FNAME,SYSTEM_LIBRARY);\n");

    fprintf(fp,"   if(LIMIT_FILE == 1) return;\n");

    fprintf(fp,"   fp = OpenFileToWrite( FNAME );\n");

    while(gets(buf)) {

	if(strindex(buf,"#COMMON")) { 
	    fprintf(fp,"   common_parameters(fp);\n");
	    fprintf(fp,"   COM;\n");
	    fprintf(fp,"   CommonBlock(fp);\n");
	    fprintf(fp,"   comment1(fp);\n");
	}
	else {
	
	    fprintf(fp,"   F77(\"");
	    f77_write(buf,fp);
	    fprintf(fp,"\\n\");\n");
	}
    }

    fprintf(fp," CloseFile(fp);\n");
    fprintf(fp," return;\n");
    fprintf(fp,"}\n");

    fclose(fp);
}


f77_write(cp , fp )
     char *cp;
     FILE *fp;
{
    
    while(*cp) {
	switch(*cp) {
	  case '"':
	    fprintf(fp,"\\\"");
	    break;

	  default:
	    fprintf(fp,"%c",*cp);
	}
	cp++;
    }
    return;
}
