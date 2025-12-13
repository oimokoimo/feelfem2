/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Xplot++.cpp
 *  Date     : 2001/04/10
n *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>

#include "xplot.hpp"
#include "xplotfuncs.hpp"

extern "C" {
  Display *XOpenDisplay(const char *);
};

xplot::xplot(char *displayName)
{
  xplotScreens++;
  xplotScreenNo = xplotScreens;


  cerr << "Open display "<<displayName << endl;

  dpy = XOpenDisplay(displayName);  /* Open display */
  if( dpy == NULL) {
    fprintf(stderr,"Can't Open display %s",displayName);
    exit(1);
  }

  root   = XDefaultRootWindow(dpy);
  screen = XDefaultScreen(dpy);
  cmap   = XDefaultColormap(dpy,screen);

  fg     = xplotMycolor(XPLOT_DEFAULT_FOREGROUND);
  bg     = xplotMycolor(XPLOT_DEFAULT_BACKGROUND);

  xlen   = XPLOT_DEFAULT_X_WINDOW_LENGTH;
  ylen   = XPLOT_DEFAULT_Y_WINDOW_LENGTH;

  win    = XCreateSimpleWindow(dpy,root,0,0,xlen,ylen,1,fg,bg);

  char window_name[BUFSIZ];
  sprintf(window_name,"xplot++ screen %d",xplotScreenNo);
  XStoreName(dpy,win,window_name);

  XSelectInput(dpy,win,
	       ExposureMask |
	       ButtonPressMask |
	       ButtonReleaseMask |
	       Button1MotionMask );
  
    gc = XCreateGC(dpy,win,0,NULL);
    XSetForeground(dpy,gc,fg);
    XSetBackground(dpy,gc,bg);

    XMapWindow(dpy,win);

    XNextEvent(dpy,&event);

    XGetGeometry(dpy,win,&root,&xPos,&yPos,&xlen,&ylen,&bw,&depth);
    
    root = root;      /* window manager may change the window size */
    xlen = xlen;
    ylen = ylen;


    spx0 = 0;       /* default size if space or fspace not called */
    spy0 = 0;
    spdx = xlen;
    spdy = ylen;

    dspx0 = 0.0;
    dspy0 = 0.0;
    dspdx = (double) xlen;
    dspdy = (double) ylen;

    FONTcomeyet  = 0;

    return;
}

xplot::xplot(char *displayName, int xSize, int ySize)
{
  xplotScreens++;
  xplotScreenNo = xplotScreens;


  cerr << "Open display "<<displayName << endl;

  dpy = XOpenDisplay(displayName);  /* Open display */
  if( dpy == NULL) {
    fprintf(stderr,"Can't Open display %s",displayName);
    exit(1);
  }

  root   = XDefaultRootWindow(dpy);
  screen = XDefaultScreen(dpy);
  cmap   = XDefaultColormap(dpy,screen);

  fg     = xplotMycolor(XPLOT_DEFAULT_FOREGROUND);
  bg     = xplotMycolor(XPLOT_DEFAULT_BACKGROUND);

  xlen   = xSize;
  ylen   = ySize;

  win    = XCreateSimpleWindow(dpy,root,0,0,xlen,ylen,1,fg,bg);

  char window_name[BUFSIZ];
  sprintf(window_name,"xplot++ screen %d",xplotScreenNo);
  XStoreName(dpy,win,window_name);

  XSelectInput(dpy,win,
	       ExposureMask |
	       ButtonPressMask |
	       ButtonReleaseMask |
	       Button1MotionMask );
  
    gc = XCreateGC(dpy,win,0,NULL);
    XSetForeground(dpy,gc,fg);
    XSetBackground(dpy,gc,bg);

    XMapWindow(dpy,win);

    XNextEvent(dpy,&event);

    XGetGeometry(dpy,win,&root,&xPos,&yPos,&xlen,&ylen,&bw,&depth);
    
    root = root;      /* window manager may change the window size */
    xlen = xlen;
    ylen = ylen;


    spx0 = 0;       /* default size if space or fspace not called */
    spy0 = 0;
    spdx = xlen;
    spdy = ylen;

    dspx0 = 0.0;
    dspy0 = 0.0;
    dspdx = (double) xlen;
    dspdy = (double) ylen;

    FONTcomeyet  = 0;

    return;
}

unsigned long xplot::xplotMycolor( char *color_name)
{
  //    Colormap cmap;
  XColor c0,c1;
  //    cmap = DefaultColormap(dpy,0);
  XAllocNamedColor( dpy, cmap, color_name,&c1,&c0);
  return(c1.pixel);
}

void xplot::xcolor( char *color_name )
{
  //    Colormap cmap;
  XColor c0,c1;
  //    cmap = DefaultColormap(dpy,0);
  XAllocNamedColor( dpy,cmap,  color_name,&c1,&c0);
  XSetForeground(dpy,gc,c1.pixel);
  return;
}

void xplot::waitEvent(void)
{
  XSelectInput(dpy,win, ExposureMask | ButtonPressMask );

  while(1) {
    XNextEvent(dpy,&event);
    switch(event.type) {
    case Expose:
	//	      xplot_expose_redraw();
	break;
    case ButtonPress:
      return;
	      
    default:
      break;
    }
  }
}

