/*
 *   FEEL system   File.c
 *  
 *   File handle routines
 *
 */
#include <stdio.h>

FILE *OpenFile( filename )
     char *filename;
{
    FILE *fp;

    fp = fopen(filename,"w");
    if(fp == NULL ) {
	char buf[BUFSIZ];
        fprintf(buf,"OPEN %s to write failed.\n",filename);
	FatalError(buf);
    }
    return(fp);
}


FILE *ReadOpen( filename )
    char *filename;
{
    FILE *fp;

    fp = fopen(filename,"r");
    if( fp == NULL ) {
	char buf[BUFSIZ];
        fprintf(buf,"OPEN %s to read failed.\n",filename);
	FatalError(buf);
    }
    return(fp);
}




