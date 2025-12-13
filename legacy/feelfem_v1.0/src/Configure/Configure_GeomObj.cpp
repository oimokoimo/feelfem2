/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Configure_GeomObj.cpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  : GeometryObject related store method
 *  
 */
#include "feeldef.hpp"
#include "Configure.hpp"
#include "pairClass.hpp"

void Configure::StoreMesherCode( char *nm, int n)
{
  StrIntPair *ptr = new StrIntPair(nm,n);
  mesherNameLst.add( ptr );

  return;
}

int Configure::IsValidMesherName(string &nm)
{
  StrIntPair *ptr = new StrIntPair(nm, DUMMY_CODE);

  if(mesherNameLst.includes(ptr)) return(YES);
  
  return(NO);
}

int Configure::GetMesherCodeByName( string &name)
{
  StrIntPair *ptr =  new StrIntPair( name, DUMMY_CODE);
  
  int pos = mesherNameLst.getPosition(ptr);

  ptr->~StrIntPair();

  ptr = mesherNameLst.getNthElement( pos );
  
  return( ptr->getCode() );
}


