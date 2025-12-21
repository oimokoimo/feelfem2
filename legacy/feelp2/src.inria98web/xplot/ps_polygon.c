/*
 *  cont,fcont        psplot routine
 *
 *  draw line from current point to the specified point
 *
 */

#include <stdio.h>
#include "psplot.h"

polygon_ps(n,x,y)
     int n;
     int x[],y[];
{
    PSplot *nowp;
    int i;
    double xx[MAX_POLYGON_POINTS];
    double yy[MAX_POLYGON_POINTS];

    if(is_psplot_plane_err("fpolygon")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];
    
    if(n > MAX_POLYGON_POINTS) {
	fprintf(stderr,"Too many points in polygon routine\n");
	return;
    }
    for(i=0;i<n;i++) {
      xx[i]=(double)(x[i]-nowp->spx0) * nowp->xlen / (double)nowp->spdx + GX;
      yy[i]=(double)(y[i]-nowp->spy0) * nowp->ylen / (double)nowp->spdy + GY;
    }

    PSplot_polygon(n,xx,yy);
    return;
}


fpolygon_ps(n,x,y)
     int n;
     double x[],y[];
{
    PSplot *nowp;
    int i;
    double xx[MAX_POLYGON_POINTS];
    double yy[MAX_POLYGON_POINTS];

    if(is_psplot_plane_err("fpolygon")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];
    
    if(n > MAX_POLYGON_POINTS) {
	fprintf(stderr,"Too many points in polygon routine\n");
	return;
    }
    for(i=0;i<n;i++) {
      xx[i]=(x[i]-nowp->dspx0) * (double)nowp->xlen / nowp->dspdx + GX;
      yy[i]=(y[i]-nowp->dspy0) * (double)nowp->ylen / nowp->dspdy + GY;
    }

    PSplot_polygon(n,xx,yy);

    return;
}

PSplot_polygon(n,x,y)
int n;
double x[],y[];
{
    int i;
    PSplot *nowp;

    nowp = PSplot_win[PSplot_plane_no];

    fprintf(nowp->fp,"N ");
    for(i=0;i<n;i++) {
      fprintf(nowp->fp,"%5.1f %5.1f",x[i],y[i]);
      if(i==0) fprintf(nowp->fp," MT\n");
      else     fprintf(nowp->fp," LT\n");
    }
    fprintf(nowp->fp,"CP FL\n");

    return;
}

