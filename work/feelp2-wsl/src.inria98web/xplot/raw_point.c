/*
 *
 *    point,fpoint
 *
 */


#include "xplot.h"


raw_point(x,y)
     int x,y;
{
    Xplot *nowp;

    /* X11 only */

    if(is_xplot_plane_err("raw_point")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];

    y = nowp->ylen - y;

    XDrawPoint( nowp->dpy, nowp->win,nowp->gc,x,y );
    
    return;
}
