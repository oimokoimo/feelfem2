/*
 *    screen (ps)
 */
#include "psplot.h"

screen_ps( scr_no )
     int scr_no;
{
    
    if(scr_no < 0 || scr_no > MAX_PS_FILES ) {
	fprintf(stderr,"File no error no=%d\n",scr_no);
	return;
    }

    if(PSplot_win[scr_no] == NULL) {
	fprintf(stderr,"PostScript file No.%d is not opened.\n",scr_no);
	return;
    }

    PSplot_plane_no = scr_no;

    return;
}

