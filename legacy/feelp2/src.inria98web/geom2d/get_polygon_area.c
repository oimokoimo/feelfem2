/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_polygon_area
 *      Date:   1995/09/1
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"


#include <math.h>

#include "geom2d.h"

#define DBG  0
/* #define XDBG 1   */
/* #define XDBG2   1 */       /* This just draw the outer shape */

#ifdef XDBG
static double dr = 0.0;
#endif

#ifdef XDBG2
static double dr = 0.0;
#endif

double get_polygon_area( po )
     POLYGON_ST *po;
{
  int i;
  int points;
  double *x,*y;
  double total_area;
  double coget_polygon_area();
  double xmin,ymin,xmax,ymax,dx,dy;


  points = po-> n;

  x = (double *)FEEL_GetMemory( sizeof(double)*(points+2));
  y = (double *)FEEL_GetMemory( sizeof(double)*(points+2));

  xmin = xmax = *(po->x);    /* these two lines for XDBG,XDBG2 */
  ymin = ymax = *(po->y);

  for(i=0;i<points;i++) {
    *(x+i) = *(po->x+i);
    *(y+i) = *(po->y+i);

    if(*(x+i) > xmax) xmax = *(x+i);  /* these 4 lines for XDBG,XDBG2 */
    if(*(y+i) > ymax) ymax = *(y+i);
    if(*(x+i) < xmin) xmin = *(x+i);
    if(*(y+i) < ymin) ymin = *(y+i);

  }
  *(x+points)   = *(po->x);    /* cyclic */
  *(y+points)   = *(po->y);
  *(x+points+1) = *(po->x + 1);         /* 1;2;....;n;1;2 */
  *(y+points+1) = *(po->y + 1);

#ifdef XDBG
  { static int come=0;
  if(come == 0)  { openpl(); come = 1; }
  }
  dx = xmax-xmin;
  dy = ymax-ymin;
  xmax = xmax + dx/20.0;
  ymax = ymax + dy/20.0;
  xmin = xmin - dx/20.0;
  ymin = ymin - dy/20.0;
  dr   = (xmax-xmin)/50.0;
  fspace(xmin,ymin,xmax,ymax);
  erase();
  xdbg_draw(x,y,points);
  fprintf(stderr,"Click window to start\n");
  xwait();
#endif

#ifdef XDBG2                   /* just show the outer shape */
  { static int come=0;
  if(come == 0)  { openpl(); come = 1; }
  }
  dx = xmax-xmin;
  dy = ymax-ymin;
  xmax = xmax + dx/20.0;
  ymax = ymax + dy/20.0;
  xmin = xmin - dx/20.0;
  ymin = ymin - dy/20.0;
  dr   = (xmax-xmin)/50.0;
  fspace(xmin,ymin,xmax,ymax);
  erase();
  xdbg_draw(x,y,points);
  fprintf(stderr,"Click window to start\n");
  xwait();
#endif

  if(points < 3) SystemAbort("Illegal points in get_polygon_area");
  if(points > MAX_POLYGON_NODE) SystemAbort("Too big polygon");

  total_area= 0.0;
  for(i=0;i<points-2;i++) {
    if(DBG) fprintf(stderr,"points = %d  i = %d\n",points,i);
    total_area = total_area + coget_polygon_area(points-i,x,y);
    if(DBG) fprintf(stderr,"RET \n");
  }

  if(DBG) fprintf(stderr,"total_area = %lf\n",total_area);

#ifdef XDBG

  printf("total_area = %lf \n",total_area);
  xwait();
#endif 

  FEEL_FreeMemory(x); 
  FEEL_FreeMemory(y);

  return(total_area);

  return;
}
     

