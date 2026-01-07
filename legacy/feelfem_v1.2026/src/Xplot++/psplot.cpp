/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : psplot.cpp
 *  Date     : 2001/04/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "psplot.hpp"
#include <stdio.h>
#include <stdlib.h>

psplot::psplot(const char *filename)
{
  fp = fopen(filename,"w");

  if(fp == NULL) {
    fprintf(stderr,"psplot constructor: cannot open %s to write.\n",filename);
    exit(1);
  }

  xlen = PSPLOT_XDOT;
  ylen = PSPLOT_YDOT;
    
  spx0 = 0;
  spy0 = 0;
  spdx = PSPLOT_XDOT;
  spdy = PSPLOT_YDOT;
  dspx0 = 0.0;
  dspy0 = 0.0;
  dspdx = (double)PSPLOT_XDOT;
  dspdy = (double)PSPLOT_YDOT;

  currentPageNo = 1;

  psinit();

  return;
}

psplot::~psplot(void)
{
  if(fp != 0) {
    closeFile();
  }
  return;
}

void psplot::psinit(void)
{
  char *getdateForPsplot(void);
  //    char *get_user_name();

  for(int i=0;i<PSPLOT_MAX_FONTS;i++) fontSizeArray[i] = 0;
  currentFontNo = 0;
  fonts         = 1;
    
    // default font
  fontSizeArray[currentFontNo] = PSPLOT_DEFAULT_FONT_SIZE;
 
  fprintf(fp,"%%!\n");
  fprintf(fp,"%%!PS-Adobe-1.0\n");

  //    fprintf(fp,"%%%%Creater:%s\n",get_user_name());
  fprintf(fp,"%%%%Creater:psplot\n");
  fprintf(fp,"%%%%Date   :%s\n",getdateForPsplot());
  fprintf(fp,"%%%%EndComments\n");


  /* PostScript Header File (ps_header.c in the old version) */
  double width = (double)PSPLOT_DEFAULT_LINEWIDTH / 10.0;

  fprintf(fp,"%%-------- First font variable ---------------------------\n");
  fprintf(fp,"/Font00 %s findfont %d scalefont def\n",
	  PSPLOT_DEFAULT_FONT_NAME,fontSizeArray[currentFontNo]);
  fprintf(fp,"%%-------- Default font set ------------------------------\n");
  fprintf(fp,"Font00 setfont\n");
  fprintf(fp,"%%-------- Default line width-----------------------------\n");
  fprintf(fp,"%4.1lf setlinewidth\n",width);
  fprintf(fp,"%%-------- Define variables ------------------------------\n");
  fprintf(fp,"/Xpos 0 def   \n");
  fprintf(fp,"/Ypos 0 def\n");
  fprintf(fp,"/Dxpos 0 def\n");
  fprintf(fp,"/Dypos 0 def\n");
  fprintf(fp,"%%-------- Define procedure for saving file size ---------\n");
  fprintf(fp,"/N { newpath } def\n");
  fprintf(fp,"/MT { moveto } def\n");
  fprintf(fp,"/LT { lineto } def\n");
  fprintf(fp,"/ST { stroke } def\n");
  fprintf(fp,"/CP { closepath } def\n");
  fprintf(fp,"/FL { fill      } def\n");
  fprintf(fp,"/SG { setgray   } def\n");
  fprintf(fp,"%%-------- show string migi zume  Tutorial p.42 ----------\n");
  fprintf(fp,"/RightShow\n");
  fprintf(fp,"{ dup stringwidth pop\n");
  fprintf(fp,"  4 -1 roll exch sub \n");
  fprintf(fp,"  3 -1 roll moveto\n");
  fprintf(fp,"  show } def\n");
  fprintf(fp,"/MiddleShow\n");
  fprintf(fp,"{ dup stringwidth pop\n");
  fprintf(fp,"  2 div\n");
  fprintf(fp,"  4 -1 roll exch sub\n");
  fprintf(fp,"  3 -1 roll moveto\n");
  fprintf(fp,"  show } def\n");
  fprintf(fp,"/SupShow\n");
  fprintf(fp,"{ /Fontsize exch def \n");
  fprintf(fp,"  4 -1 roll\n");
  fprintf(fp,"  dup /Xpos exch def\n");
  fprintf(fp,"  4 -1 roll\n");
  fprintf(fp,"  dup /Ypos exch def\n");
  fprintf(fp,"  moveto\n");
  fprintf(fp,"  exch dup stringwidth\n");
  fprintf(fp,"  2 div\n");
  fprintf(fp,"  Ypos add Fontsize 0.8 mul add /Ypos exch def\n");
  fprintf(fp,"  Xpos add /Xpos exch def\n");
  fprintf(fp,"  show\n");
  fprintf(fp,"  Xpos Ypos moveto\n");
  fprintf(fp,"  0.5 0.5 scale show\n");
  fprintf(fp,"  2.0 2.0 scale } def\n");
  fprintf(fp,"\n");
  fprintf(fp,"/SupMiddleShow\n");
  fprintf(fp,"{ /Fontsize exch def\n");
  fprintf(fp,"  4 -1 roll\n");
  fprintf(fp,"  /Xpos exch def\n");
  fprintf(fp,"  3 -1 roll\n");
  fprintf(fp,"  /Ypos exch def\n");
  fprintf(fp,"  exch dup stringwidth\n");
  fprintf(fp,"  /Dypos exch def\n");
  fprintf(fp,"  2 div /Dxpos exch def\n");
  fprintf(fp,"  Xpos Dxpos sub\n");
  fprintf(fp,"  Ypos \n");
  fprintf(fp,"  moveto\n");
  fprintf(fp,"  show\n");
  fprintf(fp,"  Xpos Dxpos add\n");
  fprintf(fp,"  Ypos Dypos add Fontsize 0.8 mul add moveto\n");
  fprintf(fp,"  0.5 0.5 scale show\n");
  fprintf(fp,"  2.0 2.0 scale } def\n");
  fprintf(fp,"\n");
  fprintf(fp,"/SupRightShow\n");
  fprintf(fp,"{ /Fontsize exch def\n");
  fprintf(fp,"  4 -1 roll\n");
  fprintf(fp,"  /Xpos exch def\n");
  fprintf(fp,"  3 -1 roll\n");
  fprintf(fp,"  /Ypos exch def\n");
  fprintf(fp,"  exch dup stringwidth\n");
  fprintf(fp,"  2 div /Dypos exch def\n");
  fprintf(fp,"  /Dxpos exch def\n");
  fprintf(fp,"  Xpos Dxpos sub \n");
  fprintf(fp,"  Ypos moveto\n");
  fprintf(fp,"  show\n");
  fprintf(fp,"  Xpos\n");
  fprintf(fp,"  Ypos Dypos add Fontsize 0.8 mul add\n");
  fprintf(fp,"  moveto\n");
  fprintf(fp,"  0.5 0.5 scale show\n");
  fprintf(fp,"  2.0 2.0 scale } def\n");
  fprintf(fp,"\n");
  fprintf(fp,"%%------------Centered Dash Patterns  CookBook p.141 -------\n");
  fprintf(fp,"\n");
  fprintf(fp,"/centerdash\n");
  fprintf(fp,"{ /pattern exch def\n");
  fprintf(fp,"  /pathlen pathlength def\n");
  fprintf(fp,"  /patternlength 0 def\n");
  fprintf(fp,"  pattern\n");
  fprintf(fp,"  { patternlength add /patternlength exch def\n");
  fprintf(fp,"  } forall\n");
  fprintf(fp,"\n");
  fprintf(fp,"  pattern length 2 mod 0 ne\n");
  fprintf(fp,"   { /patternlength patternlength 2 mul def } if\n");
  fprintf(fp,"\n");
  fprintf(fp,"   /first pattern 0 get def\n");
  fprintf(fp,"\n");
  fprintf(fp,"   /last patternlength first sub def\n");
  fprintf(fp,"\n");
  fprintf(fp,"   /n pathlen last sub patternlength idiv def\n");
  fprintf(fp,"   /endpart pathlen patternlength n mul sub\n");
  fprintf(fp,"    last sub 2 div def\n");
  fprintf(fp,"\n");
  fprintf(fp,"   /offset first endpart sub def\n");
  fprintf(fp,"\n");
  fprintf(fp,"   pattern offset setdash\n");
  fprintf(fp,"   } def\n");
  fprintf(fp,"\n");
  fprintf(fp,"/pathlength\n");
  fprintf(fp,"{ flattenpath\n");
  fprintf(fp,"  /dist 0 def\n");
  fprintf(fp,"\n");
  fprintf(fp,"  { /yfirst exch def /xfirst exch def\n");
  fprintf(fp,"    /ymoveto yfirst def /xmoveto xfirst def }\n");
  fprintf(fp,"  { /ynext exch def /xnext exch def\n");
  fprintf(fp,"    /dist dist ynext yfirst sub dup mul\n");
  fprintf(fp,"    xnext xfirst sub dup mul add sqrt add def\n");
  fprintf(fp,"    /yfirst  ynext def /xfirst xnext def }\n");
  fprintf(fp,"    {}\n");
  fprintf(fp,"\n");
  fprintf(fp,"   {/ynext ymoveto def /xnext xmoveto def\n");
  fprintf(fp,"    /dist dist ynext yfirst sub dup mul\n");
  fprintf(fp,"      xnext xfirst sub dup mul add sqrt add def\n");
  fprintf(fp,"    /yfirst ynext def /xfirst xnext def}\n");
  fprintf(fp,"    pathforall\n");
  fprintf(fp,"    dist\n");
  fprintf(fp,"   } def\n");
  fprintf(fp,"%%-------- End of Pre definitions ------------------------\n");
  
  return;
}

