/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNlabel_InfoGenerate.cpp
 *  Date     : 2002/07/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNlabel.hpp"
#include "Label.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"

int SNlabel::InfoGenerate(void)
{
  labelPtr = new Label(val);
  feelfemobj.StoreLabelPtr(labelPtr);     

  return(0);
}
