/**********************************************************
  
  xplotv.c   Version 1991/07/24  
  
  pget,etc added.                  1991/05/20
  PLOT compatible routines added.  1991/06/22
  NEWPEN          routine added.   1991/06/24
  REDRAW          function         1991/07/22
  MultiScreenModel and Motif       1991/07/24
  
  Latest change                    1991/08/07
				   1994/12/07
  ***********************************************************/
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Intrinsic.h>

#define BG_COL   "antiquewhite"

#define MAX_REDRAW 100000
#define MAX_PLANE      16


#define PLOT_LINE      1
#define PLOT_COL       2
#define PLOT_LINSEL    3
#define PLOT_PLATE     4

static int  X_AXIS = 600;
static int  Y_AXIS = 600;

static XEvent event;
XFontStruct *font;
static char *fontname = "lucidasanstypewriter-10";
static int FONTcomeyet = 0;


struct xplot_st { 
  Display *dpy; 
  Window root,win; 
  GC gc; 
  Colormap cmap;
  
  int screen , black,white;
  
  int        xlen,ylen;                   /* the size of the window  */ 
  int        spx0,spy0,spdx,spdy;         /* space function          */ 
  double     dspx0,dspy0,dspdx,dspdy;     /* space func for double   */
  int        cpx,cpy;                     /* current graphical point */
  double     dcpx,dcpy;                   /* double c.g. pointer     */
  
  int        redraw[MAX_REDRAW];          /* Data structure for redrawing */
  int        redraw_ptr;                
};

static struct xplot_st *plane[MAX_PLANE]  = {
  NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
  NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };

static struct  xplot_st     *nowp = NULL;
static int             plane_number = -1;

set_size( x , y)
	int x,y;
{ 
    X_AXIS = x;
    Y_AXIS = y;
}
plot_screen(n)
     int n;
{
  if(n <0 || n >= MAX_PLANE) {
    fprintf(stderr,"(plot_screen) Screen number error\n");
    return;
  }
  if(plane[n] == NULL) {
    fprintf(stderr,"(plot_screen) Screen %d is not opned yet.\n");
    return;
  }
  nowp = plane[n];
  plane_number = n;
  return;
  
}

plot_set_screen(n,dpyx,winx,gcx)
     Display *dpyx;
     Window winx;
     GC gcx;
     
     int n;
{
  int x,y,bw,depth;                  /* for XGetGeometry dummy */
  unsigned long MyColor();

  if(n <0 || n >= MAX_PLANE) {
    fprintf(stderr,"(plot_set_screen) Screen number error\n");
    return;
  }
  if(plane[n] != NULL) {
    fprintf(stderr,"(plot_set_screen) Screen %d has already been opned .\n",n);
    return;
  }
  
  plane[n] = (struct xplot_st *)malloc(sizeof (struct xplot_st));
  plane_number = n;
  
  nowp = plane[n];

  nowp->redraw_ptr = 0;
  nowp->redraw[0] = 0;
  
  nowp->dpy = dpyx;
  nowp->win = winx;
  nowp->gc  =  gcx;
  

  nowp->root = XDefaultRootWindow(nowp->dpy);
  nowp->screen = XDefaultScreen(nowp->dpy);
  nowp->cmap = XDefaultColormap(nowp->dpy,nowp->screen);
  nowp->black = XBlackPixel(nowp->dpy,nowp->screen);

 /*    nowp->white = XWhitePixel(nowp->dpy,nowp->screen); */
  
  nowp->white = MyColor(nowp->dpy,BG_COL); 
  
  XGetGeometry(nowp->dpy,nowp->win,&nowp->root,&x,&y,&nowp->xlen,&nowp->ylen,&bw,&depth); 

  return;
}

plot_flush(n)
int n;
{
  XFlush(plane[n]->dpy);
}

