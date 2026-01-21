/*
 *  linewidth.c
 */

#include "xplot.h"

linewidth(n)
     int n;
{
    Xplot *nowp;

    if(Xplot_PostScript == YES) {
	linewidth_ps(n);
    }

    /* do nothing in case of X-Window */
    
    return;
}

linewidth_(n)
int *n;
{
  linewidth(*n);
  return;
}
