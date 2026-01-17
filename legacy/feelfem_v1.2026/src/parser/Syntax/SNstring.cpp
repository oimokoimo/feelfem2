/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNstring.cpp
 *  Date     : 2001/02/19
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNstring.hpp"

SNstring::SNstring(char *ptr) :
  SNunit("string",SN_STRING) 
{
  str=ptr;
  return;
}

SNstring::~SNstring()
{
  str.~string();
  return;
}

SNstring::operator const char * () const
{
   return ((const char *)str);
}
