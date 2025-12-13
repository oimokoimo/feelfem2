/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ginac_funcs.hpp
 *  Date     : 2001/03/19
 *  Modified : 
 *  
 *  Purpose  : no string must appear here.
 *  
 */


void setGinacExprToCharBuf(char *buf,int bufsiz);  // for MakeBoundaryElement_*

void setExprGinacEvaluate(char *);
void subsExprGinacEvaluate(int,char *);
void subsExprGinacEvaluate(int,double);
int  isExprGinacNumeric(void);
double getDoubleExprGinac(void);

