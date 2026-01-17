/*
 *  ps_linewidth.c
 */

#include <stdio.h>
#include "psplot.h"

linewidth_ps(n)
     int n;
{
    PSplot *nowp;
    double dn;

    if(is_psplot_plane_err("linewidth")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];

    if(n == PSplot_linewidth) return;

    dn = (double)n / 10.0;
    fprintf(nowp->fp,"%4.1lf setlinewidth\n",dn);

    PSplot_linewidth = n;
    
    return;
}


