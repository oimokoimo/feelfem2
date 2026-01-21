/*
 *
 *    point,fpoint
 *
 */


#include "xplot.h"


point(x,y)
     int x,y;
{
    Xplot *nowp;
    int x1,y1;

    if(Xplot_PostScript == YES) {
/*	point_ps(x,y); */
	fprintf(stderr,"point_ps is not made now.\n");
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("cont")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];


    x1 = ( x  - nowp->spx0) * nowp->xlen / nowp->spdx;
    y1 = ( y  - nowp->spy0) * nowp->ylen / nowp->spdy;
    
    nowp->cpx = x;
    nowp->cpy = y;
    
    y1 = nowp->ylen - y1;

    XDrawPoint( nowp->dpy, nowp->win,nowp->gc,x1,y1 );
    
    return;
}


fpoint(x,y)
     double x,y;
{
    Xplot *nowp;
    int x1,y1;

    if(Xplot_PostScript == YES) {
/*	fpoint_ps(x,y); */
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("fpoint")) return;            /* already open? */
    nowp = Xplot_win[Xplot_plane_no];

    x1 = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y1 = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

    nowp->dcpx = x;
    nowp->dcpy = y;
    
    y1 = nowp->ylen - y1;
    
    XDrawPoint( nowp->dpy, nowp->win,nowp->gc,x1,y1 );

    return;
}



