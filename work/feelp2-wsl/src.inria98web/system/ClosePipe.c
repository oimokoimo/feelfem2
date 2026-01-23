/*
 * FEEL system Prototype Version 2
 * 
 * File     ClosePipe.c
 * Made     1992/09/24
 * Modified 
 * Version  0.0
 *
 * Purpose: close pipeline
 *
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

void ClosePipe( fp )
     FILE *fp;
{
    pclose(fp);
    return;
}
