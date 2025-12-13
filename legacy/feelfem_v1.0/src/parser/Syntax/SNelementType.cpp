/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementType.cpp
 *  Date     : 2002/11/02
 *  Modified : 
 *  
 *  Purpose  : element type parser
 *  
 */

#include "feeldef.hpp"
#include "SNelementType.hpp"

SNelementType::SNelementType( SNidentifierlist *ptr) 
  :            SNunit("elementType",SN_ELEMENTTYPE) 
{ 
  etypeIdentifierLst = ptr;
  return;
}

