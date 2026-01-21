/*
 * FEEL system Prototype Version 2
 * 
 * File     GetMaxInteger.c
 * Made     1992/08/26
 * Modified 
 * Version  0.0
 *
 * Purpose: Choose maximum value from given integer array;
 *
 */

int GetMaxInteger( n , dat)
     int n;
     int dat[];
{
    int i,max;
    
    max = dat[0];

    for(i=1;i<n;i++) {
	if(max < dat[i]) max = dat[i];
    }

    return(max);
}

	
