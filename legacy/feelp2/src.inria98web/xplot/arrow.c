/*
 *  arrow,farrow        xplot routine
 *
 *  draw arrow
 *
 */

#include "xplot.h"

arrow(x1,y1,x2,y2)
     int x1,y1,x2,y2;
{
    move(x1,y1);
    cont(x2,y2);
    fprintf(stderr,"arrow is not supported under current version\n");
    return;
}


farrow(x1,y1,x2,y2)
     double x1,y1,x2,y2;
{
    fmove(x1,y1);
    fcont(x2,y2);
    farrowhead(x1,y1,x2,y2);
    return;
}


/* FORTRAN INTERFACE */

arrow_(x,y,z,w)
     int *x,*y,*z,*w;
{
    arrow(*x,*y,*z,*w);
    return;
}


farrow_(x,y,z,w)
     double *x,*y,*z,*w;
{
    farrow(*x,*y,*z,*w);
    return;
}


