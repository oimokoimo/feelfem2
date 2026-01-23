/*
 * FEEL system Prototype Version 2
 * 
 * File     OpenPipe.c
 * Made     1992/09/24
 * Modified 
 * Version  0.0
 *
 * Purpose:
 *
 */

#include <stdio.h>
#include "../feel_def/feel_msg.h"

extern FILE *popen(const char *command, const char *type);
extern int   pclose(FILE *stream);

FILE *OpenPipeToRead( cmd )
     char *cmd;
{
    FILE *pfp;
    
    pfp = popen(cmd ,"r");

    if(pfp == NULL) {
	OpenPipeToReadAbort( cmd );
    }

    return(pfp);
}

