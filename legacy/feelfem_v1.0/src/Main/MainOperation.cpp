/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MainOperation.cpp
 *  Date     : 2000/04/25
 *  Modified : 2000/04/25
 *  
 *  Purpose  : Functions on Main class
 *  
 */

#include "Main.hpp"
#include "Procedure.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"

Main::Main()
{
  programModelType = feelfemproc.GetProgramModel();

  // make variable list
  feelfemobj.MakeVarLstForMain( this );

  return;
}



Main::~Main()
{
  // do nothing;
  return;
}


void Main::AddVariablePtr( Variable *vPtr )
{
  if(mainVarPtrLst.includes(vPtr)) return;

  mainVarPtrLst.add(vPtr);
 
  return;
}


//void Main::AddScheme( Scheme *schemePtr)
//{
// schemePtrLst.addlast(schemePtr);
//
//  return;
//}
