/*
 *  ps_fontsize.c
 */

#include <stdio.h>
#include "psplot.h"

fontsize_ps(n)
     int n;
{
    int i;
    PSplot *nowp;
    double dn;

    if(is_psplot_plane_err("fontsize_ps")) return;     /* already open? */

    nowp = PSplot_win[PSplot_plane_no];

    if(n <1 ) {
       fprintf(stderr,"Illegal font size for PostScript(fontsize)\n");
       return;
    }

    if(n == PSplot_font_size[PSplot_font_ptr]) return;

    for(i=0;i<MAX_PS_FONTS;i++) {
      if(n == PSplot_font_size[i]) {
	PSplot_font_ptr = i;
	fprintf(nowp->fp,"Font0%d setfont\n",i);
	return;
      }
    }
    if(PSplot_fonts == MAX_PS_FONTS) {
      fprintf(stderr,"No more font definition space\n");
      return;
    }
    PSplot_font_size[PSplot_fonts] = n;
    PSplot_font_ptr = PSplot_fonts;
    fprintf(nowp->fp,"/Font0%d %s findfont %d scalefont def\n",
	    PSplot_fonts,PSplot_font_name, n);
    fprintf(nowp->fp,"Font0%d setfont\n",PSplot_fonts);
   
    PSplot_fonts++;
    return;
}


