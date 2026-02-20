/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNparametric.cpp
 *  Date     : 2002/07/11
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feeldef.hpp"
#include "SNparametric.hpp"

SNparametric::SNparametric(const char *nm) : SNunit("parametric",SN_PARAMETRIC) 
{ 
  parametricName = nm;
  elementShapeName = DEFAULT_STRING;
  return;
}

