/*
 * plot_get_csize.c
 *
 * Modified 1996/11/12
 *
 */
#include "xplot.h"

int plot_get_csize()
{
    if(Xplot_PostScript == YES) {
	return(plot_get_csize_ps());
    }

    return(Xplot_font_size);
}

