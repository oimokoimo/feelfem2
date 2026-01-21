/*
 *  closepl,closeplv     xplot routine
 *
 *  close the window
 *
 */

#include "xplot.h"


closepl()   /* Destroy window after mouse click */
{
    Xplot *nowp;
    XEvent event;

    if(Xplot_PostScript == YES) {
	closepl_ps();
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("closepl")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];

    XSelectInput(nowp->dpy,nowp->win,ExposureMask | ButtonPressMask);

    while(1) {
	XNextEvent(nowp->dpy,&event);    /* wait button press before break 
					    the window                     */
	switch(event.xany.type)
	  {
	    case Expose:
	      xplot_expose_redraw();
	      break;

	    case ButtonPress:
	      if(nowp->FONTcomeyet) {
		  XFreeFont(nowp->dpy,nowp->font);
	      }
	      XFreeGC(nowp->dpy,nowp->gc);
	      XDestroyWindow(nowp->dpy,nowp->win);
	      XCloseDisplay(nowp->dpy);

	      free(nowp);
	      Xplot_win[Xplot_plane_no] = NULL;

	      return;
	      break;

	    default:
	      break;
	  }
    }
}



closeplv(n)
     int n;
{
    Xplot *nowp;


    if(Xplot_PostScript == YES) {
	closeplv_ps(n);
    }
    if(Xplot_X11 == NO) {
	return;
    }

    if(is_xplot_plane_err("closeplv")) return;            /* already open? */

    nowp = Xplot_win[Xplot_plane_no];


    if(nowp->FONTcomeyet) {
	XFreeFont(nowp->dpy,nowp->font);
    }
    XFreeGC(nowp->dpy,nowp->gc);
    XDestroyWindow(nowp->dpy,nowp->win);
    XCloseDisplay(nowp->dpy);

    free(nowp);
    Xplot_win[Xplot_plane_no] = NULL;

    return;

}


