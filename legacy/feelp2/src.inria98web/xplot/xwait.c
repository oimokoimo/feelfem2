/*
 * xwait   xplot routine
 *
 *
 */

#include "xplot.h"


xwait()
{
    XEvent event;
    Xplot  *nowp;

    if(Xplot_X11 == NO) {
      return;
    }


    if(is_xplot_plane_err("xwait")) return;            /* already open? */
    nowp = Xplot_win[Xplot_plane_no];


    XSelectInput(nowp->dpy,nowp->win, ExposureMask | ButtonPressMask );

    while(1) {
	XNextEvent(nowp->dpy,&event);

	switch(event.type) 
	  {
	    
	    case Expose:
	      xplot_expose_redraw();
	      break;

	    case ButtonPress:
	      return;
	      
	    default:
	      break;
	  }

    }

}

/* FORTRAN INTERFACE */
xwait_()
{
    xwait();
    return;
}
