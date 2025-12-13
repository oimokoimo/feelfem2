/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MainOperation.cpp
 *  Date     : 2000/04/25
 *  Modified : 2000/04/25
 *  
 *  Purpose  : Functions on Main class
 *  
 */

#include "Main.hpp"

Main::Main()
{
  // do nothing;
  return;
}



Main::~Main()
{
  // do nothing;
  return;
}



void Main::AddScheme( Scheme *schemePtr)
{
  schemePtrLst.addlast(schemePtr);

  return;
}
