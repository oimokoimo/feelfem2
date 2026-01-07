/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Node_print.cpp
 *  Date     : 2002/02/01
 *  Modified : 
 *  
 *  Purpose  : debug routine
 *  
 */

#include <iostream.h>
#include "Node.hpp"

void Node::print(ostream &ost)
{
  ost << "(" << xi ;
  if(dimension >1) {
    ost << "," << eta;
  }
  if(dimension >2) {
    ost << "," << zeta;
  }
  ost << ") [eval=";

  ost << eval() << "]";
  
  return;
}
