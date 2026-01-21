/*
 * xwait   xplot routine
 *
 *
 */

#include "xplot.h"


plot_flush()
{
    XEvent event;
    Xplot  *nowp;

    if(Xplot_X11 == NO) {
      return;
    }


    if(is_xplot_plane_err("plot_flush")) return;            /* already open? */
    nowp = Xplot_win[Xplot_plane_no];

    XFlush(nowp->dpy);
    return;

}

/* FORTRAN INTERFACE */
plot_flush_()
{
    plot_flush();
    return;
}
