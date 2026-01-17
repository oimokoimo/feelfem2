/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNunit.cpp
 *  Date     : 2001/12/21
 *  Modified : 
 *  
 *  Purpose  : for virtual print function,  why = 0; ???
 *  
 */

#include <iostream.h>
#include "SNunit.hpp"

void SNunit::print(ostream &ost)
{
  ost << "VIRTUAL FUNCTION SNunit::print is called.\n";
}
