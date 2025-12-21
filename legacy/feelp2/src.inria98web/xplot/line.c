/*
 *  line,fline        xplot routine
 *
 *  draw line
 *
 */

#include "xplot.h"

line(x1,y1,x2,y2)
     int x1,y1,x2,y2;
{
    move(x1,y1);
    cont(x2,y2);
    return;
}


fline(x1,y1,x2,y2)
     double x1,y1,x2,y2;
{
    fmove(x1,y1);
    fcont(x2,y2);
    return;
}


/* FORTRAN INTERFACE */

line_(x,y,z,w)
     int *x,*y,*z,*w;
{
    line(*x,*y,*z,*w);
    return;
}


fline_(x,y,z,w)
     double *x,*y,*z,*w;
{
    fline(*x,*y,*z,*w);
    return;
}


