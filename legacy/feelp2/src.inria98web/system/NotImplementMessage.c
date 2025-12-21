/*
 * FEEL system Prototype Version 2
 * 
 * File     NotImplementMessage.c
 * Made     1992/09/04
 * Modified 
 * Version  0.0
 *
 * Purpose: Output Not Implemented Message.
 *
 */

#include <stdio.h>

#define STRESS  fprintf(stderr,"%c[5m",27)
#define NORMAL  fprintf(stderr,"%c[0m",27)

int not_implemented = 0;

NotImplement( s )
     char *s;
{
    
    STRESS;

    fprintf(stderr,"NOT IMPLEMENTED MODULE [%38s]\n",s);
    
    NORMAL;

    not_implemented ++;

    return;
}
