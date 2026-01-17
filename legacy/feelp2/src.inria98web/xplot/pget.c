/*
 * pget,fpget    xplot routines
 *
 *  reads the point cordinate with mouse in the window
 *
 */

#include "xplot.h"

int pget(x,y)                               /* get the cordinate when button
                                               pressed. */
     int *x,*y;
{
    int           rx,ry,wx,wy;
    unsigned int          key;
    Window              wr,wc;
    XEvent              event;
    Xplot               *nowp;
    

    if(is_xplot_plane_err("pget")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];
    

    XSelectInput(nowp->dpy,nowp->win,ButtonPressMask);

    while(1) {
	XNextEvent(nowp->dpy,&event);
	switch(event.xany.type) {
	  case ButtonPress:
	    XQueryPointer(nowp->dpy,nowp->win,&wr,&wc,&rx,&ry,&wx,&wy,&key);
	    *x = wx * nowp->spdx / nowp->xlen + nowp->spx0;
	    *y = (nowp->ylen - wy) * nowp->spdy / nowp->ylen + nowp->spy0;
	    return(key);
	    
	  default:
	    break;
	}
    }
}


int fpget(x,y)                               /* get the cordinate when button
                                                pressed. */
     double *x,*y;
{
    int rx,ry,wx,wy;
    unsigned int key;
    Window    wr,wc;
    XEvent    event;
    Xplot *nowp;

    if(is_xplot_plane_err("fpget")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];

    XSelectInput(nowp->dpy,nowp->win,ButtonPressMask);

    while(1) {
	XNextEvent(nowp->dpy,&event);
	switch(event.xany.type) {
	  case ButtonPress:
	    XQueryPointer(nowp->dpy,nowp->win,&wr,&wc,&rx,&ry,&wx,&wy,&key);
	    *x = wx * nowp->dspdx / (double)nowp->xlen + nowp->dspx0;
	    *y = ((double)nowp->ylen-wy)*nowp->dspdy/(double)nowp->ylen +
	      nowp->dspy0;
	    return(key);

	  default:
	    break;
	}
    }
}



/* FORTRAN INTERFACE */

int pget_( x , y )
     int *x,*y;
{
    return(pget( x , y ));
}


int fpget_( x , y )
     double *x,*y;
{
    return(fpget( x , y ));
}

