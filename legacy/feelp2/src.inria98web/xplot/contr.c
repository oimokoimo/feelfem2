/*
 *  contr.c
 *
 *  draw contour program
 *
 *  date 1996/07/04
 *
 *
 *  functions
 *
 *
 *
 */
#include <stdio.h>
#include "contr.h"



static double xx[10],yy[10];
static int    ipts;
static double contr_val[MAX_BARS];   /*  val[n-1] <=  x  < val[n] */
static int    contr_bars;
static int grayscale[MAX_BARS];
static int line_flag = 1;
static int draw_flag = 0;

void contr_line_flag_on() 
{
  line_flag = 1;
  return;
}
void contrdrawoff_()
{
  draw_flag = 0;
  return;
}
void contrdrawon_()
{
  draw_flag = 1;
  return;
}

void contrlineon_()
{
  contr_line_flag_on();
  return;
}

/*
 *  GRAY scale 
 *
 *
 */


void contr_glib_init()    /* Gray scale */
{
  int i,max,gray;
  int how_many_contr_bars();

  max = how_many_contr_bars();
  max = max+1;
  for(i=0;i<max;i++) {
    gray = 100 * i /(max-1) ;
    grayscale[i] = gray;        /* in case of PostScript, xplot routine
				   converts to 0.0 to 1.0               */
  }
  setgray(0);
  return;

}

void contr_glib_user_set( n, nval )
     int  n;
     int *nval;
{
  int i,max;
  int how_many_contr_bars();
  max = how_many_contr_bars();
  max = max+1;

  if(max != n) {
    fprintf(stderr,"number of color bars mismatch  %d/%d\nignored\n",max,nval);
    return;
  }

  for(i=0;i<max;i++) {
    grayscale[i] = *(nval+i);
  }
  return;

}
/* FORTRAN interface to above routine */
void contrusetgray_( n , m)
     int *n;
     int *m;
{
  contr_glib_user_set(*n,m);
  return;
}


void draw_contr_3(x0,y0,x1,y1,x2,y2,scale)
     double x0,y0,x1,y1,x2,y2;
     int scale;
{
  double x[3],y[3];

  if(draw_flag ==0) return;

  setgray(grayscale[scale]);
  x[0] = x0; x[1] = x1; x[2] = x2;
  y[0] = y0; y[1] = y1; y[2] = y2;

/*  fprintf(stdout,"contr_3  %d\n",scale);
  fprintf(stdout,"grayscale  %d\n",grayscale[scale]);
  */
  fpolygon(3,x,y);
  return;
}

void draw_contr_4(x0,y0,x1,y1,x2,y2,x3,y3,scale)
     double x0,y0,x1,y1,x2,y2,x3,y3;
     int scale;
{
  double x[4],y[4];

  if(draw_flag ==0) return;
  setgray(grayscale[scale]);

/*  fprintf(stdout,"contr_4  %d\n",scale);
*/
  x[0] = x0; x[1] = x1; x[2] = x2; x[3] = x3;
  y[0] = y0; y[1] = y1; y[2] = y2; y[3] = y3;

  fpolygon(4,x,y);
  return;
}

void draw_contr_5(x0,y0,x1,y1,x2,y2,x3,y3,x4,y4,scale)
     double x0,y0,x1,y1,x2,y2,x3,y3,x4,y4;
     int scale;
{
  double x[5],y[5];

  if(draw_flag ==0) return;
  setgray(grayscale[scale]);

/*  fprintf(stdout,"contr_5  %d\n",scale);
*/
  x[0] = x0; x[1] = x1; x[2] = x2; x[3] = x3; x[4] = x4;
  y[0] = y0; y[1] = y1; y[2] = y2; y[3] = y3; y[4] = y4;

  fpolygon(5,x,y);
  return;
}




/*
 *   contr main routines
 *
 *
 */

/* Buffer Initialize */
static void contr_buf_init()
{
  ipts = 0;
  return;
}

static void contr_buf_push(x,y)
     double x,y;
{
  if(ipts >0 && xx[ipts-1] == x && yy[ipts-1] == y) return;
  xx[ipts] = x;
  yy[ipts] = y;
  ipts++;
  return;
}

static void contr_buf_draw( scale )
     int scale;
{
  int i;
/* OIMO  printf("scale=%d :",scale); 
  for(i=0;i<ipts;i++) {
    printf("(%lf,%lf) ",xx[i],yy[i]);
  }
  printf("\n");
  */

  if(ipts == 3) {
    draw_contr_3(xx[0],yy[0],xx[1],yy[1],xx[2],yy[2],scale);
    ipts = 0;
    return;
  }
  if(ipts == 4) {
    draw_contr_4(xx[0],yy[0],xx[1],yy[1],xx[2],yy[2],xx[3],yy[3],scale);
    ipts = 0;
    return;    
  }
  if(ipts == 5) {
    draw_contr_5(xx[0],yy[0],xx[1],yy[1],xx[2],yy[2],xx[3],yy[3],xx[4],yy[4],
		 scale);
    ipts = 0;
    return;    
  }
  fprintf(stderr,"Illegal data contr_buf_draw %d\n",ipts);
  exit(1);
}


