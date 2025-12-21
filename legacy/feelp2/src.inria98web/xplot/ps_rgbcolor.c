/*
 *   rgbcolor PostScript
 */

#include "psplot.h"

ps_rgbcolor(scale)
    double scale;
{
    double r,g,b;
    PSplot *nowp;

    if(is_psplot_plane_err("rgbcolor")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];


    if(scale <0.25) {
      r = 0.0;
      g = 4.0*scale;
      b = 1.0;
    }
    else if(scale <0.5) {
      r = 0.0;
      g = 1.0;
      b = 1.0-4*(scale-0.25);
    }
    else if(scale <0.75) {
      r = 4*(scale-0.5);
      g = 1.0;
      b = 0.0;
    }
    else {
      r = 1.0;
      g = 1.0-4*(scale-0.75);
      b = 0.0;
    }

/*
    if(scale <0.5) {
      r = 0.0;
      g = 2* scale;
      b = 1.0 - 2*scale;
    }
    else {
      r = 2*(scale-0.5);
      g = 2*(1.0-scale);
      b = 0.0;
    }
*/
   /* 
    r    = scale;
    b    = 1.0-scale;
    if(scale <0.5) g = 2 * scale;
    else           g = 2 * (1.0-scale);
    */

    fprintf(nowp->fp,"%5.3f %5.3f %5.3f setrgbcolor\n",r,g,b);

    return;
}

psrgbcolor_( scale )
double *scale;
{
  ps_rgbcolor(*scale);
}
