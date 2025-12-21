/*
 * FEEL system Prototype Version 2
 * 
 * File     FEEL_FreeMemory.c
 * Made     1992/08/20
 * Modified 1992/08/24
 * Version  0.0
 *
 * Purpose: Free Heap Memory
 *
 */

#include <stdio.h>

FEEL_FreeMemory( cp )
   char *cp;
{      
    free(cp);
    return;
}