void tricontr_uni(x1,y1,x2,y2,x3,y3,v1)
double x1,y1,x2,y2,x3,y3,v1;
{
  int scale;

  scale = get_contr_scale(v1);

/*  printf("oimo tricontr_uni  %lf\n",v1);
*/

  draw_contr_3(x1,y1,x2,y2,x3,y3,scale);

  return;
}

/*
 *     v1 is the smallest value 
 *  Pre routine adjusts
 *   
 */
void tricontr_dif(x1,y1,x2,y2,x3,y3,v1,v2,v3)
double x1,y1,v1;
double x2,y2,v2;
double x3,y3,v3;
{
  int i;
  int dstep12,dstep23,dstep13;  /* node points for each side */
  int dstep;                    /* total nodes */
  int scale;
  double a12[MAX_BARS];
  double a23[MAX_BARS];
  double a13[MAX_BARS];

  double xx12[MAX_BARS];
  double yy12[MAX_BARS];
  int    fc12[MAX_BARS];

  double xx13[MAX_BARS];
  double yy13[MAX_BARS];
  double fc13[MAX_BARS];

  /* standard point is POINT P1 */
  
  int flag23;        /*  0:v2=v3  1:v2<v3  -1:v3<v2 */


  dstep12 = step_contr(v1,v2,a12);   /* step contour は開始点含まず */
  dstep13 = step_contr(v1,v3,a13);

  if(v2 < v3) {
    dstep23 = step_contr(v2,v3,a23);
    flag23  = 1;
    dstep   = dstep13;
  }
  else if( v2 == v3) {
    flag23 = 0;
    dstep  = dstep13;
  }
  else {
    flag23  = -1;
    dstep23 = step_contr(v3,v2,a23);
    dstep   = dstep12;
  }
  
  /* 何れも終了点に達しない場合 */
  if(dstep == 0) {
    tricontr_uni(x1,y1,x2,y2,x3,y3,v1);
    return;
  }

  /* Make xx,yy,fc  array */

  /* first node */
  xx12[0] = x1;  yy12[0] = y1;  fc12[0] = 0;
  xx13[0] = x1;  yy13[0] = y1;  fc13[0] = 0;

  /* Side 12 */
  for(i=1;i<=dstep12;i++) {
    xx12[i] = (x2-x1)*a12[i-1]+x1;
    yy12[i] = (y2-y1)*a12[i-1]+y1;
    if(a12[i-1] == 1.0) {
      fc12[i] = 1;
    }
    else {
      fc12[i] = 0;
    }
  }
  
  if(dstep12<dstep13) {      /* flag23 is not suitable here */
    for(i=0;i<dstep23;i++) {
      xx12[i+dstep12+1] = (x3-x2)*a23[i]+x2;
      yy12[i+dstep12+1] = (y3-y2)*a23[i]+y2;
      fc12[i+dstep12+1] = 2;
    }
  }

  /* Side 13 */
  for(i=1;i<=dstep13;i++) {
    xx13[i] = (x3-x1)*a13[i-1]+x1;
    yy13[i] = (y3-y1)*a13[i-1]+y1;
    if(a13[i-1] == 1.0) {
      fc13[i] = 1;
    }
    else {
      fc13[i] = 0;
    }
  }
  
  if(dstep13<dstep12) {      /* flag23 is not suitable here */
    for(i=0;i<dstep23;i++) {
      xx13[i+dstep13+1] = (x2-x3)*a23[i]+x3;
      yy13[i+dstep13+1] = (y2-y3)*a23[i]+y3;
      fc13[i+dstep13+1] = 2;
    }
  }
 

  /* fc flag means    0  on original side
   *                  1  on vertex
   *                  2  on side 23
   */

  scale   = get_contr_scale(v1);     /* base scale value */

  for(i=0;i<dstep;i++) {

    contr_buf_init();
    
    contr_buf_push(xx12[i],yy12[i]);     /* start point on line 12 */

    if(fc12[i] == 0 && fc12[i+1] == 2) {
      contr_buf_push(x2,y2);
    }
    contr_buf_push(xx12[i+1],yy12[i+1]);

    contr_buf_push(xx13[i+1],yy13[i+1]);

    if(fc13[i+1] == 2 && fc13[i] == 0) {
      contr_buf_push(x3,y3);
    }

    if(i != 0) {
      contr_buf_push(xx13[i],yy13[i]);
    }

      

    contr_buf_draw(scale);
    
    scale++;
  }

  for(i=0;i<dstep;i++) {
    if(line_flag!=0 && i <dstep-1) {

#ifdef MPIXPLOT
      mpixplotfline_(xx12+i+1,yy12+i+1,xx13+i+1,yy13+i+1);
#else
      setgray(0);
      fline(xx12[i+1],yy12[i+1],xx13[i+1],yy13[i+1]);
#endif

    }
  }
  /* draw highest region */
  if(v2 > v3) {
    if(fc12[dstep] == 1) return;
  }
  else {
    if(fc13[dstep] == 1) return;
  }


  contr_buf_init();
  contr_buf_push(xx12[dstep],yy12[dstep]);
  if(fc12[dstep] == 0) contr_buf_push(x2,y2);
  if(fc13[dstep] == 0) contr_buf_push(x3,y3);
  contr_buf_push(xx13[dstep],yy13[dstep]);
  contr_buf_draw(scale);

  if(line_flag!=0 ) {
#ifdef MPIXPLOT
    mpixplotfline_(xx12+dstep,yy12+dstep,xx13+dstep,yy13+dstep);
#else
    setgray(0);
    fline(xx12[dstep],yy12[dstep],xx13[dstep],yy13[dstep]);
#endif
  }

  return;
}

