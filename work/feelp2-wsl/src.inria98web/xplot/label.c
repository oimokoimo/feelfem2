/*
 *  label.c
 */

#include "xplot.h"

label(s)
	char *s;
{
    Xplot *nowp;

    if(Xplot_PostScript == YES) {
/* 	label_ps(x,y);  */
fprintf(stderr,"label is not implemented for ps routine now\n");
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("label")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];

    symbol(nowp->cpx,nowp->cpy,s);

    return;
}