int openpl()
{
  int x,y,bw,depth;                  /* for XGetGeometry dummy */
  
  unsigned long MyColor();
  
  plane_number = 0;
  plane[plane_number] = (struct xplot_st *)malloc(sizeof (struct xplot_st));
  nowp = plane[plane_number];
  nowp->redraw[0] = 0;                     /* INITIALIZE FOR REDRAW */
  nowp->redraw_ptr = 0;
  
  nowp->dpy = XOpenDisplay( getenv("DISPLAY") );
  if( nowp->dpy == NULL ) {
    fprintf(stderr,"cannot open %s (X-window system)\n",getenv("DISPLAY"));
    exit(1);
  }
  nowp->root = XDefaultRootWindow(nowp->dpy);
  nowp->screen = XDefaultScreen(nowp->dpy);
  nowp->cmap = XDefaultColormap(nowp->dpy,nowp->screen);
  nowp->black = XBlackPixel(nowp->dpy,nowp->screen);
  /*    nowp->white = XWhitePixel(nowp->dpy,nowp->screen); */
  
  nowp->white = MyColor(nowp->dpy,BG_COL);
  
  nowp->win = XCreateSimpleWindow(nowp->dpy,nowp->root,0,0,X_AXIS,Y_AXIS,1,nowp->black,nowp->white);
  /*    XChangeWindowAttributes(nowp->dpy,nowp->win,CWBackingStore,Always);
   */
  XSelectInput(nowp->dpy,nowp->win,ExposureMask);
  
  nowp->gc = XCreateGC(nowp->dpy,nowp->win,0,NULL);
  XSetForeground(nowp->dpy,nowp->gc,nowp->black);
  XSetBackground(nowp->dpy,nowp->gc,nowp->white);
  
  /*    XSetFunction(nowp->dpy,nowp->gc,GXxor);  */
  XMapWindow(nowp->dpy,nowp->win);
  
  XNextEvent(nowp->dpy,&event);        /* wait for the window open in real screen */
  
  XGetGeometry(nowp->dpy,nowp->win,&nowp->root,&x,&y,&nowp->xlen,&nowp->ylen,&bw,&depth);
  
  return;
}

/*  Multi screen version openpl */

int openplv(n)
     int n;
{
  int x,y,bw,depth;                  /* for XGetGeometry dummy */
  
  unsigned long MyColor();
  
  if(n < 0 || n >= MAX_PLANE) {
    fprintf(stderr,"(openplv)Screen number must be  0 <= n <= 15\n");
    return;
  }
  
  if(plane[n] != NULL) {
    fprintf(stderr,"(openplv)Screen %d is opened already.\n",n);
    return;
  }
  
  
  plane_number = n;
  plane[plane_number] = (struct xplot_st *)malloc(sizeof (struct xplot_st));
  nowp = plane[plane_number];
  nowp->redraw[0] = 0;                     /* INITIALIZE FOR REDRAW */
  nowp->redraw_ptr = 0;
  
  nowp->dpy = XOpenDisplay( getenv("DISPLAY") );
  if( nowp->dpy == NULL ) {
    fprintf(stderr,"cannot open %s (X-window system)\n",getenv("DISPLAY"));
    exit(1);
  }
  nowp->root = XDefaultRootWindow(nowp->dpy);
  nowp->screen = XDefaultScreen(nowp->dpy);
  nowp->cmap = XDefaultColormap(nowp->dpy,nowp->screen);
  nowp->black = XBlackPixel(nowp->dpy,nowp->screen);
  /*    nowp->white = XWhitePixel(nowp->dpy,nowp->screen); */
  
  nowp->white = MyColor(nowp->dpy,BG_COL);
  
  nowp->win = XCreateSimpleWindow(nowp->dpy,nowp->root,0,0,X_AXIS,Y_AXIS,1,nowp->black,nowp->white);
  /*    XChangeWindowAttributes(nowp->dpy,nowp->win,CWBackingStore,Always);
   */
  XSelectInput(nowp->dpy,nowp->win,ExposureMask);
  
  nowp->gc = XCreateGC(nowp->dpy,nowp->win,0,NULL);
  XSetForeground(nowp->dpy,nowp->gc,nowp->black);
  XSetBackground(nowp->dpy,nowp->gc,nowp->white);
  
  /*    XSetFunction(nowp->dpy,nowp->gc,GXxor);  */
  XMapWindow(nowp->dpy,nowp->win);
  
  XNextEvent(nowp->dpy,&event);        /* wait for the window open in real screen */
  
  XGetGeometry(nowp->dpy,nowp->win,&nowp->root,&x,&y,&nowp->xlen,&nowp->ylen,&bw,&depth);
  
  return;
}
int openplvd(n,sname)
     int n;
     char *sname;
{
  int x,y,bw,depth;                  /* for XGetGeometry dummy */
  
  unsigned long MyColor();
  
  if(n < 0 || n >= MAX_PLANE) {
    fprintf(stderr,"(openplv)Screen number must be  0 <= n <= 15\n");
    return;
  }
  
  if(plane[n] != NULL) {
    fprintf(stderr,"(openplv)Screen %d is opened already.\n",n);
    return;
  }
  
  
  plane_number = n;
  plane[plane_number] = (struct xplot_st *)malloc(sizeof (struct xplot_st));
  nowp = plane[plane_number];
  nowp->redraw[0] = 0;                     /* INITIALIZE FOR REDRAW */
  nowp->redraw_ptr = 0;
  
  nowp->dpy = XOpenDisplay( sname );
  if( nowp->dpy == NULL ) {
    fprintf(stderr,"cannot open %s (X-window system)\n",sname);
    exit(1);
  }
  nowp->root = XDefaultRootWindow(nowp->dpy);
  nowp->screen = XDefaultScreen(nowp->dpy);
  nowp->cmap = XDefaultColormap(nowp->dpy,nowp->screen);
  nowp->black = XBlackPixel(nowp->dpy,nowp->screen);
  /*    nowp->white = XWhitePixel(nowp->dpy,nowp->screen); */
  
  nowp->white = MyColor(nowp->dpy,BG_COL);
  
  nowp->win = XCreateSimpleWindow(nowp->dpy,nowp->root,0,0,X_AXIS,Y_AXIS,1,nowp->black,nowp->white);
  /*    XChangeWindowAttributes(nowp->dpy,nowp->win,CWBackingStore,Always);
   */
  XSelectInput(nowp->dpy,nowp->win,ExposureMask);
  
  nowp->gc = XCreateGC(nowp->dpy,nowp->win,0,NULL);
  XSetForeground(nowp->dpy,nowp->gc,nowp->black);
  XSetBackground(nowp->dpy,nowp->gc,nowp->white);
  
  /*    XSetFunction(nowp->dpy,nowp->gc,GXxor);  */
  XMapWindow(nowp->dpy,nowp->win);
  
  XNextEvent(nowp->dpy,&event);        /* wait for the window open in real screen */
  
  XGetGeometry(nowp->dpy,nowp->win,&nowp->root,&x,&y,&nowp->xlen,&nowp->ylen,&bw,&depth);
  
  return;
}

