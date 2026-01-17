/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Label.cpp
 *  Date     : 2002/07/19 (aist)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "Label.hpp"

int Label::labels = 0;

Label::Label(const char *nm)
{
  name    = nm;

  labels++;
  labelNo = labels;

  return;
}

Label::~Label()
{
  // do nothing now
  return;
}

int Label::GetLabelNo(void)
{
  return( labelNo );
}

const char *Label::GetName(void)
{
  return ( (const char *)name);

}
