/*
 *  cont,fcont        xplot routine
 *
 *  draw line from current point to the specified point
 *
 */

#include "xplot.h"

cont(x,y)
     int x,y;
{
    Xplot *nowp;
    int x1,x2,y1,y2;

    if(Xplot_PostScript == YES) {
	cont_ps(x,y);
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("cont")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];


    x1 = ( x  - nowp->spx0) * nowp->xlen / nowp->spdx;
    x2 = (nowp->cpx - nowp->spx0) * nowp->xlen / nowp->spdx;
    y1 = ( y  - nowp->spy0) * nowp->ylen / nowp->spdy;
    y2 = (nowp->cpy - nowp->spy0) * nowp->ylen / nowp->spdy;
    
    nowp->cpx = x;
    nowp->cpy = y;
    
    
    y1 = nowp->ylen - y1;
    y2 = nowp->ylen - y2;
    xplot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,x1,y1,x2,y2);
    
    return;
}


fcont(x,y)
     double x,y;
{
    Xplot *nowp;
    int x1,x2,y1,y2;

    if(Xplot_PostScript == YES) {
	fcont_ps(x,y);
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("cont")) return;            /* already open? */
    nowp = Xplot_win[Xplot_plane_no];

    x1 = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y1 = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

    x2 = (nowp->dcpx - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y2 = (nowp->dcpy - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
    
    nowp->dcpx = x;
    nowp->dcpy = y;
    
    y1 = nowp->ylen - y1;
    y2 = nowp->ylen - y2;
    
    xplot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,x1,y1,x2,y2);

    return;
}

fcont_abs(ix,iy)
int ix,iy;
{
    double x,y;
    int x1,y1,x2,y2;
    Xplot *nowp;

    if(Xplot_PostScript == YES) {
	fcont_abs_ps(x,y);
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("fcont_abs")) return;  /* already open? */

    nowp = Xplot_win[Xplot_plane_no];

    x  = nowp->dcpx + (double)ix * nowp->dspdx / (double)nowp->xlen;
    y  = nowp->dcpy + (double)iy * nowp->dspdy / (double)nowp->ylen;

    x1 = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y1 = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

    x2 = (nowp->dcpx - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y2 = (nowp->dcpy - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
    
    nowp->dcpx = x;
    nowp->dcpy = y;
    
    y1 = nowp->ylen - y1;
    y2 = nowp->ylen - y2;

    fprintf(stderr,"(%d,%d)-(%d,%d)\n",x1,y1,x2,y2);
    
    xplot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,x1,y1,x2,y2);

    return;
}
