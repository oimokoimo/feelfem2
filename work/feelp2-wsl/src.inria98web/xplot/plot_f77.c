/* 
 * plotf77.c   CALCOMP PLOT function interface routines
 *
 *
 */
#include "xplot.h"

plots_()
{
    openpl();
    fspace(0.0,0.0,10.0,10.0);   /* This size is for Iwanami's book */
    return;
}


plotv_()
{
    closepl();
}


plot_(x,y,ip)                    /* CAUTION  variables are REAL * 4 */
     float *x,*y;
     int *ip;
{
  double dx,dy;
  dx = *x;
  dy = *y;

  if(*ip < 0 || *ip == 3) {
    fmove(dx,dy);
  }
  else {
    if(*ip == 2) {
      fcont(dx,dy);
    }
    else {
      fprintf(stderr,"Illegal function (PLOT) %d\n",*ip);
    }
  }
}

