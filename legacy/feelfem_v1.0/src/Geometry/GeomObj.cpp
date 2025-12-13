/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GeomObj.hpp
 *  Date     : 2002/03/18
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <assert.h>
#include <iostream.h>

#include "feeldef.hpp"

#include "GeomObj.hpp"

GeomObj::GeomObj(int n,char *nm)
{
  geomType = n;          // geomObj is a container
  name     = nm;

  geomObjNo++;       // geomObjNo is statinc int GeomObj::geomObjNo;
  geomNo = geomObjNo;

  dFlag  = NO;
  nFlag  = NO;
  
  return;
}

GeomObj::~GeomObj()
{
  return;
}

int GeomObj::IsNameIs( string &nm)
{
  if(name == nm) return(YES);

  return(NO);
}

int GeomObj::GetType( void )
{
  return(geomType);
}
   
void GeomObj::SetDirichletFlag()
{
  dFlag = YES;
  return;
}

void GeomObj::SetNeumannFlag()
{
  nFlag = YES;
  return;
}

int GeomObj::GetDirichletFlag()
{
  return(dFlag);
}

int GeomObj::GetNeumannFlag()
{
  return(nFlag);
}

int GeomObj::GetPropertyNo(void)
{
  cerr << "It must not be called." << endl;
  assert(1==0);
  return(0);
}

