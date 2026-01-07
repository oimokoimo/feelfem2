/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Interpolation_print.cpp
 *  Date     : 2002/04/09
 *  Modified : 
 *  
 *  Purpose  : check write function
 *  
 */

#include <iostream.h>

#include "Interpolation.hpp"

void Interpolation::print(ostream &ost)
{
  nodePtr->print(ost);
  ost << " [" << type << "] ";
  ost << " : " << exprStr;

  return;
}
