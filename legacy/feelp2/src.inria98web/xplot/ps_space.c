/*
 * space,fspace   psplot routine
 *
 */

#include "psplot.h"

space_ps(x1,y1,x2,y2)
     int x1,y1;
     int x2,y2;
{
    PSplot *nowp;
    int   dx,dy;

    if(is_psplot_plane_err("space")) return;            /* already open? */
    
    nowp = PSplot_win[PSplot_plane_no];

    dx = x2 - x1;
    dy = y2 - y1;

    if(dx <= 0 || dy <= 0) {                           /* parameter error */
	psplot_error("space range error");
	return;
    }


    if(dx * YDOT > dy * XDOT) {            /* size ajust */
	dy = dx * YDOT / XDOT;
    }
    else if( dx * YDOT < dy * XDOT) {
	dx = dy * XDOT / YDOT;
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


fspace_ps(x1,y1,x2,y2)
     double x1,y1,x2,y2;
{
    PSplot *nowp;
    double dx,dy;

    if(is_psplot_plane_err("fspace")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];

    dx = x2 - x1;
    dy = y2 - y1;

    if(dx <= 0.0 || dy <= 0.0) {
	psplot_error("fspace range error");
	return;
    }

    if(dx * (double)YDOT > dy * (double)XDOT) {            /* size ajust */
	dy = dx * (double)YDOT / (double)XDOT;
    }
    else if( dx * (double)YDOT < dy * (double)XDOT) {
	dx = dy * (double)XDOT / (double)YDOT;
    }

    
    nowp->dspdx = dx;             /* double part of translation parameter */
    nowp->dspdy = dy;
    nowp->dspx0 = x1;
    nowp->dspy0 = y1;
                          
                  
    return;
}
