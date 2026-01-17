/*
 *  peke,fpeke        psplot routine  1996/04/16
 *
 *  draw line from current point to the specified point
 *
 */

#include <stdio.h>
#include "psplot.h"

#define PEKE_DOT 2

peke_ps(x,y)
     int x,y;
{
    PSplot *nowp;
    double x1,y1;

    if(is_psplot_plane_err("peke")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];



    x1 = ( x  - nowp->spx0) * nowp->xlen / nowp->spdx;
    y1 = ( y  - nowp->spy0) * nowp->ylen / nowp->spdy;
    
    nowp->cpx = x;
    nowp->cpy = y;
    

    x1 = x1 + GX;
    y1 = y1 + GY;

    fprintf(nowp->fp,"N %5.1f %5.1f MT  %5.1f %5.1f LT ST\n",
		     x1-PEKE_DOT,y1-PEKE_DOT,x1+PEKE_DOT,y1+PEKE_DOT);

    fprintf(nowp->fp,"N %5.1f %5.1f MT  %5.1f %5.1f LT ST\n",
		     x1+PEKE_DOT,y1-PEKE_DOT,x1-PEKE_DOT,y1+PEKE_DOT);

    
    return;
}


fpeke_ps(x,y)
     double x,y;
{
    PSplot *nowp;
    double x1,y1;

    if(is_psplot_plane_err("cont")) return;            /* already open? */
    nowp = PSplot_win[PSplot_plane_no];


    x1 = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y1 = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

    
    nowp->dcpx = x;
    nowp->dcpy = y;


    x1 = x1 + GX;
    y1 = y1 + GY;


    fprintf(nowp->fp,"N %5.1f %5.1f MT  %5.1f %5.1f LT ST\n",
		     x1-PEKE_DOT,y1-PEKE_DOT,x1+PEKE_DOT,y1+PEKE_DOT);

    fprintf(nowp->fp,"N %5.1f %5.1f MT  %5.1f %5.1f LT ST\n",
		     x1+PEKE_DOT,y1-PEKE_DOT,x1-PEKE_DOT,y1+PEKE_DOT);
    return;
}