double coget_polygon_area(n,x,y)
     int n;
     double *x,*y;
{
  int i,j;
  double area,tri_area_by_3p();
  int flag;

  /* try to remove next node */

  if(n == 3) {
    area = (double)tri_area_by_3p(*x,*y,*(x+1),*(y+1),*(x+2),*(y+2));

#ifdef XDBG
    fprintf(stderr,"FINISH\n");
    draw_tri(*x,*y,*(x+1),*(y+1),*(x+2),*(y+2));
#endif

    return(area);
  }


  for(i=0;i<n;i++) {


#ifdef XDBG
    long il;  il = i;
    fnumber(*(x+i+1),*(y+i+1),il);
    fprintf(stderr,"CHECK POINT i = %d\n",i);
    fprintf(stderr,"Click to CHECK!\n");
    xwait();

#endif

    
    if(DBG) fprintf(stderr,"Check for convex\n");
    if(not_convex_edge(*(x+i),  *(y+i),
		       *(x+i+1),*(y+i+1),
		       *(x+i+2),*(y+i+2)    )==YES) continue;

    if(DBG) fprintf(stderr,"Check for intersect\n");
    if(intersect(*(x+i),*(y+i),*(x+i+2),*(y+i+2),n,x,y) == YES) continue;

    /* check 3  97/11/12 added */
    if(DBG) fprintf(stderr,"Check for No.3\n");
    flag = NO;
    for(j=0;j<i;j++) {
      if(is_inside_tri(*(x+i),*(y+i),*(x+i+1),*(y+i+1),*(x+i+2),*(y+i+2),
		       *(x+j),*(y+j)) == YES) flag = YES;
    }
    for(j=i+3;j<n;j++) {
      if(is_inside_tri(*(x+i),*(y+i),*(x+i+1),*(y+i+1),*(x+i+2),*(y+i+2),
		       *(x+j),*(y+j)) == YES) flag = YES;
    }
    if(flag == YES) continue;
    

    area = tri_area_by_3p(*(x+i),  *(y+i),
			  *(x+i+1),*(y+i+1),
			  *(x+i+2),*(y+i+2));
#ifdef XDBG
    draw_tri(*(x+i),*(y+i),*(x+i+1),*(y+i+1),*(x+i+2),*(y+i+2));
#endif
    

    if(i == n-1)  {         /* cut the starting point */
      if(DBG) fprintf(stderr,"CUT THE FIRST POINT\n");
      for(j=0;j<n-1;j++) {
	*(x+j) = *(x+j+1);
	*(y+j) = *(y+j+1);
      }
      *(x+n-1)   = *x;      /* New 1st node */
      *(y+n-1)   = *y;
      *(x+n-1+1) = *(x+1);  /* New 2nd node */
      *(y+n-1+1) = *(y+1);
    }


    else {                 /* cut the 2nd point to last point */
      if(DBG) fprintf(stderr,"CUT 2nd POINT \n");

      for(j=i+1;j<n-1;j++) {
	*(x+j) = *(x+j+1);
	*(y+j) = *(y+j+1);
      }
      *(x+n-1)   = *x;      /* New 1st node */
      *(y+n-1)   = *y;
      *(x+n-1+1) = *(x+1);  /* New 2nd node */
      *(x+n-1+1) = *(y+1);
    }

    return (area);

  }

  area = -1.0;

  return(area);   /* This means ERROR  (06/oct/98 modified get_region_area) */


}

double tri_area_by_3p(x1,y1,x2,y2,x3,y3)
     double x1,y1,x2,y2,x3,y3;
{
  double s1,t1, s2,t2, area;

  s1 = x1-x2;
  t1 = y1-y2;

  s2 = x3-x2;
  t2 = y3-y2;

  area = (s1*t2 - t1*s2) / 2.0;

  if(area < 0.0) area = -area;

  if(area <= 0.0) SystemAbort("tri_area_by_3p(<=0 ERROR detected");

  return(area);
}



int not_convex_edge(x1,y1,x2,y2,x3,y3)
     double x1,y1,x2,y2,x3,y3;
{
  double ss,tt,s1,t1, s2,t2, r , cosine, sine;

  s1 = x1-x2;
  t1 = y1-y2;

  s2 = x3-x2;
  t2 = y3-y2;

  r = sqrt(s2*s2+t2*t2);
  
  cosine = s2/r;
  sine   = t2/r;

  /* rotate s1,t1 */
  ss = cosine * s1 + sine   * t1;
  tt = -sine  * s1 + cosine * t1;


#ifdef XDBG
  fmove(x1,y1);
  fcont(x2,y2);
  fcont(x3,y3);
  fprintf(stderr,"This angle is ");
  if(tt>0) {
    fprintf(stderr,"    CONVEX %lf\n",tt);
  }
  else {
    fprintf(stderr,"NOT CONVEX %lf\n",tt);
  }
#endif

  if(tt >0 ) {
    return (NO);
  }
  else {
    return (YES);
  }

}



