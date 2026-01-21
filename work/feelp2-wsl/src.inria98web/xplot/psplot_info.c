/*
 *  xplot_info.c
 *
 *  information routine for xplot library
 *
 *
 *
 */
#include "psplot.h"

void logical2pixel_ps(ix,iy,x,y)
int ix,iy;
double *x,*y;
{
    PSplot *nowp;
    nowp = PSplot_win[PSplot_plane_no];

    *x  =  (double)ix * nowp->dspdx / (double)nowp->xlen;
    *y  =  (double)iy * nowp->dspdy / (double)nowp->ylen;
    return;
}



