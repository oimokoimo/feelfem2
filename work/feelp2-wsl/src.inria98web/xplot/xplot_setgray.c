/*
 *    xplot_setgray.c
 */

#include "xplot.h"

void setgray( n )
int n;
{

  double scale;
  static int current = 0;
  char buf[10];
  
  if(n < 0 || n > 100) {
    fprintf(stderr,"Error setgray argument must be between 0 to 100\n");
    return;
  }
  
  if(current == n) return;

  current = n;
  
  if(Xplot_PostScript == YES) {
    scale = (double)n / 100.0;
    ps_setgray(scale);
  }
  if(Xplot_X11 == NO) {
    return;
  }
  sprintf(buf,"gray%d",n);
  xcolor(buf);

  return;
}
  

void setgrayblack()
{
  if(Xplot_X11 == YES) {
     fprintf(stderr,"setgrayblack is for PostScript now... \n");
     return;
  } 
  ps_setgrayblack();
}

void setgray_( n )
  int *n;
{
   setgray(*n);
   return;
}
