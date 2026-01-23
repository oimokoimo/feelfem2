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
#include <stdlib.h>

void FEEL_FreeMemory( cp )
   void *cp;
{      
    free(cp);
    return;
}