int intersect(x1,y1,x2,y2,n,x,y)    /* *(x+n) = *(x) */
     double x1,y1,x2,y2;
     int n;
     double *x,*y;
{
  int i;

  for(i=0;i<n;i++) {

    if(x1 == *(x+i)   && y1 == *(y+i)) continue;
    if(x1 == *(x+i+1) && y1 == *(y+i+1)) continue;
    if(x2 == *(x+i)   && y2 == *(y+i)) continue;
    if(x2 == *(x+i+1) && y2 == *(y+i+1)) continue;

    if(is_mid_connect(x1,y1,x2,y2,
		      *(x+i),*(y+i),*(x+i+1),*(y+i+1)) == YES) {
      return(YES);
    }

  }
  return (NO);

}

int is_mid_connect(x1,y1,x2,y2,xx1,yy1,xx2,yy2)
     double  x1, y1, x2, y2;
     double xx1,yy1,xx2,yy2;
{
  double s,t,px,py,qx,qy;
  double u,v;
  double a,b;
  double det;

  s  = x2 - x1;
  t  = y2 - y1;

  px = xx1- x1;
  py = yy1- y1;

  qx = xx2- x1;
  qy = yy2- y1;


  u  = qx - px;
  v  = qy - py;

  
  if(s*v-t*u != 0.0) {

    det = -s*v + t* u;

    a = (-v * px + u * py) / det;
    b = (-t * px + s * py) / det;

    if(DBG) fprintf(stderr,"a= %lf, b=%lf  ",a,b);

    if(a <= 0.0 || a >= 1.0 || b <= 0.0 || b >= 1.0) {
      if(DBG) fprintf(stderr,"NO\n");
      return(NO);
    }
    else {
      if(DBG) fprintf(stderr,"YES\n");
      return(YES);
    }

  }


  /* in case of two lines are parallel */


  if(px*qy == qx*py) {  /* This means these two line segment are on the
			   same line                                     */
    if(s >  0.0 && px > 0.0 && px < s) return(YES);
    if(s >  0.0 && qx > 0.0 && qx < s) return(YES);
    if(s <  0.0 && px < 0.0 && px > s) return(YES);
    if(s <  0.0 && qx < 0.0 && qx > s) return(YES);
    if(s == 0.0 && t  > 0.0 && py > 0.0 && py < t) return(YES);    
    if(s == 0.0 && t  > 0.0 && qy > 0.0 && qy < t) return(YES);
    if(s == 0.0 && t  < 0.0 && py < 0.0 && py > t) return(YES);    
    if(s == 0.0 && t  < 0.0 && qy < 0.0 && qy > t) return(YES);
  }
  
  return(NO);

}

int is_inside_tri(x1,y1,x2,y2,x3,y3,xx,yy)
     double x1,y1,x2,y2,x3,y3,xx,yy;
{
  double s,t;
  double dx1,dx2,dy1,dy2;
  double dx,dy;
  double det;

  dx1 = x1-x2;
  dy1 = y1-y2;
  dx2 = x3-x2;
  dy2 = y3-y2;

  dx  = xx-x2;
  dy  = yy-y2;

  det = dx1*dy2-dx2*dy1;
  if(det == 0.0) {fprintf(stderr,"DET ERROR in is_inside_tri det=%lf\n",det); exit(1); }
  t   = ( dy2*dx-dx2*dy)/det;
  s   = (-dy1*dx+dx1*dy)/det;

  if(DBG) fprintf(stderr,"t=%lf s=%lf",t,s);

  if( t <= 1.0 && t >=0.0 && s <= 1.0 && s >= 0.0 && t+s <= 1.0) { 

    /* case YES */

#ifdef XDBG
    if(DBG) fprintf(stderr,"  YES\n"); 
    fhako(xx,yy);
#endif 
    return (YES); 
  }

  /*case NO */
  if(DBG) fprintf(stderr," NO\n");
  return(NO);
}



#ifdef XDBG
xdbg_draw(x,y,n)
     double *x,*y;
     int     n;
{
  int i;
fprintf(stderr,"POLYGON POINTS = %d\n",n);
  fmove(*(x+n-1),*(y+n-1));
  for(i=0;i<n;i++) {
    fcont(*(x+i),*(y+i));
    fpeke(*(x+i),*(y+i));
  }
}
#endif

#ifdef XDBG2
xdbg_draw(x,y,n)
     double *x,*y;
     int     n;
{
  int i;
fprintf(stderr,"POLYGON POINTS = %d\n",n);
  fmove(*(x+n-1),*(y+n-1));
  for(i=0;i<n;i++) {
    fcont(*(x+i),*(y+i));
    fpeke(*(x+i),*(y+i));
    fnumber(*(x+i),*(y+i),i+1);
  }
}
#endif
