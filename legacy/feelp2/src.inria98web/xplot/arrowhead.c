/*
 *  arrowhead                 xplot routine
 *
 *  draw batten mark
 *
 */

#include "xplot.h"

/* arrowhead(x,y)
     int x,y;
{
    Xplot *nowp;
    int xx,yy;


    if(Xplot_PostScript == YES) {
        arrowhead_ps(x,y);
    }
    if(Xplot_X11 == NO) {
        return;
    }

    if(is_xplot_plane_err("arrowhead")) return;           

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
*/

farrowhead(x1,y1,x2,y2)
     double x1,y1,x2,y2;
{
    Xplot *nowp;
    int xx,yy,ix,iy;

    double dx,dy;
    double sx,sy,r,sqrt();

    if(Xplot_PostScript == YES) {
        farrowhead_ps(x1,y1,x2,y2);
    }
    if(Xplot_X11 == NO) {
        return;
    }

    if(is_xplot_plane_err("farrowhead")) return;            /* already open? */

    dx = x2 - x1;
    dy = y2 - y1;

    sx =  dy - dx;
    sy = -dx - dy;

    r  = sqrt(sx*sx + sy * sy);
    sx = sx/r;  sy = sy/r;

    nowp = Xplot_win[Xplot_plane_no];

    xx = ( x2   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    yy = ( y2   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
    
    nowp->dcpx = x2;
    nowp->dcpy = y2;
    
    yy = nowp->ylen - yy;

    ix = 4 * sx;
    iy = 4 * sy;
    xplot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,xx,yy,xx+ix,yy-iy);
    xplot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,xx,yy,xx+iy,yy+ix);

    return;
}

