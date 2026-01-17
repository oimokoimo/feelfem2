/*
 *  cont,fcont        psplot routine
 *
 *  draw line from current point to the specified point
 *
 */

#include <stdio.h>
#include "psplot.h"

cont_ps(x,y)
     int x,y;
{
    PSplot *nowp;
    double x1,x2,y1,y2;

    if(is_psplot_plane_err("cont")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];



    x1 = ( x  - nowp->spx0) * nowp->xlen / nowp->spdx;
    x2 = (nowp->cpx - nowp->spx0) * nowp->xlen / nowp->spdx;
    y1 = ( y  - nowp->spy0) * nowp->ylen / nowp->spdy;
    y2 = (nowp->cpy - nowp->spy0) * nowp->ylen / nowp->spdy;
    
    nowp->cpx = x;
    nowp->cpy = y;
    
/*    
    y1 = nowp->ylen - y1;
    y2 = nowp->ylen - y2;
*/

    x1 = x1 + GX;
    x2 = x2 + GX;
    y1 = y1 + GY;
    y2 = y2 + GY;

    fprintf(nowp->fp,"N %5.1f %5.1f MT  %5.1f %5.1f LT ST\n",x1,y1,x2,y2);
    
    return;
}


fcont_ps(x,y)
     double x,y;
{
    PSplot *nowp;
    double x1,x2,y1,y2;

    if(is_psplot_plane_err("cont")) return;            /* already open? */
    nowp = PSplot_win[PSplot_plane_no];


    x1 = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y1 = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

    x2 = (nowp->dcpx - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y2 = (nowp->dcpy - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
    
    nowp->dcpx = x;
    nowp->dcpy = y;

/*    
    y1 = nowp->ylen - y1;
    y2 = nowp->ylen - y2;
*/

    x1 = x1 + GX;
    x2 = x2 + GX;
    y1 = y1 + GY;
    y2 = y2 + GY;

    fprintf(nowp->fp,"%5.1f %5.1f MT  %5.1f %5.1f LT ST\n",x1,y1,x2,y2);

    return;
}

fcont_abs_ps(ix,iy)
     int ix,iy;
{
    PSplot *nowp;
    double x,y;
    double x1,x2,y1,y2;

    if(is_psplot_plane_err("fcont")) return;        /* already open? */
    nowp = PSplot_win[PSplot_plane_no];

    x  = nowp->dcpx + (double)ix * nowp->dspdx / (double)nowp->xlen;
    y  = nowp->dcpy + (double)iy * nowp->dspdy / (double)nowp->ylen;

    x1 = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y1 = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

    x2 = (nowp->dcpx - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y2 = (nowp->dcpy - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
    
    nowp->dcpx = x;
    nowp->dcpy = y;

/*    
    y1 = nowp->ylen - y1;
    y2 = nowp->ylen - y2;
*/

    x1 = x1 + GX;
    x2 = x2 + GX;
    y1 = y1 + GY;
    y2 = y2 + GY;

    fprintf(nowp->fp,"%5.1f %5.1f MT  %5.1f %5.1f LT ST\n",x1,y1,x2,y2);

    return;
}

