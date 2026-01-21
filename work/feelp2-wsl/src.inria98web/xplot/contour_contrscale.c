/*
 *  
 *  contour_contrscale.c
 *
 *  Modified 1996/11/12  yoko gaki  
 *
 *  contrscale  is vertical contour scale map
 *  contrscale2 is horizontal contour scale map
 */
#include <stdio.h>
#include "contr.h"

static double get_text_height( n )
    int n;
{
    double x,y;
    logical2pixel(n,n,&x,&y);
    return(x);
}

void contrscale(x,y,xlen,ylen,max,val)
    double  x,y;           /* draw scale base point    */
    int     xlen,ylen;     /* scale tile size          */
    int     max;           /* number of bars (=tiles-1)*/
    double *val;           /* bar value                */
{
    int     i,j;
    double  dx,dy;
    double  xx[4],yy[4];
    double  xxx,yyy;
    char    str[BUFSIZ];

    logical2pixel(xlen,ylen,&dx,&dy);

    for(i=0;i<=max;i++) {

	xx[0] = x ;
	yy[0] = y + dy*(double)i;
	xx[1] = x + dx;
	yy[1] = y + dy*(double)i;
	xx[2] = x + dx;
	yy[2] = y + dy*(double)(i+1);
	xx[3] = x;
	yy[3] = y + dy*(double)(i+1);

	contr_setgray(i);
	fpolygon(4,xx,yy);

        setgrayblack();
	fmove(xx[3],yy[3]);
	for(j=0;j<4;j++) {
	    fcont(xx[j],yy[j]);
	}
    }

    /* draw var value */
    for(i=0;i<max;i++) {
	xxx = x + dx *1.2;
	yyy = y + dy*(double)(i+1);
	sprintf(str,"%5.1lf",*(val+i));
	fsymbol(xxx,yyy,str);
    }
	

    return;
}

contrscale2(x,y,xlen,ylen,max,val)
    double  x,y;           /* draw scale base point    */
    int     xlen,ylen;     /* scale tile size          */
    int     max;           /* number of bars (=tiles-1)*/
    double *val;           /* bar value                */
{
    int     i,j;
    double  dx,dy;
    double  xx[4],yy[4];
    double  xxx,yyy;
    double  tlen;             /* text height */
    char    str[BUFSIZ];

    logical2pixel(xlen,ylen,&dx,&dy);

    for(i=0;i<=max;i++) {

	xx[0] = x + dx*(double)i;
	yy[0] = y ;
	xx[1] = x + dx*(double)(i+1);
	yy[1] = y ;
	xx[2] = x + dx*(double)(i+1);
	yy[2] = y + dy;
	xx[3] = x + dx*(double)i;
	yy[3] = y + dy;

	contr_setgray(i);
	fpolygon(4,xx,yy);

	setgrayblack();
	fmove(xx[3],yy[3]);
	for(j=0;j<4;j++) {
	    fcont(xx[j],yy[j]);
	}
    }

    /* draw var value */

    tlen = (double)get_text_height(plot_get_csize());
    for(i=0;i<max;i++) {
	xxx = x + dx*(double)(i+1)- tlen*2;
	yyy = y - tlen*1.2;
	sprintf(str,"%5.1lf",*(val+i));
	fsymbol(xxx,yyy,str);
    }
	

    return;
}
contrscale2f(x,y,xlen,ylen,max,val,fmt,len,itype)
    double  x,y;           /* draw scale base point    */
    int     xlen,ylen;     /* scale tile size          */
    int     max;           /* number of bars (=tiles-1)*/
    double *val;           /* bar value                */
    char   *fmt;           /* format in C expression   */
    int     len;           /* length of number         */
    int     itype;         /* if 0 INTEGER, if 1 REAL  */
{
    int     i,j;
    int     ival;             /* for conversion use */
    double  dx,dy;
    double  xx[4],yy[4];
    double  xxx,yyy;
    double  tlen;             /* text height */
    char    str[BUFSIZ];

    logical2pixel(xlen,ylen,&dx,&dy);

    for(i=0;i<=max;i++) {

	xx[0] = x + dx*(double)i;
	yy[0] = y ;
	xx[1] = x + dx*(double)(i+1);
	yy[1] = y ;
	xx[2] = x + dx*(double)(i+1);
	yy[2] = y + dy;
	xx[3] = x + dx*(double)i;
	yy[3] = y + dy;

	contr_setgray(i);
	fpolygon(4,xx,yy);

	setgrayblack();
	fmove(xx[3],yy[3]);
	for(j=0;j<4;j++) {
	    fcont(xx[j],yy[j]);
	}
    }

    /* draw var value */

    /* get_text_height is the routine in this source file */
    tlen = get_text_height(plot_get_csize());

    for(i=0;i<max;i++) {
	xxx = x + dx*(double)(i+1)- tlen*(len-1)/2.0;
	yyy = y - tlen*1.5;

	if(itype == 0) {
	  ival = *(val+i);
	  sprintf(str,fmt,ival);
        }
	else {
	  sprintf(str,fmt,*(val+i));
        }

	fsymbol(xxx,yyy,str);
    }
	

    return;
}

void contrscale_(x,y,xlen,ylen,max,val)
    double *x,*y;
    int *xlen,*ylen;
    int *max;
    double *val;
{
    contrscale(*x,*y,*xlen,*ylen,*max,val);
    return;
}
void contrscale2_(x,y,xlen,ylen,max,val)
    double *x,*y;
    int *xlen,*ylen;
    int *max;
    double *val;
{
    contrscale2(*x,*y,*xlen,*ylen,*max,val);
    return;
}
void contrscale2f_(x,y,xlen,ylen,max,val,fmt,len,itype)
    double *x,*y;
    int *xlen,*ylen;
    int *max;
    double *val;
    char *fmt;
    int *len;
    int *itype;
{
    contrscale2f(*x,*y,*xlen,*ylen,*max,val,fmt,*len,*itype);
    return;
}
