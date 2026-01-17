/*
 *  symbol,fsymbol        psplot routine
 *
 *  draw string
 *
 */

#include <stdio.h>
#include "psplot.h"


ps_symbol_convert(fp,s)
  FILE *fp;
  char *s;
{
   while(*s) {
      switch(*s) {
	case '(':
	case ')':
	case '\\':
	   fprintf(fp,"\\%c",*s);
	   break;
        default:
	   fprintf(fp,"%c",*s);
           break;
       }
       s++;
    }
    return;
}
symbol_ps(x,y,s)
     int x,y;
     char *s;
{
    PSplot *nowp;
    double x1,y1;

    if(is_psplot_plane_err("cont")) return;            /* already open? */

    nowp = PSplot_win[PSplot_plane_no];


    x1 = ( x  - nowp->spx0) * nowp->xlen / nowp->spdx;
    y1 = ( y  - nowp->spy0) * nowp->ylen / nowp->spdy;
    
    nowp->cpx = x;
    nowp->cpy = y;

/*    
    y1 = nowp->ylen - y1;
    y2 = nowp->ylen - y2;
*/

    x1 = x1 + GX;
    y1 = y1 + GY;

    fprintf(nowp->fp,"N %5.1f %5.1f MT (",x1,y1);
    ps_symbol_convert(nowp->fp,s);
    fprintf(nowp->fp,") show\n");
    
    return;
}


fsymbol_ps(x,y,s)
     double x,y;
     char *s;
{
    PSplot *nowp;
    double x1,y1;

    if(is_psplot_plane_err("fsymbol")) return;            /* already open? */
    nowp = PSplot_win[PSplot_plane_no];


    x1 = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    y1 = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

    nowp->dcpx = x;
    nowp->dcpy = y;

/*    
    y1 = nowp->ylen - y1;
    y2 = nowp->ylen - y2;
*/

    x1 = x1 + GX;
    y1 = y1 + GY;

    fprintf(nowp->fp,"%5.1f %5.1f MT (",x1,y1);
    ps_symbol_convert(nowp->fp,s);
    fprintf(nowp->fp,") show\n");

    return;
}