/*      wait routine */
xwait()
{
  XSelectInput(nowp->dpy,nowp->win, ExposureMask | ButtonPressMask);
  while(1) {
    XNextEvent(nowp->dpy,&event); 
    switch(event.type)
      {
      case Expose:
	expose_redraw();
	break;
      case ButtonPress :
	return;
      default:
	break;
      }
  }
}

xwait_() {xwait();}


int pget(x,y)                               /* get the cordinate when button
					       pressed. */
     int *x,*y;
{
  int rx,ry,wx,wy;
  unsigned int key;
  Window    wr,wc;
  
  XSelectInput(nowp->dpy,nowp->win,ButtonPressMask | ExposureMask );
  while(1) {
    XNextEvent(nowp->dpy,&event);
    switch(event.xany.type) {
    case ButtonPress:
      XQueryPointer(nowp->dpy,nowp->win,&wr,&wc,&rx,&ry,&wx,&wy,&key);
      *x = wx * nowp->spdx / nowp->xlen + nowp->spx0;
      *y = (nowp->ylen - wy) * nowp->spdy / nowp->ylen + nowp->spy0;
      XSelectInput(nowp->dpy,nowp->win,ExposureMask);
      return(key);
    case Expose:
      expose_redraw();
      break;
      
    default:
      break;
    }
  }
}


int fpget(x,y)                               /* get the cordinate when button
						pressed. */
     double *x,*y;
{
  int rx,ry,wx,wy;
  unsigned int key;
  Window    wr,wc;
  
  XSelectInput(nowp->dpy,nowp->win,ButtonPressMask | ExposureMask);
  while(1) {
    XNextEvent(nowp->dpy,&event);
    switch(event.xany.type) {
    case ButtonPress:
      XQueryPointer(nowp->dpy,nowp->win,&wr,&wc,&rx,&ry,&wx,&wy,&key);
      *x = wx * nowp->dspdx / (double)nowp->xlen + nowp->dspx0;
      *y = ((double)nowp->ylen - wy ) * nowp->dspdy / (double)nowp->ylen + nowp->dspy0;
      XSelectInput(nowp->dpy,nowp->win,ExposureMask);
      return(key);
    case Expose:
      expose_redraw();
      break;
      
    default:
      break;
    }
  }
}

closepl()
{
  XSelectInput(nowp->dpy,nowp->win,ExposureMask | ButtonPressMask);
  while(1) { 
    XNextEvent(nowp->dpy,&event);           /* wait button press before break the window */
    switch(event.xany.type)
      {
      case Expose:
	expose_redraw();
	break;
      case ButtonPress:
	if(FONTcomeyet) {
	  XFreeFont(nowp->dpy,font);
	}
	XFreeGC(nowp->dpy,nowp->gc);
	XDestroyWindow(nowp->dpy,nowp->win);
	XCloseDisplay(nowp->dpy);
	
	free(plane[plane_number]);
	plane[plane_number] = NULL;
	plane_number = -1;
	
	return;
	break;
	
      default:
	break;
      }
  }
}

