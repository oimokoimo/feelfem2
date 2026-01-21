/*
 *  peke,fpeke                 xplot routine
 *
 *  draw batten mark
 *
 */

#include "xplot.h"

peke(x,y)
     int x,y;
{
    Xplot *nowp;
    int xx,yy;


    if(Xplot_PostScript == YES) {
        peke_ps(x,y);
    }
    if(Xplot_X11 == NO) {
        return;
    }

    if(is_xplot_plane_err("peke")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];


    xx = ( x  - nowp->spx0) * nowp->xlen / nowp->spdx;
    yy = ( y  - nowp->spy0) * nowp->ylen / nowp->spdy;
    
    nowp->cpx = x;
    nowp->cpy = y;

    yy = nowp->ylen - yy;
    
    xplot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,xx-2,yy-2,xx+2,yy+2);
    xplot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,xx-2,yy+2,xx+2,yy-2);
    
    return;
}


fpeke(x,y)
     double x,y;
{
    Xplot *nowp;
    int xx,yy;

    if(Xplot_PostScript == YES) {
        fpeke_ps(x,y);
    }
    if(Xplot_X11 == NO) {
        return;
    }


    if(is_xplot_plane_err("fpeke")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];

    xx = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    yy = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
    
    nowp->dcpx = x;
    nowp->dcpy = y;
    
    yy = nowp->ylen - yy;
    
    xplot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,xx-2,yy-2,xx+2,yy+2);
    xplot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,xx-2,yy+2,xx+2,yy-2);

    return;
}


peke_(x,y)
     int *x,*y;
{
    peke(*x,*y);
    return;
}

fpeke_(x,y)
     double *x,*y;
{
    fpeke(*x,*y);
    return;
}