void psplot::spaceInteger(int x1,int y1,int x2,int y2)
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

void psplot::spaceDouble(double x1,double y1,double x2,double y2)
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

void psplot::moveToInteger(int x,int y)
{
  cpx = x;
  cpy = y;

  return;
}

void psplot::moveToDouble(double x,double y)
{
  dcpx = x;
  dcpy = y;

  return;
}

void psplot::contToInteger(int x,int y)
{
  double x1,x2,y1,y2;

  x1 = xCoord( x );
  x2 = xCoord(cpx);
  y1 = yCoord( y );
  y2 = yCoord(cpy);

  cpx = x;
  cpy = y;

  DrawLine(x1,y1,x2,y2);

  return;
}

void psplot::contToDouble(double x,double y)
{
  double x1,x2,y1,y2;

  x1 = xCoord(x);
  y1 = yCoord(y);
  x2 = xCoord(dcpx);
  y2 = yCoord(dcpy);

  dcpx = x;
  dcpy = y;

  DrawLine(x1,y1,x2,y2);

  return;
}


////////////////////////////////////////////////////////
// peke
////////////////////////////////////////////////////////
void psplot::pekeToInteger(int x,int y)
{
  double x1,y1;

    x1 = xCoord(x);
    y1 = yCoord(y);

    DrawPeke(x1,y1);

    return;
}