/*    Multi screen closepl   this routine destroys window without delay */

closeplv(n)
     int n;
{
  struct xplot_st *tmpp;
  
  if(n < 0 || n >= MAX_PLANE) {
    fprintf(stderr,"(closeplv) Screen number error.\n");
    return;
  }
  if(plane[n] == NULL) {
    fprintf(stderr,"(closeplv) Screen %d is not opened.\n",n);
    return;
  }
  tmpp = plane[n];
  
  XFreeGC(tmpp->dpy,tmpp->gc);
  XDestroyWindow(tmpp->dpy,tmpp->win);
  XCloseDisplay(tmpp->dpy);
  
  if(nowp == plane[n]) nowp == NULL;
  free(plane[n]);
  plane[n] = NULL;
  if(n == plane_number) plane_number = -1;
  
  return;
  
}

plot_terminate_screen(n)
     int n;
{
  struct xplot_st *tmpp;
  
  if(n < 0 || n >= MAX_PLANE) {
    fprintf(stderr,"(plot_terminate_screen) Screen number error.\n");
    return;
  }
  if(plane[n] == NULL) {
    fprintf(stderr,"(plot_terminate_screen) Screen %d is not opened.\n",n);
    return;
  }
  tmpp = plane[n];
  erasev(n);
  
  XFreeGC(tmpp->dpy,tmpp->gc);
/*  XDestroyWindow(tmpp->dpy,tmpp->win);  */
/*  XCloseDisplay(tmpp->dpy);             */
  
  if(nowp == plane[n]) nowp == NULL;
  free(plane[n]);
  plane[n] = NULL;
  if(n == plane_number) plane_number = -1;
  
  return;
}

erase()                          /* clear the window */
{
  nowp->redraw_ptr = 0;
  nowp->redraw[0]  = 0;
  XClearWindow(nowp->dpy,nowp->win);
  return;
}
erasev(n)                          /* clear the window */
int n;
{
  struct xplot_st *tmpp;

  if(n < 0 || n >= MAX_PLANE) {
    fprintf(stderr,"(erasev) Screen number error.\n");
    return;
  }
  if(plane[n] == NULL) {
    fprintf(stderr,"(erasev) Screen %d is not opened.\n",n);
    return;
  }

  tmpp = plane[n];

  tmpp->redraw_ptr = 0;
  tmpp->redraw[0]  = 0;
  XClearWindow(nowp->dpy,nowp->win);
  return;
}

space(x1,y1,x2,y2)
     int x1,y1,x2,y2;
{
  int dx,dy;
  dx = x2 - x1;
  dy = y2 - y1;
  if(dx <= 0 || dy <= 0) {
    fprintf(stderr,"space parameter error %d %d %d %d\n",x1,y1,x2,y2);
    exit(1);
  }
  if(dx * nowp->ylen > dy * nowp->xlen) {
    dy = dx * nowp->ylen / nowp->xlen;
  }
  else if( dx * nowp->ylen < dy * nowp->xlen) {
    dx = dy * nowp->xlen/ nowp->ylen;
  }
  nowp->spdx = dx;
  nowp->spdy = dy;
  nowp->spx0 = x1;
  nowp->spy0 = y1;
  nowp->dspdx = (double)dx;
  nowp->dspdy = (double)dy;
  nowp->dspx0 = (double)x1;
  nowp->dspy0 = (double)y1;
  return;
}

fspace(x1,y1,x2,y2)
     double x1,y1,x2,y2;
{
  double dx,dy;
  dx = x2 - x1;
  dy = y2 - y1;
  if(dx <= 0 || dy <= 0) {
    fprintf(stderr,"space parameter error %le %le %le %le\n",x1,y1,x2,y2);
    exit(1);
  }
  if(dx * (double)nowp->ylen > dy * (double)nowp->xlen) {
    dy = dx * (double)nowp->ylen / (double)nowp->xlen;
  }
  else if( dx * (double)nowp->ylen < (double) dy * nowp->xlen) {
    dx = dy * (double)nowp->xlen / (double)nowp->ylen;
  }
  nowp->dspdx = dx;
  nowp->dspdy = dy;
  nowp->dspx0 = x1;
  nowp->dspy0 = y1;
  nowp->spdx =  nowp->xlen;
  nowp->spdy =  nowp->ylen;
  nowp->spx0 =     0;
  nowp->spy0 =     0;
  return;
}


