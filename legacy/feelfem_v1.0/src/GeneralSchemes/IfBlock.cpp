/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : IfBlock.cpp
 *  Date     : 2002/07/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "IfBlock.hpp"
#include "Label.hpp"
#include "Object.hpp"
#include "feelfuncs.hpp"

IfBlock::IfBlock(const char *nm) 
{
  gotoLabel = nm;
  return;
}

IfBlock::~IfBlock() 
{
  // do nothing;
  return;
}

Label *IfBlock::GetLabelPtr(void)
{
  Label *ret;
  ret = feelfemobj.GetLabelPtrByName( gotoLabel );
  
  return(ret);
}

