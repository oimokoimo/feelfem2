/*
 * FEEL system Prototype Version 2
 * 
 * File     OpenFile.c
 * Made     1992/09/24
 * Modified 
 * Version  0.0
 *
 * Purpose: Open UNIX FILE
 *
 */

#include <stdio.h>
#include "system.h"
#include "../feel_def/feel_msg.h"

static FILE *feel_fp = NULL;
extern int   one_file;

FILE *OpenFileToRead( filename )
     char *filename;
{
    FILE *fp;

    fp = fopen(filename , "r" );
    
    if(fp == NULL) {
	OpenFileToReadAbort( filename );
    }

    return(fp);
}

      
FILE *OpenFileToWrite( filename )
     char *filename;
{
    FILE *fp;

    if(one_file == 1 && strindex(filename,".f") 
                     && !streq(filename,"feel_main.f")) {
	if(feel_fp == NULL) {
	    feel_fp = fopen("feelgo.f","w");
	    if(feel_fp == NULL) OpenFileToWriteAbort( "feelgo.f" );
	}
	return(feel_fp);
    }

    fp = fopen(filename , "w" );
    
    if(fp == NULL) {
	OpenFileToWriteAbort( filename );
    }
    return(fp);
}

void CloseEachOneFile( fp )
     FILE *fp;
{
    if(fp == feel_fp) return;
    else              fclose(fp);
}

void CloseOneFile()
{
    fclose(feel_fp);
    return;
}



      

