/*
 *   setgray PostScript
 */

#include "psplot.h"
static int CMODE = 0;

ps_setgrayblack()
{
    PSplot *nowp;
    nowp = PSplot_win[PSplot_plane_no];
    fprintf(nowp->fp,"%6.2f SG\n",0.0);
}
 
ps_setgray(scale)
    double scale;
{
    PSplot *nowp;

    if(CMODE) { ps_rgbcolor(scale); return; }

    if(is_psplot_plane_err("setgray")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];

    fprintf(nowp->fp,"%6.2f SG\n",scale);

    return;
}

pscoloron_()  { CMODE = 1; }
pscoloroff_() { CMODE = 0; ps_setgray(0.0); }
