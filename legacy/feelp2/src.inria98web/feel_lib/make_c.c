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

main()
{
    char *cp;
    char buf[BUFSIZ];
    FILE *fp;

    fp = fopen("basic_libraries.c","w");
    if(fp == NULL) {
	fprintf(stderr,"cannot write to file.\n");
	exit(1);
    }

    fprintf(fp,"#include <stdio.h>\n\n");
    fprintf(fp,"void basic_libraries( fp )\n");
    fprintf(fp,"     FILE *fp;\n");
    fprintf(fp,"{\n");


    while(gets(buf)) {
	if(buf[0] == ';') continue;
	cp = buf;
	fprintf(fp,"  fprintf(fp,\"");
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
