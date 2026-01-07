/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EsetInfo.cpp
 *  Date     : 2002/03/01
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feeldef.hpp"
#include "EsetInfo.hpp"

EsetInfo::EsetInfo()
{
  dependencyFlag = NO;
  return;
}


EsetInfo::~EsetInfo()
{
  argStrLst.~list();
  return;
}

int EsetInfo::HasDependency()
{
  return(dependencyFlag);
}

list <string>&EsetInfo::GetArgStrList(void)
{
  return( argStrLst );
}