void psplot::pekeToDouble(double x,double y)
{
  double x1,y1;

  x1 = xCoord(x);
  y1 = yCoord(y);

  DrawPeke(x1,y1);

  return;
}

// inner functions,  these funtions really write ps data to files.

void psplot::DrawLine(double x1,double y1,double x2,double y2)
{
  fprintf(fp,"%5.1f %5.1f MT  %5.1f %5.1f LT ST\n",x1,y1,x2,y2);
  return;
}

// symbol
void psplot::symbolInteger(int x,int y, const char *mesg)
{
  double x1,y1;

  //  dcpx = x;
  //  dcpy = y;

  x1 = xCoord(x);
  y1 = yCoord(y);

  WriteString(x1,y1,mesg);

  return;
}

void psplot::symbolDouble(double x,double y, const char *mesg)
{
  double x1,y1;

  //  dcpx = x;
  //  dcpy = y;

  x1 = xCoord(x);
  y1 = yCoord(y);

  WriteString(x1,y1,mesg);

  return;
}

void psplot::WriteString(double x,double y,const char *mesg)
{
  fprintf(fp,"N %5.1f %5.1f MT (\n",x,y);

  while(*mesg) {
    switch(*mesg) {
    case '(':
    case ')':
    case '\\':
      fprintf(fp,"\\%c",*mesg);
      break;
    default:
      fprintf(fp,"%c",*mesg);
      break;
    }
    mesg++;
  }

  fprintf(fp,") show\n");

  return;
}



void psplot::DrawPeke(double a,double b)
{
  fprintf(fp,"N %5.1f %5.1f MT %5.1f %5.1f LT ST\n",
	  a-PSPLOT_PEKE_LEN,b-PSPLOT_PEKE_LEN,
	  a+PSPLOT_PEKE_LEN,b+PSPLOT_PEKE_LEN   );

  fprintf(fp,"N %5.1f %5.1f MT %5.1f %5.1f LT ST\n",
	    a-PSPLOT_PEKE_LEN,b+PSPLOT_PEKE_LEN,
	    a+PSPLOT_PEKE_LEN,b-PSPLOT_PEKE_LEN );
  return;
}


//
void psplot::psErase(void)
{
  fprintf(fp,"showpage\n");
  currentPageNo++;
  fprintf(fp,"%%-  Page %d  -\n",currentPageNo);
  return;
}


void psplot::closeFile(void)
{
  fprintf(fp,"showpage\n");
  fclose(fp);
  fp = 0;

  return;
}


double psplot::xCoord(double x)
{
  double x1;
  x1 = ( x   - dspx0) * (double)xlen / dspdx;
  x1 = x1 + PSPLOT_GX;

  return(x1);
}

double psplot::yCoord(double y)
{
  double y1;

  y1 = ( y   - dspy0) * (double)ylen / dspdy;
  y1 = y1 + PSPLOT_GY;

  return(y1);
}

double psplot::xCoord(int x)
{
  double x1;

  x1 = ( x  - spx0) * xlen / spdx;
  x1 = x1 + PSPLOT_GX;

  return(x1);
}

double psplot::yCoord(int y)
{
  double y1;
  
  y1 = ( y  - spy0) * ylen / spdy;
  y1 = y1 + PSPLOT_GY;

  return(y1);
}
