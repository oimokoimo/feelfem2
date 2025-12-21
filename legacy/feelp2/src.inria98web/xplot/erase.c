/*
 *  erase,erasev        xplot routine
 *
 *  erase the window
 */

#include "xplot.h"


erase() 
{
    
    if(is_xplot_plane_err("erase")) return;            /* already open? */

    erasev( Xplot_plane_no );

    return;
}

erasev( n )                          /* clear the window */
     int n;
{
    Xplot *nowp;

    if( n < 0 || n > MAX_WINDOWS) {
	xplot_error("erasev screen no error");
	return;
    }
    if( Xplot_win[n] == NULL ) {
	xplot_error("erasev specified screen is not opened.");
	return;
    }

    nowp = Xplot_win[Xplot_plane_no];
    
/*    nowp->redraw_ptr = 0;
      nowp->redraw[0]  = 0;
*/

    XClearWindow(nowp->dpy,nowp->win);
    return;

}

