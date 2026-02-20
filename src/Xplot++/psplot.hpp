/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : psplot.hpp
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

#ifndef FEM_CLASS_PSPLOT
#define FEM_CLASS_PSPLOT

#include <iostream>


#define YES   1
#define NO    0
#define NONE -1

#define PSPLOT_MAX_FONTS    10

#define PSPLOT_PEKE_LEN      2.0     // peke


//#define MAX_PS_FILES    11       // in C++ version, not controlled here
//#define DEFAULT_XLEN   600
//#define DEFAULT_YLEN   600

#define PSPLOT_DEFAULT_FONT_NAME  "/Times-Roman"
#define PSPLOT_DEFAULT_FONT_SIZE  10
#define PSPLOT_DEFAULT_LINEWIDTH   5

/* NEC PC-602PS, PR-3000PS  */
#define PSPLOT_XDOT   574
#define PSPLOT_YDOT   776
#define PSPLOT_XMAX   612
#define PSPLOT_YMAX   792
#define PSPLOT_GX      24
#define PSPLOT_GY      15

class psplot {
public:
  psplot(const char *filename);
  ~psplot();


  void psinit(void); // called from constructor to write header PS 

  //  unsigned long xplotMycolor(char *);  
  //  void xcolor(char *);
  //  void waitEvent(void);
  void spaceInteger(int,int,int,int);
  void spaceDouble(double,double,double,double);
  void moveToInteger(int,int);
  void moveToDouble(double,double);
  void contToInteger(int,int);
  void contToDouble(double,double);

  // peke
  void pekeToInteger(int,int);
  void pekeToDouble(double,double);

  
  void symbolInteger(int,int,const char *);
  void symbolDouble(double,double,const char *);


  void psErase(void);
  void closeFile(void);

  // inner function
  void DrawLine(double,double,double,double)  ;   // cont,fcont
  void WriteString(double,double,const char *);   // symbol,fsymbol
  void DrawPeke(double,double);


private:
  FILE     *fp;
  double  rate;
  
  int     currentPageNo;
    
  int     xlen,ylen;

  int           spx0,spy0;   /* integer base point  */
  int           spdx,spdy;   /* integer edge length */
  double      dspx0,dspy0;   /* double  base point  */
  double      dspdx,dspdy;   /* double  edge length */

  int             cpx,cpy;   /* integer current point */
  double        dcpx,dcpy;   /* double  current point */

  int   fontSizeArray[PSPLOT_MAX_FONTS];
  int   currentFontNo;
  int   fonts;

  double xCoord(double);
  double xCoord( int  );
  double yCoord(double);
  double yCoord( int  );

};

#endif
