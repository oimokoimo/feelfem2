/*
 *  color.c
 *
 */ 
#include "xplot.h"

void xplot_color(n)
unsigned long n;
{
    Xplot *nowp;
    static unsigned long color_sav = 99999;

    if(color_sav == n) return;

    nowp = Xplot_win[Xplot_plane_no];

    XSetForeground(nowp->dpy,nowp->gc,n);
    color_sav = n;

    return;
}

