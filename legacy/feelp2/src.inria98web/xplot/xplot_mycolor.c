/*
 *  xplot_mycolor    xplot routine
 *
 *    get color code from color name
 */

#include "xplot.h"

unsigned long xplot_mycolor( color_name)
     char    *color_name;
{
    Colormap cmap;
    Xplot   *nowp;
    XColor c0,c1;

    nowp = Xplot_win[Xplot_plane_no];

    cmap = DefaultColormap(nowp->dpy,0);
    XAllocNamedColor( nowp->dpy, cmap, color_name,&c1,&c0);
    
    return(c1.pixel);
}

void xcolor( color_name )
    char *color_name;
{
    Colormap cmap;
    Xplot   *nowp;
    XColor c0,c1;

    nowp = Xplot_win[Xplot_plane_no];

    cmap = DefaultColormap(nowp->dpy,0);
    XAllocNamedColor( nowp->dpy,nowp->cmap,  color_name,&c1,&c0);
    XSetForeground(nowp->dpy,nowp->gc,c1.pixel);
    return;
}