void xplot::spaceInteger(int x1,int y1,int x2,int y2)
{
  int dx = x2 - x1;
  int dy = y2 - y1;

  if(dx * ylen > dy * xlen) {            /* size ajust */
    dy = dx * ylen / xlen;
  }
  else if( dx * ylen < dy * xlen) {
    dx = dy * xlen/ ylen;
  }
  spdx = dx;
  spdy = dy;
  spx0 = x1;
  spy0 = y1;
  dspdx = (double)dx;
  dspdy = (double)dy;
  dspx0 = (double)x1;
  dspy0 = (double)y1;

  return;
}

void xplot::spaceDouble(double x1,double y1,double x2,double y2)
{
  double dx,dy;

  dx = x2 - x1;
  dy = y2 - y1;

  if(dx * (double)ylen > dy * (double)xlen) {
    dy = dx * (double)ylen / (double)xlen;
  }
  else if( dx * (double)ylen < (double) dy * xlen) {
    dx = dy * (double)xlen / (double)ylen;
  }
    
  dspdx = dx;             /* double part of translation parameter */
  dspdy = dy;
  dspx0 = x1;
  dspy0 = y1;

  return;
}

void xplot::moveToInteger(int x,int y)
{
  cpx = x;
  cpy = y;

  return;
}

void xplot::moveToDouble(double x,double y)
{
  dcpx = x;
  dcpy = y;

  return;
}

// cont,fcont
void xplot::contToInteger(int x,int y)
{
    int x1,x2,y1,y2;

    x1 = ( x  - spx0) * xlen / spdx;
    x2 = (cpx - spx0) * xlen / spdx;
    y1 = ( y  - spy0) * ylen / spdy;
    y2 = (cpy - spy0) * ylen / spdy;
    
    cpx = x;
    cpy = y;
    
    
    //    y1 = ylen - y1;
    //    y2 = ylen - y2;
    DrawLine(x1,y1,x2,y2);

    return;
}


void xplot::contToDouble(double x,double y)
{
    int x1,x2,y1,y2;

    //    x1 = int(( x   - dspx0) * (double)xlen / dspdx);
    //    y1 = int(( y   - dspy0) * (double)ylen / dspdy);
    x1 = xCoord(x);
    y1 = yCoord(y);
    x2 = xCoord(dcpx);
    y2 = yCoord(dcpy);

    //    x2 = int((dcpx - dspx0) * (double)xlen / dspdx);
    //    y2 = int((dcpy - dspy0) * (double)ylen / dspdy);
    
    dcpx = x;
    dcpy = y;
    
    //    y1 = ylen - y1;
    //    y2 = ylen - y2;
    
    DrawLine(x1,y1,x2,y2);

    return;
}
///////////////////////////////////////////////////////////////////////
// symbol,fsymbol
///////////////////////////////////////////////////////////////////////
void xplot::symbolInteger(int x,int y, const char *mesg)
{
  int x1,y1;

    x1 = xCoord(x);
    y1 = yCoord(y);
    
    //    cpx = x;
    //    cpy = y;
    
    WriteString(x1,y1,mesg);

    return;
}

void xplot::symbolDouble(double x,double y,const char *mesg)
{
    int x1,x2,y1,y2;

    x1 = xCoord(x);
    y1 = yCoord(y);
    
    //    dcpx = x;
    //    dcpy = y;
    
    WriteString(x1,y1,mesg);

    return;
}

////////////////////////////////////////////////////////
// peke
////////////////////////////////////////////////////////
void xplot::pekeToInteger(int x,int y)
{
  int x1,y1;

    x1 = xCoord(x);
    y1 = yCoord(y);

    DrawPeke(x1,y1);

    return;
}

void xplot::pekeToDouble(double x,double y)
{
  int x1,y1;

    x1 = xCoord(x);
    y1 = yCoord(y);

    DrawPeke(x1,y1);

    return;
}

//
//
//  Inner functions. These functions call X-Window subroutines.
//
//
//
void xplot::DrawLine(int a,int b, int c, int d) 
{
  // store the data for redraw.....


  XDrawLine(dpy,win,gc,a,b,c,d);  
  return;
}
// 

void xplot::WriteString(int a, int b, const char *mesg)
{
  XDrawString(dpy,win,gc,a,b,mesg,xplotStrlen(mesg));
  XFlush(dpy);
  
  return;
}

void xplot::DrawPeke(int a,int b)
{
  XDrawLine(dpy,win,gc,
	    a-XPLOT_PEKE_LEN,b-XPLOT_PEKE_LEN,
	    a+XPLOT_PEKE_LEN,b+XPLOT_PEKE_LEN   );

  XDrawLine(dpy,win,gc,
	    a-XPLOT_PEKE_LEN,b+XPLOT_PEKE_LEN,
	    a+XPLOT_PEKE_LEN,b-XPLOT_PEKE_LEN   );

  return;
}


void xplot::closeWindow(void)
{
  //  cerr << "DO NOTHING NOW   void xplot::closeWindow(void) \n";

  XFreeGC(dpy,gc);
  XDestroyWindow(dpy,win);
  XCloseDisplay(dpy);

  return;
}

int xplot::xCoord( double x )
{
  return(int(( x   - dspx0) * (double)xlen / dspdx));
}

int xplot::xCoord( int x )
{
  return( ( x  - spx0) * xlen / spdx );
}


int xplot::yCoord( int y )
{
  return( ylen - ( y  - spy0) * ylen / spdy);
}

int xplot::yCoord( double y )
{  
  return(ylen - int(( y   - dspy0) * (double)ylen / dspdy));
}


int xplot::xplotStrlen(const char *str)
{
  int length = 0;
  while(*str) {
    length ++;
    str++;
  }

  return(length);
}
