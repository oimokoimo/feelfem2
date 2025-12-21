/************************************************************************/
/*                                                                      */
/* View ver 1.0 1994.5.17                                               */
/* viewplot.c                                                           */
/* Copy rights - all rights reserved by NEC                             */
/*                                                                      */
/************************************************************************/

#include "view.h"

#define	PLOT_FONT	"6x13"
#define	PLOT_FONT_SZX	6	
#define	PLOT_FONT_SZY	13	

void	ViewExtPlotAxis(xmin,xmax,ymin,ymax,nx,ny,npy,cid,id)
float	xmin,xmax,ymin,ymax;
int	nx,ny;
int	npy;
int	cid;
int	id;
{
	int	i,j,k;

	int	rw,rh;
	int	x0,x1,x2,x3;
	int	y0,y1,y2,y3;
	int	dx,dy;
	int	rr;
	int	gg;

	float	v;
	char	str[100];

	Display	*d;
	Window	w;
	GC	g;
	Font	f;

	int	nx1,nx2,nx3,ny1,ny2,ny3;
	char	val[100];

	d = viewdisp[id].disp;
	w = viewdisp[id].win;
	g = viewdisp[id].gc;

	rw = viewport[id].width;
	rh = viewport[id].height;

	dx = (int)(rw * 0.8);
	dy = (int)(rh * 0.8);
	x0 = (int)(rw * 0.1);
	y0 = (int)(rh * 0.1);
	x1 = x0 + dx;
	y1 = y0 + dy;

    	XSetForeground(d,g,viewcolor[id][cid].color[0].pixel);
	f = XLoadFont(d,PLOT_FONT);
	XSetFont(d,g,f);

	XSetLineAttributes(d,g,2,LineSolid,CapButt,JoinMiter);
	XDrawLine(d,w,g,x0,rh-y0,x1,rh-y0);
	XDrawLine(d,w,g,x1,rh-y0,x1,rh-y1);
	XDrawLine(d,w,g,x1,rh-y1,x0,rh-y1);
	XDrawLine(d,w,g,x0,rh-y1,x0,rh-y0);

	nx1 = 0; nx2 = 0;
	if (xmin != 0.0) nx1 = (int)log10(fabs((double)xmin));
	if (xmax != 0.0) nx2 = (int)log10(fabs((double)xmax));
	if (abs(nx1) > abs(nx2)) nx3 = nx1;
	else                     nx3 = nx2;
	if (nx3 >  0 && nx3 <=  3) sprintf(val,"%s","% .1f");
	if (nx3 > -2 && nx3 <=  0) sprintf(val,"%s","% .3f");
	if (nx3 >  3 || nx3 <= -2) sprintf(val,"%s","% .1e");

	for (i = 0;i < nx + 1;i ++) {
		v = (xmax - xmin) / nx * i + xmin;
		sprintf(str,val,v);
		x2 = (x1 - x0) / nx * i + x0 - strlen(str) * PLOT_FONT_SZX / 2;
		y2 = y0 - (PLOT_FONT_SZY + 5);
		XDrawString(d,w,g,x2,rh-y2,str,strlen(str));
	}

	ny1 = 0; ny2 = 0;
	if (ymin != 0.0) ny1 = (int)log10(fabs((double)ymin));
	if (ymax != 0.0) ny2 = (int)log10(fabs((double)ymax));
	if (abs(ny1) > abs(ny2)) ny3 = ny1;
	else                     ny3 = ny2;
	if (ny3 >   0 && ny3 <=  3) sprintf(val,"%s","% .1f");
	if (ny3 >  -2 && ny3 <=  0) sprintf(val,"%s","% .3f");
	if (ny3 >   3 || ny3 <= -2) sprintf(val,"%s","% .1e");
		
	for (i = 0;i < ny + 1;i ++) {
		v = (ymax - ymin) / ny * i + ymin;
		sprintf(str,val,v);
		switch(npy) {
		case	1:
		       x2 = x0 - (strlen(str) * PLOT_FONT_SZX + 5);
	               y2 = (y1 - y0) / ny * i + y0 - PLOT_FONT_SZY / 2;
	               XDrawString(d,w,g,x2,rh-y2,str,strlen(str));
		       break;
		case	2:
		       x2 = x1 + 5;
	               y2 = (y1 - y0) / ny * i + y0 - PLOT_FONT_SZY / 2;
	               XDrawString(d,w,g,x2,rh-y2,str,strlen(str));
		       break;
		}
	}

	XSetLineAttributes(d,g,1,LineSolid,CapButt,JoinMiter);
		
	if (rw > rh) rr = rh;
	else         rr = rw;
	gg = rr / 100;
	if (gg < 2) gg = 2;
	for (i = 0;i < nx + 1;i ++) {
		if (i == 0 || i == nx) continue;
		x2 = (x1 - x0) / nx * i + x0;
		y2 = y0 + gg;
		y3 = y1 - gg;
		XDrawLine(d,w,g,x2,rh-y0,x2,rh-y2);
		XDrawLine(d,w,g,x2,rh-y1,x2,rh-y3);
	}
	for (i = 0;i < ny + 1;i ++) {
		if (i == 0 || i == ny) continue;
		y2 = (y1 - y0) / ny * i + y0;
		switch(npy) {
		case	1:
			x2 = x0 + gg;
			XDrawLine(d,w,g,x0,rh-y2,x2,rh-y2);
			break;
		case	2:
			x3 = x1 - gg;
			XDrawLine(d,w,g,x1,rh-y2,x3,rh-y2);
			break;
		}
	}
}

