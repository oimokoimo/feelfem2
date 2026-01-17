/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : FiniteElement.hpp
 *  Date     : 2002/01/02
 *  Modified : 
 *  
 *  Purpose  : Function definitions
 *  
 */

#ifndef FEM_CLASS_FINITEELEMENT
#define FEM_CLASS_FINITEELEMENT

double evalNodePoint(void);
double evalNodeLine(double);
double evalNodeTri(double,double);
double evalNodeRect(double,double);
double evalNodeTetra(double,double,double);
double evalNodeCube(double,double,double);

#endif
