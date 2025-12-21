/*
 * space,fspace   xplot routine
 *
 */

#include "xplot.h"

space(x1,y1,x2,y2)
     int x1,y1;
     int x2,y2;
{
    Xplot *nowp;
    int   dx,dy;

    if(Xplot_PostScript == YES) {
	space_ps(x1,y1,x2,y2);
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("space")) return;            /* already open? */
    
    nowp = Xplot_win[Xplot_plane_no];

    dx = x2 - x1;
    dy = y2 - y1;

    if(dx <= 0 || dy <= 0) {                           /* parameter error */
	xplot_error("space range error");
	return;
    }


    if(dx * nowp->ylen > dy * nowp->xlen) {            /* size ajust */
	dy = dx * nowp->ylen / nowp->xlen;
    }
    else if( dx * nowp->ylen < dy * nowp->xlen) {
	dx = dy * nowp->xlen/ nowp->ylen;
    }

    nowp->spdx = dx;
    nowp->spdy = dy;
    nowp->spx0 = x1;
    nowp->spy0 = y1;
    nowp->dspdx = (double)dx;
    nowp->dspdy = (double)dy;
    nowp->dspx0 = (double)x1;
    nowp->dspy0 = (double)y1;

    return;

}


fspace(x1,y1,x2,y2)
     double x1,y1,x2,y2;
{
    Xplot *nowp;
    double dx,dy;

    if(Xplot_PostScript == YES) {
	fspace_ps(x1,y1,x2,y2);
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("fspace")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];

    dx = x2 - x1;
    dy = y2 - y1;

    if(dx <= 0.0 || dy <= 0.0) {
	xplot_error("fspace range error");
	return;
    }
    if(dx * (double)nowp->ylen > dy * (double)nowp->xlen) {
	dy = dx * (double)nowp->ylen / (double)nowp->xlen;
    }
    else if( dx * (double)nowp->ylen < (double) dy * nowp->xlen) {
	dx = dy * (double)nowp->xlen / (double)nowp->ylen;
    }
    
    nowp->dspdx = dx;             /* double part of translation parameter */
    nowp->dspdy = dy;
    nowp->dspx0 = x1;
    nowp->dspy0 = y1;
                          
                  
    return;
}