int	ViewExtPlotClip(x1,x2,y1,y2,xmin,xmax,ymin,ymax)
int	*x1,*x2,*y1,*y2,xmin,xmax,ymin,ymax;
{
        float   fx[2],fy[2];
        int     px1,px2,py1,py2;
        int     fg;

        if (*x1 <= xmin && *x2 <= xmin) return( -1 );
        if (*x1 >= xmax && *x2 >= xmax) return( -1 );
        if (*y1 <= ymin && *y2 <= ymin) return( -1 );
        if (*y1 >= ymax && *y2 >= ymax) return( -1 );

        if (*x1 > xmin && *x1 < xmax &&
            *x2 > xmin && *x2 < xmax &&
            *y1 > ymin && *y1 < ymax &&
            *y2 > ymin && *y2 < ymax) return( 1 );

        if (*x1 < *x2) {
                px1 = *x1; px2 = *x2;
                py1 = *y1; py2 = *y2;
                fg = 1;
        }else{
                px1 = *x2; px2 = *x1;
                py1 = *y2; py2 = *y1;
                fg = -1;
        }

        fx[0] = (float)px1;
        fx[1] = (float)px2;
        fy[0] = (float)py1;
        fy[1] = (float)py2;

        if (px1 < xmin) {
                if (px2 > xmax) {
                        px1 = xmin;
                        py1 = ViewUtilLagrange((float)xmin,2,fx,fy);
                        px2 = xmax;
                        py2 = ViewUtilLagrange((float)xmax,2,fx,fy);
                }else{
                        px1 = xmin;
                        py1 = ViewUtilLagrange((float)xmin,2,fx,fy);
                }
        }
        else if (px1 < xmax) {
                if (px2 > xmax) {
                        px2 = xmax;
                        py2 = ViewUtilLagrange((float)xmax,2,fx,fy);
                }
        }else return( -1 );

        if (py1 < ymin) {
                if (py2 > ymax) {
                        px1 = ViewUtilLagrange((float)ymin,2,fy,fx);
                        py1 = ymin;
                        px2 = ViewUtilLagrange((float)ymax,2,fy,fx);
                        py2 = ymax;
                }else if (py2 > ymin) {
                        px1 = ViewUtilLagrange((float)ymin,2,fy,fx);
                        py1 = ymin;
                }else return( -1 );
        }else if (py1 < ymax) {
                if (py2 > ymax) {
                        px2 = ViewUtilLagrange((float)ymax,2,fy,fx);
                        py2 = ymax;
                }else if (py2 < ymin) {
                        px2 = ViewUtilLagrange((float)ymin,2,fy,fx);
                        py2 = ymin;
                }
        }else{
                if (py2 < ymin) {
                        px1 = ViewUtilLagrange((float)ymax,2,fy,fx);
                        py1 = ymax;
                        px2 = ViewUtilLagrange((float)ymin,2,fy,fx);
                        py2 = ymin;
                }else if (py2 < ymax) {
                        px1 = ViewUtilLagrange((float)ymax,2,fy,fx);
                        py1 = ymax;
                }else return( -1 );
        }

        if (fg > 0) {
                *x1 = px1; *x2 = px2;
                *y1 = py1; *y2 = py2;
        }else{
                *x1 = px2; *x2 = px1;
                *y1 = py2; *y2 = py1;
        }

        return( 1 );
}

