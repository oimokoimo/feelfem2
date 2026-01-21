/*
 * FEEL system Prototype Version 2
 * 
 * File     ReverseIntArray.c
 * Made     1992/09/07
 * Modified 
 * Version  0.0
 *
 * Purpose: Reverse integer array
 *
 */

void ReverseIntArray(n,d)
     int n;
     int d[];
{
    int x;
    int i;
    
    for(i=0;i<n/2;i++) {
	x = d[i];
	d[i] = d[n-i-1];
	d[n-i-1] = x;
    }
    return;
}
