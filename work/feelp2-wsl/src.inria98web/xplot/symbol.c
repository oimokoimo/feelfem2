/*
 *  symbol.c    xplot routine
 * 
 *  Made 1992/09/08
 */

#include "xplot.h"

symbol(x,y,s)
     int x,y;
     char *s;
{
    Xplot *nowp;
    int x1,y1;

    if(Xplot_PostScript == YES) {
	symbol_ps(x,y,s);
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("symbol")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];

    x1 = ( x  - nowp->spx0) * nowp->xlen / nowp->spdx;
    y1 = ( y  - nowp->spy0) * nowp->ylen / nowp->spdy;

    y1 = nowp->ylen - y1;

    if(nowp->FONTcomeyet == NO) {
	nowp->FONTcomeyet = YES;
	nowp->font = XLoadFont( nowp->dpy,DEFAULT_FONT );
	XSetFont(nowp->dpy,nowp->gc,nowp->font);
    }

    XDrawString(nowp->dpy,nowp->win,nowp->gc,x1,y1,s,strlen(s));

    XFlush(nowp->dpy);

    return;
}

	

fsymbol(x,y,s)
     double x,y;
     char *s;
{
    Xplot *nowp;
    int x1,y1;


    if(Xplot_PostScript == YES) {
	fsymbol_ps(x,y,s);
    }
    if(Xplot_X11 == NO) {
	return;
    }
    if(is_xplot_plane_err("symbol")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];

    x1 = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y1 = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

    y1 = nowp->ylen - y1;


    if(nowp->FONTcomeyet == NO) {
	nowp->FONTcomeyet = YES;
	nowp->font = XLoadFont( nowp->dpy,DEFAULT_FONT );
	XSetFont(nowp->dpy,nowp->gc,nowp->font);
    }

    XDrawString(nowp->dpy,nowp->win,nowp->gc,x1,y1,s,strlen(s));

    XFlush(nowp->dpy);

    return;
}

	
symbol_(x,y,s)
     int *x,*y;
     char *s;
{
    symbol(*x,*y,s);

    return;
}


fsymbol_(x,y,s)
     double *x,*y;
     char *s;
{
    fsymbol(*x,*y,s);

    return;
}

