
#include "psplot.h"


int openplps(filename)
     char *filename;
{
    if(filename == NULL || streq("stdout",filename)) {
	Xplot_ps_fp = stdout;
    }
    else {
	Xplot_ps_fp = fopen(filename,"w");
	if(Xplot_ps_fp == NULL) {
	    fprintf(stderr,"Cannot open ps file '%s'\n",filename);
	    exit(1);
	}
    }
    Xplot_PostScript = YES;            /* Use flag */

    init_ps();

    return;
}


