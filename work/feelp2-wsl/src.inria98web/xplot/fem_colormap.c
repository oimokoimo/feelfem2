/* 
 *   fem_colormap.c
 */

#include "xplot.h"

#define START_PIXEL 80

static Colormap cm_fem;
static double   min,max;
static double   dt;
static int      grade_range;


fem_colormap_init( grade , dmin, dmax)
     int grade;
     double dmin,dmax;
{
    raw_make_fem_colormap(grade);

    grade_range = grade;
    min = dmin;
    max = dmax;
    dt  = dmax - dmin;

    return;
}

raw_make_fem_colormap(grade)
     int grade;
{
    Xplot *nowp;
    XColor color;

    int i;

    nowp = Xplot_win[Xplot_plane_no];

    cm_fem = XCreateColormap(nowp->dpy,nowp->win,DefaultVisual(nowp->dpy,0),
			     AllocAll);

    for(i=0;i<grade;i++) {
	
	color.pixel = i + START_PIXEL;
	color.red   = (long)65535L*(long)i/grade;
	color.green = (long)0L;
	color.blue  = 65535L-65535L*(long)i/grade;
	color.flags = DoRed | DoGreen | DoBlue ;
	XStoreColor( nowp->dpy , cm_fem, &color);
    }
    return;
}

fem_contour_loop()
{
    XEvent e;
    Xplot *nowp;
    int flag;

    nowp = Xplot_win[Xplot_plane_no];

    flag = 1;
    
    XSelectInput(nowp->dpy,nowp->win, ButtonPressMask );

    while(1) {
	XNextEvent(nowp->dpy, &e);
	switch(e.xbutton.button) {
	      case Button1 :
		flag = flag * -1;
		if(flag == -1) {
		    XInstallColormap(nowp->dpy,cm_fem);
		}
		else {
		    XUninstallColormap(nowp->dpy,cm_fem);
		}
		break;

	      case Button3:
		return;
	      default:
		break;
	    }
      }

}

fem_raw_point(x,y,d)
     int x,y;
     double d;
{
    int grade;

    grade = (d - min )/dt * grade_range + START_PIXEL;

    raw_foreground( grade );
    raw_point(x,y);

    return;
}

fem_draw_contour_triangle(x1,y1,x2,y2,x3,y3,d1,d2,d3)
     double x1,y1,x2,y2,x3,y3;
     double d1,d2,d3;
{
    int xx1,yy1,xx2,yy2,xx3,yy3;
    
    Xplot *nowp;

    nowp = Xplot_win[Xplot_plane_no];

    xx1 = ( x1  - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    yy1 = ( y1  - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
    xx2 = ( x2  - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    yy2 = ( y2  - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
    xx3 = ( x3  - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
    yy3 = ( y3  - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

    fem_triangle_dot_plane(xx1,yy1,xx2,yy2,xx3,yy3,d1,d2,d3);

    return;
}

femcontour_(x1,y1,x2,y2,x3,y3,d1,d2,d3)
     double *x1,*y1,*x2,*y2,*x3,*y3,*d1,*d2,*d3;
{

    fem_draw_contour_triangle(*x1,*y1,*x2,*y2,*x3,*y3,*d1,*d2,*d3);
    return;
}

femcontourinit_(grade,dmin,dmax)
     int *grade;
     double *dmin,*dmax;
{
    fem_colormap_init( *grade , *dmin, *dmax);
}

showcontour_()
{
    fem_contour_loop();
}
