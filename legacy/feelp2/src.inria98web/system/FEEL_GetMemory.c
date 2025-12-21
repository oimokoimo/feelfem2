/*
 * FEEL system Prototype Version 2
 * 
 * File     FEEL_GetMemory.c
 * Made     1992/08/20
 * Modified 
 * Version  0.0
 *
 * Purpose: Get Memory from heap area
 *
 */

#include <stdio.h>


char *FEEL_GetMemory( size )
     int size;
{
    char *cp,*cp2;
    
    if(size == 0) return(NULL);

    cp2 = cp = (char *)malloc( size );

    if(cp == NULL ) {
	SystemAbort("No more heap memory");
    }

    while(size) {
      *cp2 = '\0';
      cp2++;
      size--;
    }
    return(cp);
}

double *FEEL_GetMemory_double( n )
     int n;
{
    double *dble;

    dble = (double *) malloc ( n * sizeof (double));

    if(dble == NULL) {
	SystemAbort("No more heap memory(double)");
    }
    
    return(dble);
}


