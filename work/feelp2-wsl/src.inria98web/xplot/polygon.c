/*
 *   polygon.c
 *
 */

#include <X11/Xlib.h>
#include "xplot.h"

polygon(n,x,y)
     int n;
     int x[],y[];
{
    int i;
    Xplot *nowp;
    XPoint xpt[MAX_POLYGON_POINTS];


    if(Xplot_PostScript == YES) {
	polygon_ps(n,x,y);
    }
    if(Xplot_X11 == NO) {
	return;
    }

    nowp = Xplot_win[Xplot_plane_no];


    if(n > MAX_POLYGON_POINTS) {
	fprintf(stderr,"Too many points in polygon routine\n");
	return;
    }
    for(i=0;i<n;i++) {
	xpt[i].x = ( x[i]  - nowp->spx0) * nowp->xlen / nowp->spdx;
        xpt[i].y = ( y[i]  - nowp->spy0) * nowp->ylen / nowp->spdy;
    }

    xplot_polygon(n,xpt);

    return;
}

fpolygon(n,x,y)
     int n;
     double x[],y[];
{
    Xplot *nowp;
    int i;
    XPoint xpt[MAX_POLYGON_POINTS];

    if(Xplot_PostScript == YES) {
        fpolygon_ps(n,x,y);
    }
    if(Xplot_X11 == NO) {
        return;
    }

    nowp = Xplot_win[Xplot_plane_no];

    
    if(n > MAX_POLYGON_POINTS) {
	fprintf(stderr,"Too many points in polygon routine\n");
	return;
    }
    for(i=0;i<n;i++) {
	xpt[i].x=(x[i]-nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
        xpt[i].y=(y[i]-nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
	xpt[i].y = nowp->ylen - xpt[i].y ;
    }

    xplot_polygon(n,xpt);

    return;
}

xplot_polygon(n,xpt)
int n;
XPoint *xpt;
{
    Xplot *nowp;
    nowp = Xplot_win[Xplot_plane_no];


    XFillPolygon(nowp->dpy,nowp->win,nowp->gc,xpt,n,Convex,
    CoordModeOrigin);
    XFlush(nowp->dpy);
    return;
}

/* FORTRAN interface */
fpolygon_(n,x,y)
int *n;
double *x,*y;
{
    fpolygon(*n,x,y);
}
