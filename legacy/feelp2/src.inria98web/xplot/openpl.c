/*
 *  openpl --- Xplot routines
 *
 */
#include <stdio.h>

#include "xplot.h"


int openpl()
{
    int ret;

    ret = openplv(0);

    return ret;
}

int openplv( no )
     int no;
{
    Xplot *nowp;
    XEvent event;
    int x,y,root,xlen,ylen,bw,depth;

    char window_name[BUFSIZ];

    Xplot_X11        = YES;            /* Use flag */

    if(no < 0 || no > MAX_WINDOWS) {
	xplot_error_d("Bad Window Number");
	return;
    }

    if( Xplot_win[no] != NULL) {
	xplot_error_d("Window %d already opened.",no);
	return;
    }

    Xplot_plane_no = no;
    Xplot_win[no]  = (Xplot *)malloc(sizeof (Xplot));
    nowp  = Xplot_win[no];


    nowp->dpy = XOpenDisplay(getenv("DISPLAY"));  /* Open display */
    if(nowp -> dpy == NULL) {
	xplot_error("Can't Open display %s",getenv("DISPLAY"));
	exit(1);
    }

    nowp->root   = XDefaultRootWindow(nowp->dpy);
    nowp->screen = XDefaultScreen(nowp->dpy);
    nowp->cmap   = XDefaultColormap(nowp->dpy,nowp->screen);

    nowp->fg     = xplot_mycolor(Xplot_fg_name);
    nowp->bg     = xplot_mycolor(Xplot_bg_name);

    nowp->win    = XCreateSimpleWindow(nowp->dpy,nowp->root,0,0,
				       Xplot_win_xlen,Xplot_win_ylen,
				       1,nowp->fg,nowp->bg);

    sprintf(window_name,"xplot    screen %d",no);
    XStoreName(nowp->dpy,nowp->win,window_name);

    XSelectInput(nowp->dpy,nowp->win,
		 ExposureMask |
		 ButtonPressMask |
		 ButtonReleaseMask |
		 Button1MotionMask );

#ifdef USE_BACKINGSTORE
    { XSetWindowAttributes att;
      att.backing_store = Always;
      XChangeWindowAttributes(nowp->dpy,nowp->win,CWBackingStore,&att);
    }
#endif
    
    nowp->gc = XCreateGC(nowp->dpy,nowp->win,0,NULL);
    XSetForeground(nowp->dpy,nowp->gc,nowp->fg);
    XSetBackground(nowp->dpy,nowp->gc,nowp->bg);

    XMapWindow(nowp->dpy,nowp->win);

    XNextEvent(nowp->dpy,&event);

    XGetGeometry(nowp->dpy,nowp->win,&root,&x,&y,&xlen,&ylen,&bw,&depth);
    
    nowp->root = root;      /* window manager may change the window size */
    nowp->xlen = xlen;
    nowp->ylen = ylen;


    nowp -> spx0 = 0;       /* default size if space or fspace not called */
    nowp -> spy0 = 0;
    nowp -> spdx = xlen;
    nowp -> spdy = ylen;

    nowp -> dspx0 = 0.0;
    nowp -> dspy0 = 0.0;
    nowp -> dspdx = (double) xlen;
    nowp -> dspdy = (double) ylen;

    nowp -> FONTcomeyet  = NO;

    return;
}
