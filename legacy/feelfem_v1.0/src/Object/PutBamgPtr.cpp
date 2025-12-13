/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PutBamgPtr.cpp
 *  Date     : 2001/04/06
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "Object.hpp"
#include "Bamg.hpp"

void Object::PutBamgPtr(Bamg *ptr)
{
  bamgPtr = ptr;
  return;
}

