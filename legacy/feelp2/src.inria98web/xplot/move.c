/*
 *  move,fmove        xplot routine
 *
 *  move current points
 *
 */

#include "xplot.h"

move(x,y)
     int x,y;
{
    Xplot *nowp;

    if(Xplot_PostScript == YES) {
	move_ps(x,y);
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("move")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];

    nowp->cpx = x;
    nowp->cpy = y;

    return;
}


fmove(x,y)
     double x,y;
{
    Xplot *nowp;

    if(Xplot_PostScript == YES) {
	fmove_ps(x,y);
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("fmove")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];

    nowp->dcpx = x;
    nowp->dcpy = y;

    return;

}
