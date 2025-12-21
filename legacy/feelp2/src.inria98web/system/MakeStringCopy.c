/*
 *   FEEL system    MakeStringCopy.c
 *  
 *   Get Memory and copy 
 *
 */

#include <stdio.h>

char *MakeStringCopy( s )
     char *s;
{
    char *cp;

    cp = (char *)FEEL_GetMemory(strlen(s)+1);

    strcpy(cp,s);
    return (cp);
}

