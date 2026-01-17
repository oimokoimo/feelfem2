/*
 *  xplot_XDrawLine        xplot routine
 *
 *  call the Xlib routine XDrawLine  (separated for redraw)
 *  
 */

#include "xplot.h"



xplot_XDrawLine(dpy,win,gc,a,b,c,d)
     Display *dpy;
     Window   win;
     GC        gc;
{
    Xplot *nowp;

    nowp = Xplot_win[Xplot_plane_no];

    XDrawLine(dpy,win,gc,a,b,c,d);

/*
    if(nowp->redraw_ptr + 6 > MAX_REDRAW) return;

    nowp->redraw[nowp->redraw_ptr++] = 1;
    nowp->redraw[nowp->redraw_ptr++] = a;
    nowp->redraw[nowp->redraw_ptr++] = b;
    nowp->redraw[nowp->redraw_ptr++] = c;
    nowp->redraw[nowp->redraw_ptr++] = d;
    nowp->redraw[nowp->redraw_ptr]   = 0;
*/

    return;
}



