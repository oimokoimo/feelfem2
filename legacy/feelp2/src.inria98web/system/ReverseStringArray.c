/*
 *      FEEL utility function  ReverseStringArray.c
 *
 *       for domain_st,region_st functions
 */

void ReverseStringArray(n,s)
     int n;
     char *s[];
{
    char *cp;
    int i;
    
    for(i=0;i<n/2;i++) {
	cp = s[i];
	s[i] = s[n-i-1];
	s[n-i-1] = cp;
    }
    return;
}