move(x,y)
     int x,y;
{
  nowp->cpx = x;
  nowp->cpy = y;
  return;
}

fmove(x,y)
     double x,y;
{
  nowp->dcpx = x;
  nowp->dcpy = y;
}

cont(x,y)
     int x,y;
{
  int x1,x2,y1,y2;
  x1 = ( x  - nowp->spx0) * nowp->xlen / nowp->spdx;
  x2 = (nowp->cpx - nowp->spx0) * nowp->xlen / nowp->spdx;
  y1 = ( y  - nowp->spy0) * nowp->ylen / nowp->spdy;
  y2 = (nowp->cpy - nowp->spy0) * nowp->ylen / nowp->spdy;
  
  nowp->cpx = x;
  nowp->cpy = y;
  
  
  y1 = nowp->ylen - y1;
  y2 = nowp->ylen - y2;
  plot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,x1,y1,x2,y2);
  
  return;
}

/*                   */
fpeke_(x,y)
     double *x,*y;
{fpeke(*x,*y);}

fpeke(x,y)
     double x,y;
{
  int x1,y1;
  x1 = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  y1 = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
  y1 = nowp->ylen - y1;
  plot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,x1-2,y1-2,x1+2,y1+2);
  plot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,x1-2,y1+2,x1+2,y1-2);
}

fhako_(x,y)
     double *x,*y;
{fhako(*x,*y);}

fhako(x,y)
     double x,y;
{
  int x1,y1;
  x1 = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  y1 = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
  y1 = nowp->ylen - y1;
  plot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,x1-2,y1-2,x1+2,y1-2);
  plot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,x1+2,y1-2,x1+2,y1+2);
  plot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,x1+2,y1+2,x1-2,y1+2);
  plot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,x1-2,y1+2,x1-2,y1-2);
}
/*********/


