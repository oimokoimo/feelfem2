/*
 *  X11 Window system
 *
 *  variable definitions
 */


#include "xplot.h"


int Xplot_plane_no = NONE;



Xplot *Xplot_win[MAX_WINDOWS] = {
    NULL,NULL,NULL,NULL,NULL,NULL,
    NULL,NULL,NULL,NULL,NULL };

int Xplot_win_xlen  = DEFAULT_XLEN;     /* default window size */
int Xplot_win_ylen  = DEFAULT_YLEN; 

char *Xplot_bg_name = DEFAULT_BG;
char *Xplot_fg_name = DEFAULT_FG;

/* FOR output flag */

int Xplot_PostScript = NO;
int Xplot_X11        = NO;

int Xplot_font_size      = FONT_SIZE;

FILE *Xplot_ps_fp;

void xplot_set_winsiz(xlen,ylen)
     int xlen,ylen;
{
  Xplot_win_xlen = xlen;
  Xplot_win_ylen = ylen;
  return;
}


