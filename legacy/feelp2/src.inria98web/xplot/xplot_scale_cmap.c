/*
 *  xplot_scale_cmap.c
 *
 *  make color map for scale drawing
 */

#include "xplot.h"

unsigned long *xplot_scale_cmap()
{
    Xplot *nowp;
    static unsigned long scale[SCALE_COLORS];
    int i;
    XColor c;

    nowp = Xplot_win[Xplot_plane_no];

    for(i=0;i<SCALE_COLORS;i++) {
	c.red = 65535L * (unsigned long)(SCALE_COLORS-i+1) /  SCALE_COLORS ;
	c.green = 0L;
	c.blue = 65535L * (unsigned long)(i+1) /  SCALE_COLORS ;

	XAllocColor( nowp->dpy,nowp->cmap,&c);

	scale[i] = c.pixel;

    }

    return(scale);
}

xplot_setfg( c )
     unsigned long c;
{
    Xplot *nowp;
    nowp = Xplot_win[Xplot_plane_no];
    
    XSetForeground(nowp->dpy,nowp->gc,c);

    return;
}