fcont(x,y)
     double x,y;
{
  int x1,x2,y1,y2;
  
  x1 = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  x2 = (nowp->dcpx - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  y1 = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
  y2 = (nowp->dcpy - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
  
  nowp->dcpx = x;
  nowp->dcpy = y;
  
  y1 = nowp->ylen - y1;
  y2 = nowp->ylen - y2;
  
  plot_XDrawLine(nowp->dpy,nowp->win,nowp->gc,x1,y1,x2,y2);
  
  return;
}

symbol(x,y,s)
     int x,y;
     char *s;
{
  int x1,x2,y1,y2;
  x = ( x  - nowp->spx0) * nowp->xlen / nowp->spdx;
  y = ( y  - nowp->spy0) * nowp->ylen / nowp->spdy;
  
  y = nowp->ylen - y;
  
  if(FONTcomeyet == 0 ) {
    FONTcomeyet = 1;
    font = XLoadQueryFont(nowp->dpy,fontname);
    XSetFont(nowp->dpy,nowp->gc,font->fid);
  }
  XDrawString(nowp->dpy,nowp->win,nowp->gc,x,y,s,strlen(s));
}

fnumber_(x,y,n)
     double *x,*y;
     long *n;
{fnumber(*x,*y,*n);}

fnumber(x,y,n)
     double x,y;
     long n;
{
  char buf[BUFSIZ];
  sprintf(buf,"%ld",n);
  fsymbol(x,y,buf);
}

fsymbol(x,y,s)
     double x,y;
     char *s;
{
  int ix,iy;
  
  ix = ( x   - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  iy = ( y   - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
  
  iy = nowp->ylen - iy;
  
  if(FONTcomeyet == 0 ) {
    FONTcomeyet = 1;
    font = XLoadQueryFont(nowp->dpy,fontname);
    XSetFont(nowp->dpy,nowp->gc,font->fid);
  }
  XDrawString(nowp->dpy,nowp->win,nowp->gc,ix,iy,s,strlen(s));
}

RGBcolor(r,g,b)
     int r,g,b;
{
  XColor newcolor;
  XGCValues values;
  unsigned long valuemask;
  
/*  valuemask = GCForeground; */
  valuemask = GCForeground;
  
  newcolor.red   = r;
  newcolor.green = g;
  newcolor.blue  = b;
  if(XAllocColor(nowp->dpy,nowp->cmap,&newcolor) == 0) {
    fprintf(stderr,"fail color allocation(XAllocColor)\n");
    return;
  }
  values.foreground = newcolor.pixel;
  XChangeGC(nowp->dpy,nowp->gc,valuemask,&values);
}

draw_tri(x1,y1,x2,y2,x3,y3)
  double x1,y1,x2,y2,x3,y3;
{
  XPoint xp[3]; 
  xp[0].x = ( x1  - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  xp[0].y = ( y1  - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
  xp[1].x = ( x2  - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  xp[1].y = ( y2  - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
  xp[2].x = ( x3  - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  xp[2].y = ( y3  - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

  xp[0].y = nowp->ylen - xp[0].y;
  xp[1].y = nowp->ylen - xp[1].y;
  xp[2].y = nowp->ylen - xp[2].y;

  XFillPolygon(nowp->dpy,nowp->win,nowp->gc,xp,3,Convex,CoordModeOrigin);
}

draw_rect(x1,y1,x2,y2,x3,y3,x4,y4)
  double x1,y1,x2,y2,x3,y3,x4,y4;
{
  XPoint xp[4]; 
  xp[0].x = ( x1  - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  xp[0].y = ( y1  - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
  xp[1].x = ( x2  - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  xp[1].y = ( y2  - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
  xp[2].x = ( x3  - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  xp[2].y = ( y3  - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;
  xp[3].x = ( x4  - nowp->dspx0) * (double)nowp->xlen / nowp->dspdx;
  xp[3].y = ( y4  - nowp->dspy0) * (double)nowp->ylen / nowp->dspdy;

  xp[0].y = nowp->ylen - xp[0].y;
  xp[1].y = nowp->ylen - xp[1].y;
  xp[2].y = nowp->ylen - xp[2].y;
  xp[3].y = nowp->ylen - xp[3].y;

  XFillPolygon(nowp->dpy,nowp->win,nowp->gc,xp,4,Convex,CoordModeOrigin);
}


set256color( n )
int n;
{
    static char *array[] = {
      "white",
      "blue",
      "red",
      "green",
      "yellow",
      "skyblue",
      "cyan",
      "aquamarine1",
      "goldenrod",
      "khaki",
      "gray30",
      "gray60",
      "lightpink",
      "magenta",
      "violet",
      "plum",

      "steelblue",
      "darkgreen",
      "greenyellow",
      "lightyellow",
      "olivedrab",
      "salmon",
      "chocolate",
      "tan",
      
      "orangered",
      "deeppink",
      "purple",
      "deepskyblue",
      "powderblue",
      "aquamarine",
      "seagreen",
      "gold"
      };




    char name[20];
    if(n < 1 || n > 32) {
      fprintf(stderr,"set256color must be 1 to 32\n");
      exit(1);
    }
    sprintf(name,"gray%d",n*6);
    plot_color(array[n-1]); 
    /* plot_color(name); */


    return;
}
    


/* FORTRAN INTERFACE ROUTINE */
openpl_()
{openpl();}

closepl_()
{closepl();}

space_(a,b,c,d) 
     int *a,*b,*c,*d;
{space(*a,*b,*c,*d);}

fspace_(a,b,c,d) 
     double *a,*b,*c,*d;
{fspace(*a,*b,*c,*d);}

move_(a,b)
     int *a,*b;
{move(*a,*b);}

fmove_(a,b)
     double *a,*b;
{fmove(*a,*b);}

cont_(a,b)
     int *a,*b;
{cont(*a,*b);}

fcont_(a,b)
     double *a,*b;
{fcont(*a,*b);}

line(a,b,c,d)
     int a,b,c,d;
{move(a,b);cont(c,d);return;}

fline(a,b,c,d)
     double a,b,c,d;
{fmove(a,b);fcont(c,d);return;}

line_(a,b,c,d)
     int *a,*b,*c,*d;
{line(*a,*b,*c,*d);}

fline_(a,b,c,d)
     double *a,*b,*c,*d;
{fline(*a,*b,*c,*d);}

symbol_(x,y,s)
     int *x,*y;
     char *s;
{symbol(*x,*y,s);}

fsymbol_(x,y,s)
     double *x,*y;
     char *s;
{fsymbol(*x,*y,s);}

plots_()
{
  openpl();
  fspace(0.0,0.0,10.0,10.0);         /* デフォルトの値 */
}

plotv_()
{
  closepl();
}

plot_(x,y,ip)
     float *x,*y;
     int *ip;
{
  double dx,dy;
  dx = *x;
  dy = *y;
  
  if(*ip < 0 || *ip == 3) {
    fmove(dx,dy);
  }
  else {
    if(*ip == 2) {
      fcont(dx,dy);
    }
    else {
      fprintf(stderr,"Illegal function (PLOT) %d\n",*ip);
    }
  }
}

linsel_(ltypev)
     int *ltypev;
{
  linsel(*ltypev);
}

newpen_(icolv)
     int *icolv;
{
  switch(*icolv) {
  case 0:
    plot_color("black");
    break;
  case 1:
    plot_color("blue");
    break;
  case 2:
    plot_color("red");
    break;
  case 3:
    plot_color("purple");
    break;
  case 4:
    plot_color("green");
    break;
  case 5:
    plot_color("lightblue");
    break;
  case 6:
    plot_color("yellow");
    break;
  default:
    plot_color("black");
    break;
  }
}



linsel(n)
     int n;
{
  unsigned int line_width;
  
  line_width = 1;
  if(nowp->redraw_ptr + 3 < MAX_REDRAW)  {
    nowp->redraw[nowp->redraw_ptr++] = 3;
    nowp->redraw[nowp->redraw_ptr++] = n;
    nowp->redraw[nowp->redraw_ptr]   = 0;
  }
  
  switch(n) {
  case 1:
    XSetLineAttributes(nowp->dpy,nowp->gc,line_width,LineSolid,CapNotLast,JoinMiter);
    break;
  case 2:
    XSetLineAttributes(nowp->dpy,nowp->gc,line_width,LineOnOffDash,CapNotLast,JoinMiter);
    break;
  case 3:
  case 4:
    XSetLineAttributes(nowp->dpy,nowp->gc,line_width,LineDoubleDash,CapNotLast,JoinMiter);
    break;
  default:
    break;
  }
}


/****************************************************************************
  
  以下、Ｘウインドウ用の拡張
  
  *****************************************************************************/
plot_color(color_name)
     char *color_name;
{
  unsigned long MyColor();
  unsigned long color;
  
  color = MyColor(nowp->dpy,color_name);
  plot_XSetForeground (nowp->dpy,nowp->gc,color);
}

scolor_(s)
     char *s;
{
  plot_color(s);
}

erase_()
{
   erase();
}



/*   X11 extension function */

unsigned long MyColor(display ,color)
     Display *display;
     char *color;
{
  Colormap cmap;
  XColor c0,c1;
  
  cmap = DefaultColormap(display ,0);
  
  XAllocNamedColor(display ,cmap,color,&c1,&c0);
  
  return(c1.pixel);
}



/* X11 Exposeure redraw routine */

plot_XDrawLine(dpy,win,gc,a,b,c,d)
     Display *dpy;
     Window   win;
     GC        gc;
{
  XDrawLine(dpy,win,gc,a,b,c,d);
  if(nowp->redraw_ptr + 6 > MAX_REDRAW) return;
  nowp->redraw[nowp->redraw_ptr++] = 1;
  nowp->redraw[nowp->redraw_ptr++] = a;
  nowp->redraw[nowp->redraw_ptr++] = b;
  nowp->redraw[nowp->redraw_ptr++] = c;
  nowp->redraw[nowp->redraw_ptr++] = d;
  nowp->redraw[nowp->redraw_ptr]  = 0;
}

plot_XSetForeground(dpy,gc,color)
     Display *dpy;
     GC        gc;
     unsigned long color;
{
  XSetForeground(dpy,gc,color);
  if(nowp->redraw_ptr + 3 > MAX_REDRAW) return;
  nowp->redraw[nowp->redraw_ptr++] = 2;
  nowp->redraw[nowp->redraw_ptr++] = color;
  nowp->redraw[nowp->redraw_ptr]   = 0;
  
}

/* linesel中で定義  */
plot_plate(x,y,r)
int x,y,r;
{
  int x1,y1,r1;
  x1 = ( x  - nowp->spx0) * nowp->xlen / nowp->spdx;
  y1 = ( y  - nowp->spy0) * nowp->ylen / nowp->spdy;
  y1 = nowp->ylen - y1;
  r1 = r * nowp->xlen / nowp->spdx;
  x1 = x1 - r1;
  y1 = y1 - r1;
  r1 = r1 * 2;
  plot_XFillArc(nowp->dpy,nowp->win,nowp->gc,x1,y1,r1,r1,0,23040);
}

plot_XFillArc(dpy,win,gc,x,y,width,height,angle1,angle2)
Display *dpy;
Window win;
GC gc;
int x,y;
unsigned int width,height;
int angle1,angle2;
{
  XFillArc(dpy,win,gc,x,y,width,height,angle1,angle2);
  if(nowp->redraw_ptr + 8 > MAX_REDRAW) return;
  nowp->redraw[nowp->redraw_ptr++] = PLOT_PLATE;
  nowp->redraw[nowp->redraw_ptr++] = x;
  nowp->redraw[nowp->redraw_ptr++] = y;
  nowp->redraw[nowp->redraw_ptr++] = width;
  nowp->redraw[nowp->redraw_ptr++] = height;
  nowp->redraw[nowp->redraw_ptr++] = angle1;
  nowp->redraw[nowp->redraw_ptr++] = angle2;
  nowp->redraw[nowp->redraw_ptr] = 0;
  
}

expose_redraw()
{
  long ptr;
  int func;
  unsigned int line_width;
  
  
  line_width = 1;
  
  ptr = 0;
  
  while(nowp->redraw[ptr]){
    switch(nowp->redraw[ptr])
      {
      case 1:                      /* XDrawLine */
	XDrawLine(nowp->dpy,nowp->win,nowp->gc,nowp->redraw[ptr+1],nowp->redraw[ptr+2],nowp->redraw[ptr+3],nowp->redraw[ptr+4]);
	ptr += 5;
	break;
	
      case 2:                      /* XSetForeground */
	XSetForeground(nowp->dpy,nowp->gc,nowp->redraw[ptr+1]);
	ptr += 2;
	break;
	
      case 3:                      /* XSetLineAttributes */
	switch( nowp->redraw[ptr+1])
	  {
	  case 1:
	    XSetLineAttributes(nowp->dpy,nowp->gc,line_width,LineSolid,CapNotLast,JoinMiter);
	    break;
	  case 2:
	    XSetLineAttributes(nowp->dpy,nowp->gc,line_width,LineOnOffDash,CapNotLast,JoinMiter);
	    break;
	  case 3:
	  case 4:
	    XSetLineAttributes(nowp->dpy,nowp->gc,line_width,LineDoubleDash,CapNotLast,JoinMiter);
	    break;
	  default:
	    break;
	  }
	ptr += 2;
	break;

      case 4:               /* XFillArc */
	XFillArc(nowp->dpy,nowp->win,nowp->gc,nowp->redraw[ptr+1],nowp->redraw[ptr+2],nowp->redraw[ptr+3],nowp->redraw[ptr+4],nowp->redraw[ptr+5],nowp->redraw[ptr+6]);
	ptr += 7;
	break;
	
      default:
	break;
      }
  }
}


expose_redraw_callback(wd,screen_number,gc)
     Widget wd;
     GC     gc;
     int    screen_number;
{
  long ptr;
  int func;
  unsigned int line_width;
  struct xplot_st *tmpp;

  if(screen_number <0 || screen_number >= MAX_PLANE) {
    fprintf(stderr,"(expose_redraw_callback) Screen number[%d] error\n",screen_number);
    return;
  }
  if(plane[screen_number] == NULL) {
    fprintf(stderr,"(expose_redraw_callback) %d is not opened.\n",screen_number);
    return;
  }
  
  tmpp = plane[screen_number];
  
  
  line_width = 1;
  ptr = 0;
  
  while(tmpp->redraw[ptr]){
    switch(tmpp->redraw[ptr])
      {
      case 1:                      /* XDrawLine */
	XDrawLine(tmpp->dpy,tmpp->win,tmpp->gc,tmpp->redraw[ptr+1],tmpp->redraw[ptr+2],tmpp->redraw[ptr+3],tmpp->redraw[ptr+4]);
	ptr += 5;
	break;
	
      case 2:                      /* XSetForeground */
	XSetForeground(tmpp->dpy,tmpp->gc,tmpp->redraw[ptr+1]);
	ptr += 2;
	break;
	
      case 3:                      /* XSetLineAttributes */
	switch( tmpp->redraw[ptr+1])
	  {
	  case 1:
	    XSetLineAttributes(tmpp->dpy,tmpp->gc,line_width,LineSolid,CapNotLast,JoinMiter);
	    break;
	  case 2:
	    XSetLineAttributes(tmpp->dpy,tmpp->gc,line_width,LineOnOffDash,CapNotLast,JoinMiter);
	    break;
	  case 3:
	  case 4:
	    XSetLineAttributes(tmpp->dpy,tmpp->gc,line_width,LineDoubleDash,CapNotLast,JoinMiter);
	    break;
	  default:
	    break;
	  }
	ptr += 2;
	break;
	
      default:
	printf("(expose_redraw_callback)oh my god!\n");
	return;
	break;
      }
  }
}



