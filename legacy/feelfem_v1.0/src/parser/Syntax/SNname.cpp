/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNname.cpp
 *  Date     : 2001/02/19
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNname.hpp"

SNname::SNname(char *ptr)
{
  name=ptr;
  return;
}

SNname::~SNname()
{
  name.~string();
  return;
}

SNname::operator const char * () const
{
   return ((const char *)name);
}
