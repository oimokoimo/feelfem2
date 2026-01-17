/*
 *    screen 
 */
#include "xplot.h"

screen( scr_no )
     int scr_no;
{
    Xplot *nowp;

    if(Xplot_PostScript == YES) {
	screen_ps(scr_no);
    }
    if(Xplot_X11 == NO) {
	return;
    }
    
    if(scr_no < 0 || scr_no > MAX_WINDOWS ) {
	fprintf(stderr,"screen no error no=%d\n",scr_no);
	return;
    }

    if(Xplot_win[scr_no] == NULL) {
	fprintf(stderr,"screen %d is not opened.\n",scr_no);
	return;
    }

    Xplot_plane_no = scr_no;

    return;
}

