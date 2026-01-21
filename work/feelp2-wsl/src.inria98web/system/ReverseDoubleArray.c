/*
 * FEEL system Prototype Version 2
 * 
 * File     ReverseDoubleArray.c
 * Made     1992/08/26
 * Modified 
 * Version  0.0
 *
 * Purpose: Reverse double array
 *
 */
#include <stdio.h>

void ReverseDoubleArray(n,d)
     int n;
     double d[];
{
    double x;
    int i;

    for(i=0;i<n/2;i++) {
	x = d[i];
	d[i] = d[n-i-1];
	d[n-i-1] = x;
    }

    return;
}
