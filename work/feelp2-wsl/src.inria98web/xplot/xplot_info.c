/*
 *  xplot_info.c
 *
 *  information routine for xplot library
 *
 *
 *
 */
#include <stdio.h>
#include "xplot.h"

void logical2pixel(ix,iy,x,y)
int ix,iy;
double *x,*y;
{
    Xplot *nowp;

    if(Xplot_PostScript == YES) {
	logical2pixel_ps(ix,iy,x,y);
    }
    if(Xplot_X11 == NO) {
	return;
    }
    
    nowp = Xplot_win[Xplot_plane_no];

    *x  =  (double)ix * nowp->dspdx / (double)nowp->xlen;
    *y  =  (double)iy * nowp->dspdy / (double)nowp->ylen;

/*
    fprintf(stderr,"Plane_no = %d\n",Xplot_plane_no);
    fprintf(stderr,"ix = %d  iy = %d\n",ix,iy);
    fprintf(stderr,"nowp->dspdx = %ld  nowp->dspdy = %ld\n",
	    nowp->dspdx,nowp->dspdy);
    fprintf(stderr,"In xplot_info, x = %ld, y = %ld\n",*x,*y);
    */

    return;
}






