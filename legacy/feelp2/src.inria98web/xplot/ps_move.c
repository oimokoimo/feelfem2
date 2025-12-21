/*
 *  move,fmove        xplot routine
 *
 *  move current points
 *
 */

#include "psplot.h"

move_ps(x,y)
     int x,y;
{
    PSplot *nowp;

    if(is_psplot_plane_err("move")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];

    nowp->cpx = x;
    nowp->cpy = y;

    return;
}


fmove_ps(x,y)
     double x,y;
{
    PSplot *nowp;

    if(is_psplot_plane_err("fmove")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];

    nowp->dcpx = x;
    nowp->dcpy = y;

    return;

}