/*
 *  contour common routine
 *
 *
 */


void contr_val_init(n,val)
     int n;
     double *val;
{
  int i;

  if(n > MAX_BARS) {
    fprintf(stderr,"Too many step values\n");
    exit(1);
  }

  contr_bars = n;

  for(i=0;i<n;i++) {
/*    fprintf(stderr,"%d  %lf\n",i,*(val+i)); */
    contr_val[i] = *(val+i);
  }


  contr_glib_init();    /* Initialize graphic library  X11 or PostScript */
  return;
}


int get_contr_scale( v1 )      /* scale starts 0 to contr_bars  */
     double v1;
{
  int i;

  for(i=0;i<contr_bars;i++) {
    if(v1 < contr_val[i]) return(i);
  }
  return(contr_bars);
}


int step_contr(v1,v2,a)
double v1,v2;
double *a;
{
  int i;
  int from,to;
  double val;

  int step;

  if(v1 > v2) {
    fprintf(stderr,"Illegal value in step contr\n");
    exit(1);
  }

  from = get_contr_scale(v1);
  to   = get_contr_scale(v2);

  if(from == to) return(0);  /* これには、v1==v2の場合も含まれる  */

  step = to - from;

  for(i=0;i<step;i++) {
    val = contr_val[from+i];
    *(a+i) = (val-v1)/(v2-v1);    /* return 0 to 1 */
    if(*(a+i) < 0.0 || *(a+i) >1.0) {
      fprintf(stderr,"arere?? \n");
      exit(1);
    }
  }
/*  fprintf(stderr,"STEP-CONTOUR\n");
  fprintf(stderr,"FROM %lf  TO %lf\n",v1,v2);
  for(i=0;i<step;i++) {
      fprintf(stderr,"i=%d  %lf\n",i,*(a+i));
  }
  */
  return(step);
}

/*
 *
 *
 *
 */

void tricontr(x1,y1,x2,y2,x3,y3,v1,v2,v3)
double x1,y1,v1;
double x2,y2,v2;
double x3,y3,v3;
{
  if( (v1 == v2 ) && (v2 == v3) ) {
    tricontr_uni(x1,y1,x2,y2,x3,y3,v1);
    return;
  }

  if( (v1 <= v2 ) && (v1 <= v3) ) {
    tricontr_dif(x1,y1,x2,y2,x3,y3,v1,v2,v3);
    return;
  }

  if( (v2 <= v3 ) && (v2 <= v1) ) {
    tricontr_dif(x2,y2,x3,y3,x1,y1,v2,v3,v1);
    return;
  }

  tricontr_dif(x3,y3,x1,y1,x2,y2,v3,v1,v2);
  return;
}




/* FORTRAN interfaces */

void tricontr_(x1,y1,x2,y2,x3,y3,v1,v2,v3)
double *x1,*y1,*v1;
double *x2,*y2,*v2;
double *x3,*y3,*v3;
{ 
 tricontr(*x1,*y1,*x2,*y2,*x3,*y3,*v1,*v2,*v3);
}  


void contrinit77_(n,val)
int *n;
double *val;
{
    contr_val_init(*n,val);
    return;
}



int how_many_contr_bars()
{
  return(contr_bars);
}

void contr_setgray( n )
int n;
{
  setgray(grayscale[n]);
  return;
}
