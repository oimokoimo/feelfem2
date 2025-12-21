/*
 * FEEL system Prototype Version 2
 * 
 * File     sort.c
 * Made     1992/09/03
 * Modified 
 * Version  0.0
 *
 * Purpose: sort functions
 *
 */

sort_int_min_max(n,dat)
     int n,dat[];
{
    int i,j;

    int swap_tmp;

    for(i=0;i<n;i++) {
	for(j=i+1;j<n;j++) {
	    if(dat[i] > dat[j]) {
		swap_tmp = dat[i] ;
		dat[i] = dat[j];
		dat[j] = swap_tmp;
	    }
	}
    }
    return;
}


       
