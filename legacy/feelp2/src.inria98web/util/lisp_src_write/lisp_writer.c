/*
 * FEEL system Prototype Version 2
 * 
 * File     lisp_writer.c
 * Made     1992/09/24
 * Modified 
 * Version  0.0
 *
 * Purpose: make printf statements to produce lisp program.
 *
 */


#include <stdio.h>

main(argc,argv)
     int argc;
     char *argv[];
{
    char *cp;
    char buf[BUFSIZ];
    char fname[BUFSIZ];
    FILE *fp;

    if(argc != 2) {
	fprintf(stderr,"Usage: %s key-name < filename\n",argv[0]);
	exit(1);
    }

    cp =argv[1];
    while(*cp) {
	if(*cp == '-') *cp = '_';
	cp++;
    }

    sprintf(fname,"%s.c",argv[1]);
    fp = fopen(fname,"w");
    if(fp == NULL) {
	fprintf(stderr,"cannot open %s\n",argv[1]);
	exit(1);
    }

    fprintf(fp,"#include <stdio.h>\n\n");
    fprintf(fp,"void lisplib_%s( fp )\n",argv[1]);
    fprintf(fp,"     FILE *fp;\n");
    fprintf(fp,"{\n");


    while(gets(buf)) {
	if(buf[0] == ';') continue;
	cp = buf;
	fprintf(fp,"  LISP_SEND(fp,\"");
	while(*cp) {
	    switch(*cp) {
	      case '"':
		fprintf(fp,"\\\"");
		break;

	      case '\\':
		fprintf(fp,"\\\\");
		break;

	      case '%':
		fprintf(fp,"%%%%");
		break;
		
	      default:
		fprintf(fp,"%c",*cp);
		break;
	    }
	    cp++;
	}
	fprintf(fp,"\\n\");\n",buf);
    }
    fprintf(fp,"}\n");

    fclose(fp);


}
