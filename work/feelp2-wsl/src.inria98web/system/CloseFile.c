/*
 * FEEL system Prototype Version 2
 * 
 * File     CloseFile.c
 * Made     1992/09/24
 * Modified 
 * Version  0.0
 *
 * Purpose: close file
 *
 */

#include <stdio.h>
#include "system.h"

extern int one_file;

void CloseFile( fp )
     FILE *fp;
{
    if(one_file == 1) {
	CloseEachOneFile(fp);
    }
    else {
	fclose(fp);
    }
    return;
}