void	ViewExtPlotLine(x,y,np,xmin,xmax,ymin,ymax,cid,id)
float	*x,*y;
float	xmin,xmax,ymin,ymax;
int	cid;
int	id;
{
	int	i,j,k;
	int	n;

	Display	*d;
	Window	w;
	GC	g;
	Font	f;

	int	rw,rh;
	int	x0,x1;
	int	y0,y1;
	int	dx,dy;
	int	px,py;
	int	qx,qy;

	float	fx,fy;

	d = viewdisp[id].disp;
	w = viewdisp[id].win;
	g = viewdisp[id].gc;

	rw = viewport[id].width;
	rh = viewport[id].height;

	dx = (int)(rw * 0.8);
	dy = (int)(rh * 0.8);
	x0 = (int)(rw * 0.1);
	y0 = (int)(rh * 0.1);
	x1 = x0 + dx;
	y1 = y0 + dy;

    	XSetForeground(d,g,viewcolor[id][cid].color[0].pixel);

	for (i = 0;i < np;i ++) {
		qx = (x[i] - xmin) / (xmax - xmin) * dx + x0;
		qy = (y[i] - ymin) / (ymax - ymin) * dy + y0;

		if (i == 0) {
			px = qx;
			py = qy;
		}else{
			px = (x[i-1] - xmin) / (xmax - xmin) * dx + x0;
			py = (y[i-1] - ymin) / (ymax - ymin) * dy + y0;
		}

		n = ViewExtPlotClip(&px,&qx,&py,&qy,x0,x1,y0,y1);
		if (n < 0) continue;
	
		XDrawLine(d,w,g,px,rh-py,qx,rh-qy);

		px = qx;
		py = qy;
	}
}

