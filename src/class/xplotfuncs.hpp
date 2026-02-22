/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Xplotfuncs.hpp
 *  Date     : 2001/04/10
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

class  xplot;
class  psplot;
extern int    xplotScreens;
extern xplot *activeXplotPtr;
extern psplot *activePsplotPtr;

//open window
void  openpl(void);
void  openpl(int,int);                        // with window size
void  openplps(const char *);

// close 
void closepl(void);

// wait
void  xwait(void);

// scale
void  space(int,int,int,int);
void fspace(double,double,double,double);

// drawing line
void  line(int,int,int,int);
void fline(double,double,double,double);
void  move(int,int);
void fmove(double,double);
void  cont(int,int);
void fcont(double,double);

// drawing peke mark
void  peke(int,int);
void fpeke(double,double);

// drawing character
void symbol(int,int,const char *);
void fsymbol(double,double,const char *);
