/*
 *  fontsize.c
 */

#include "xplot.h"

fontsize(n)
     int n;
{
    Xplot *nowp;

    if(Xplot_PostScript == YES) {
	fontsize_ps(n);
    }

    /* do nothing in case of X-Window */
    
    return;
}

fontsize_(n)
int *n;
{
  fontsize(*n);
  return;
}
