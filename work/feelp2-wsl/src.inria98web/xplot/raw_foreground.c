/*
 *    raw_foreground.c
 */

#include "xplot.h"

raw_foreground( n )
     int n;
{
    Xplot *nowp;

    nowp = Xplot_win[Xplot_plane_no];


    XSetForeground(nowp->dpy,nowp->gc,n);
    return;
}