void	ViewExtPlotMarker(x,y,np,xmin,xmax,ymin,ymax,mid,cid,id)
float	*x,*y;
float	xmin,xmax,ymin,ymax;
int	mid;
int	cid;
int	id;
{
	int	i,j,k;
	int	n;

	Display	*d;
	Window	w;
	GC	g;
	Font	f;

	int	rw,rh;
	int	x0,x1;
	int	y0,y1;
	int	dx,dy;
	int	px,py;
	int	qx,qy;

	float	fx,fy;

	XPoint	dr[10];

	d = viewdisp[id].disp;
	w = viewdisp[id].win;
	g = viewdisp[id].gc;

	rw = viewport[id].width;
	rh = viewport[id].height;

	dx = (int)(rw * 0.8);
	dy = (int)(rh * 0.8);
	x0 = (int)(rw * 0.1);
	y0 = (int)(rh * 0.1);
	x1 = x0 + dx;
	y1 = y0 + dy;

    	XSetForeground(d,g,viewcolor[id][cid].color[0].pixel);

	for (i = 0;i < np;i ++) {
		qx = (x[i] - xmin) / (xmax - xmin) * dx + x0;
		qy = (y[i] - ymin) / (ymax - ymin) * dy + y0;
		px = qx;
		py = qy;
		n = ViewExtPlotClip(&px,&qx,&py,&qy,x0,x1,y0,y1);
		if (n < 0) continue;

		switch(mid) {
		case	1:
	                XDrawArc(d,w,g,qx-4,rh-(qy+4),8,8,0,360*64);
                	break;
		case	2:
			dr[0].x = qx + 4;
			dr[0].y = rh - (qy + 4);
			dr[1].x = qx - 4;
			dr[1].y = rh - (qy + 4);
			dr[2].x = qx - 4;
			dr[2].y = rh - (qy - 4);
			dr[3].x = qx + 4;
			dr[3].y = rh - (qy - 4);
			dr[4].x = qx + 4;
			dr[4].y = rh - (qy + 4);
			XDrawLines(d,w,g,dr,5,CoordModeOrigin);
                	break;
		case	3:
			dr[0].x = qx + 4;
			dr[0].y = rh - (qy - 4);
			dr[1].x = qx;
			dr[1].y = rh - (qy + 4);
			dr[2].x = qx - 4;
			dr[2].y = rh - (qy - 4);
			dr[3].x = qx + 4;
			dr[3].y = rh - (qy - 4);
			XDrawLines(d,w,g,dr,4,CoordModeOrigin);
                	break;
		case	4:
	                XFillArc(d,w,g,qx-4,rh-(qy+4),8,8,0,360*64);
                	break;
		case	5:
			dr[0].x = qx + 4;
			dr[0].y = rh - (qy + 4);
			dr[1].x = qx - 4;
			dr[1].y = rh - (qy + 4);
			dr[2].x = qx - 4;
			dr[2].y = rh - (qy - 4);
			dr[3].x = qx + 4;
			dr[3].y = rh - (qy - 4);
			XFillPolygon(d,w,g,dr,4,Convex,CoordModeOrigin);
                	break;
		case	6:
			dr[0].x = qx + 4;
			dr[0].y = rh - (qy - 4);
			dr[1].x = qx;
			dr[1].y = rh - (qy + 4);
			dr[2].x = qx - 4;
			dr[2].y = rh - (qy - 4);
			XFillPolygon(d,w,g,dr,3,Convex,CoordModeOrigin);
                	break;
		}
	}
}


void	ViewExtPlotMinMax(xmin,xmax,ymin,ymax,nx,ny,fg)
float	*xmin,*xmax,*ymin,*ymax;
int	*nx,*ny,fg;
{
	double	txmin,txmax,tymin,tymax;
	int	ndx,ndy;
	int	nx0,nx1,nx2,ny0,ny1,ny2;
	int	nxmin,nxmax,nymin,nymax;
	int	nr;
	int	nxdiv,nydiv;

	if (fg > 0) return;

	*xmin *=  0.99999;
	*ymin *=  0.99999;
	*xmax *=  1.00001;
	*ymax *=  1.00001;

	nx1 = -1; nx2 = -1; ny1 = -1; ny2 = -1;

	if (*xmin != 0.0) nx1 = (int)log10(fabs(*xmin)) - 1;
	if (*xmax != 0.0) nx2 = (int)log10(fabs(*xmax)) - 1;
	if (*ymin != 0.0) ny1 = (int)log10(fabs(*ymin)) - 1;
	if (*ymax != 0.0) ny2 = (int)log10(fabs(*ymax)) - 1;

        if (nx1 >= -1 && nx2 >= -1) {
		if (nx1 > nx2) nx0 = nx1;
		else           nx0 = nx2;
	}else if (nx1 < -1 && nx2 < -1) {
		if (nx1 > nx2) nx0 = nx1;
		else           nx0 = nx2;
	}else if (nx1 < 0 && nx2 < 0) {
                if (nx1 > nx2) nx0 = nx2;
                else           nx0 = nx1;
        }else{
		if (nx1 > nx2) nx0 = nx1;
		else           nx0 = nx2;
	}
        if (ny1 >= -1 && ny2 >= -1) {
		if (ny1 > ny2) ny0 = ny1;
		else           ny0 = ny2;
	}else if (ny1 < -1 && ny2 < -1) {
		if (ny1 > ny2) ny0 = ny1;
		else           ny0 = ny2;
	}else if (ny1 < 0 && ny2 < 0) {
                if (ny1 > ny2) ny0 = ny2;
                else           ny0 = ny1;
	}else{
		if (ny1 > ny2) ny0 = ny1;
	        else           ny0 = ny2;
	}
/*
	if (nx0 < 0) nx0 -= 1;
	if (ny0 < 0) ny0 -= 1;
*/

	nxdiv = 5;
	nydiv = 5;

	txmin = pow(10.0,(double)nx0);
	nxmin = *xmin / txmin - 1;

	txmax = pow(10.0,(double)nx0);
	nxmax = *xmax / txmax + 1;

	while((nxmax - nxmin) / nxdiv > 9) nxdiv *= 2;

	while(nxmin % nxdiv != 0) nxmin -= 1;
	*xmin = (double)nxmin * txmin;

	while(nxmax % nxdiv != 0) nxmax += 1;
	*xmax = (double)nxmax * txmax;

	ndx = nxmax - nxmin;
	*nx = ndx / nxdiv;

	tymin = pow(10.0,(double)ny0);
	nymin = *ymin / tymin - 1;

	tymax = pow(10.0,(double)ny0);
	nymax = *ymax / tymax + 1;

	while((nymax - nymin) / nydiv > 9) nydiv *= 2;

	while(nymin % nydiv != 0) nymin -= 1;
	*ymin = (double)nymin * tymin;

	while(nymax % nydiv != 0) nymax += 1;
	*ymax = (double)nymax * tymax;

	ndy = nymax - nymin;
	*ny = ndy / nydiv;
}

