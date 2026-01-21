/*
 *  arrowhead,farrowhead        psplot routine  1996/04/16
 *
 *  draw line from current point to the specified point
 *
 */

#include <stdio.h>
#include "psplot.h"

#define ARROWHEAD_DOT 4
/*
arrowhead_ps(x,y)
     int x,y;
{
    PSplot *nowp;
    double x1,y1;

    if(is_psplot_plane_err("arrowhead")) return;  

    nowp = PSplot_win[PSplot_plane_no];



    x1 = ( x  - nowp->spx0) * nowp->xlen / nowp->spdx;
    y1 = ( y  - nowp->spy0) * nowp->ylen / nowp->spdy;
    
    nowp->cpx = x;
    nowp->cpy = y;
    

    x1 = x1 + GX;
    y1 = y1 + GY;

    fprintf(nowp->fp,"N %5.1f %5.1f MT  %5.1f %5.1f LT ST\n",
		     x1-ARROWHEAD_DOT,y1-ARROWHEAD_DOT,x1+ARROWHEAD_DOT,y1+ARROWHEAD_DOT);

    fprintf(nowp->fp,"N %5.1f %5.1f MT  %5.1f %5.1f LT ST\n",
		     x1+ARROWHEAD_DOT,y1-ARROWHEAD_DOT,x1-ARROWHEAD_DOT,y1+ARROWHEAD_DOT);

    
    return;
}
*/


farrowhead_ps(x1,y1,x2,y2)
     double x1,y1,x2,y2;
{
    PSplot *nowp;

    double xx,yy;
    double dx,dy;
    double sx,sy,r;


    if(is_psplot_plane_err("cont")) return;            /* already open? */
    nowp = PSplot_win[PSplot_plane_no];


    xx = ( x2   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    yy = ( y2   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

    
    nowp->dcpx = x2;
    nowp->dcpy = y2;


    xx = xx + GX;
    yy = yy + GY;


    dx = x2 - x1;
    dy = y2 - y1;

    sx =  dy - dx;
    sy = -dx - dy;

    r  = (double)sqrt(sx*sx + sy * sy);
    sx = sx/r;  sy = sy/r;

    fprintf(nowp->fp,"N %5.1f %5.1f MT  %5.1f %5.1f LT ST\n",xx,yy,
	    xx + sx * ARROWHEAD_DOT, yy + sy * ARROWHEAD_DOT);
    fprintf(nowp->fp,"N %5.1f %5.1f MT  %5.1f %5.1f LT ST\n",xx,yy,
	    xx + sy * ARROWHEAD_DOT, yy - sx * ARROWHEAD_DOT);

    return;
}

