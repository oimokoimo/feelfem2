#include "psplot.h"


int openplps(filename)
     char *filename;
{
    openplvps( 0 , filename );
    return;
}


int openplvps( scr_no, filename)
     int scr_no;
     char *filename;
{
    
    if(scr_no <0 || scr_no >= MAX_PS_FILES) {
	fprintf(stderr,"screen no error(openplvps)\n");
	exit(1);
    }

    PSplot_win[scr_no] = (PSplot *)malloc(sizeof(PSplot));
    if(PSplot_win[scr_no] == NULL) {
	fprintf(stderr,"cannot allocate PSplot structure.\n");
	exit(1);
    }



    if(filename == NULL || streq("stdout",filename)) {
	PSplot_win[scr_no]->fp = stdout;
    }
    else {
	PSplot_win[scr_no]->fp = fopen(filename,"w");
	if(PSplot_win[scr_no]->fp == NULL) {
	    fprintf(stderr,"Cannot open ps file '%s'\n",filename);
	    exit(1);
	}
    }

    Xplot_PostScript = YES;            /* Use flag */
    PSplot_plane_no = scr_no;

    PSplot_win[scr_no] -> xlen = XDOT;
    PSplot_win[scr_no] -> ylen = YDOT;
    
    PSplot_win[scr_no] -> spx0 = 0;
    PSplot_win[scr_no] -> spy0 = 0;
    PSplot_win[scr_no] -> spdx = XDOT;
    PSplot_win[scr_no] -> spdy = YDOT;
    PSplot_win[scr_no] -> dspx0 = 0.0;
    PSplot_win[scr_no] -> dspy0 = 0.0;
    PSplot_win[scr_no] -> dspdx = (double)XDOT;
    PSplot_win[scr_no] -> dspdy = (double)YDOT;

    init_ps();

    return;
}