/*      fg = -1     ｎが２０ぐらい	                */
/*      fg = 0      ｎ、ｍｉｎ、ｍａｘ 定義しなくてよい	*/
/*      fg = 1      なにもしない		        */
/*      fg = 2      ｎ を定義する必要あり	        */
/*      fg = 3      ｍｉｎ、ｍａｘ を定義する必要あり   */

void	ViewExtPlotMinMax2(min,max,n,fg)
float	*min,*max;
int	*n,fg;
{
	double	tmin,tmax;
	int	nd;
	int	n0,n1,n2;
	int	nmin,nmax;
	int	nr;
	int	ndiv,nndiv;
        double	eps;

        if (fabs(*max - *min) < 10e-30) {
          *max += 1.0; *min -= 1.0;
          *n = 2;
          return;
        }else{
          eps = fabs(*max - *min) / 100.0;
        }
          
	switch(fg) {
          case	-1:
          case	 0:
	    *min -= eps; *max += eps;
	    n1 = -1; n2 = -1;

	    if (*min != 0.0) n1 = (int)log10(fabs(*min)) - 1;
	    if (*max != 0.0) n2 = (int)log10(fabs(*max)) - 1;

            if (n1 >= -1 && n2 >= -1) {
	      if (n1 > n2) n0 = n1;
	      else         n0 = n2;
	    }else if (n1 < -1 && n2 < -1) {
	      if (n1 > n2) n0 = n1;
	      else         n0 = n2;
	    }else if (n1 < 0 && n2 < 0) {
              if (n1 > n2) n0 = n2;
              else         n0 = n1;
            }else{
	      if (n1 > n2) n0 = n1;
	      else         n0 = n2;
	    }

            if (fg < 0) {
                ndiv = 10; nndiv = 39;
	    }else{       
                ndiv = 5;  nndiv = 9;
            }

	    tmin = pow(10.0,(double)n0);
	    nmin = *min / tmin - 1;

	    tmax = pow(10.0,(double)n0);
	    nmax = *max / tmax + 1;

	    while((nmax - nmin) / ndiv > nndiv) ndiv *= 2;

	    while(nmin % ndiv != 0) nmin -= 1;
	    *min = (double)nmin * tmin;

	    while(nmax % ndiv != 0) nmax += 1;
	    *max = (double)nmax * tmax;

	    nd = nmax - nmin;
            if (fg < 0) *n = 20;
	    else        *n = nd / ndiv;
            break;
          case	1:
            break;
	}
}
