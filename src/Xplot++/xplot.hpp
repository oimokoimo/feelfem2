/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : xplot++.hpp
 *  Date     : 2001/04/10
 *  Modified : 
 *  
 *  Purpose  :
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#ifndef FEM_CLASS_XPLOT
#define FEM_CLASS_XPLOT


#include <X11/Xlib.h>

#define XPLOT_DEFAULT_FOREGROUND  "black"
#define XPLOT_DEFAULT_BACKGROUND  "white"
#define XPLOT_DEFAULT_X_WINDOW_LENGTH  600
#define XPLOT_DEFAULT_Y_WINDOW_LENGTH  600

#define XPLOT_PEKE_LEN                   2   // peke length


class xplot {
public:
  xplot(const char *DISPLAY);
  xplot(const char *DISPLAY,int xSize,int ySize);  // with window size
  ~xplot();

  unsigned long xplotMycolor(const char *);  
  void xcolor(const char *);
  void waitEvent(void);
  void closeWindow(void);

  void spaceInteger(int,int,int,int);
  void spaceDouble(double,double,double,double);

  void moveToInteger(int,int);
  void moveToDouble(double,double);
  void contToInteger(int,int);
  void contToDouble(double,double);

  // peke
  void pekeToInteger(int,int);
  void pekeToDouble(double,double);

  void symbolInteger(int,int, const char *);
  void symbolDouble(double,double,const char *);


  // Inner function
  void DrawLine(int,int,int,int);
  void WriteString(int,int,const char *);
  void DrawPeke(int,int);

  // general ...
  int  xplotStrlen(const char *);

private:
  int xplotScreenNo;
  
  Display      *dpy;
  Window        root;
  Window        win;
  GC            gc;
  Colormap      cmap;
  XEvent        event;

  int           screen;
  int           fg;
  int           bg;
  unsigned int  bw;
  unsigned int  depth;

  int           xPos,yPos;     // Window position
  unsigned int  xlen,ylen;     // Window size

  int           spx0,spy0;     /* integer base point  */
  int           spdx,spdy;     /* integer edge length */
  double        dspx0,dspy0;   /* double  base point  */
  double        dspdx,dspdy;   /* double  edge length */
  
  int             cpx,cpy;   /* integer current point */
  double        dcpx,dcpy;   /* double  current point */
  
  int         FONTcomeyet;
  Font               font;

  // Private transform functions
  int xCoord(int);
  int xCoord(double);
  int yCoord(int);
  int yCoord(double);

};

#endif
