/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Expression_Infogenerate.cpp
 *  Date     : 2002/01/31
 *  Modified : 
 *  
 *  Purpose  : make solvePtr
 *  
 */
#include <cassert>

#include "Expression.hpp"

#include "../check/check_funcs.hpp"  // isCoordinate, etc.

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "Object.hpp"
#include "Variable.hpp"

#include "SolveElement.hpp"
#include "Neumann.hpp"
#include "Dirichlet.hpp"

#include "Assign.hpp"

#include "orderedPtrList.hpp"

void Expression::MakeVariablePtr( orderedPtrList <Variable *>&vPtrLst)  //uniq
{
  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str)  ) continue;  // in check/is

    Variable *vPtr;

    vPtr = feelfemobj.GetVariablePtrWithName( str );
    
    if( !vPtrLst.includes(vPtr)) {      // uniq
      vPtrLst.add(vPtr);
    }
  }
  return;
}

void Expression::AddVariablePtr_Regional(SolveElement *sePtr,
					list<string>&tLst    )

  // tLst contains test function symbols
{
  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str)  ) continue;  // in check/is
    if( tLst.includes(str) ) continue;  // test function

    Variable *vPtr;

    vPtr = feelfemobj.GetVariablePtrWithName( str );
    sePtr->AddVariablePtr_uniq_exceptUnknown( vPtr );
  }
  return;
}

void Expression::AddVariablePtr_Boundary(Neumann *nPtr,
					 list<string>&tLst    ,
					 list<string>&nTVarLst)
  // tLst contains test function symbols
{
  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if(isCoordinateX(str)) {
      nPtr->UseX();
      continue;
    }
    if(isCoordinateY(str)) {
      nPtr->UseY();
      continue;
    }
    if(isCoordinateZ(str)) {
      nPtr->UseZ();
      continue;
    }

    // nx
    if( isSystemNX(str)) {
      nPtr->UseNX();
      continue;
    }

    // ny
    if( isSystemNY(str)) {
      nPtr->UseNY();
      continue;
    }

    // nz
    if( isSystemNZ(str)) {
      nPtr->UseNZ();
      continue;
    }

    if( tLst.includes(str)    ) continue; // test function
    if( nTVarLst.includes(str)) continue; // neumann temporary variable

    Variable *vPtr;

    vPtr = feelfemobj.GetVariablePtrWithName( str );
    nPtr ->AddVariablePtr( vPtr );        // already _uniq
  }
  return;
}


// check usage of system variables in neumann data (x,y,z,nx,ny,nz)
// called from SNsolveNeumannPairs_InfoGenerate.cpp
void Expression::CheckXYZNXNYNZ_Neumann(Neumann *nPtr)
{
  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if(isCoordinateX(str)) {
      nPtr->UseX();
      continue;
    }
    if(isCoordinateY(str)) {
      nPtr->UseY();
      continue;
    }
    if(isCoordinateZ(str)) {
      nPtr->UseZ();
      continue;
    }

    // nx
    if( isSystemNX(str)) {
      nPtr->UseNX();
      continue;
    }

    // ny
    if( isSystemNY(str)) {
      nPtr->UseNY();
      continue;
    }

    // nz
    if( isSystemNZ(str)) {
      nPtr->UseNZ();
      continue;
    }
  }
  return;
}

// check usage of system variables in assign expression (x,y,z,nx,ny,nz)
// called from SNassignment_InfoGenerate.cpp
void Expression::CheckXYZNXNYNZ_Assign(Assign *asPtr)
{
  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if(isCoordinateX(str)) {
      asPtr->UseX();
      continue;
    }
    if(isCoordinateY(str)) {
      asPtr->UseY();
      continue;
    }
    if(isCoordinateZ(str)) {
      asPtr->UseZ();
      continue;
    }

    // nx
    if( isSystemNX(str)) {
      asPtr->UseNX();
      continue;
    }

    // ny
    if( isSystemNY(str)) {
      asPtr->UseNY();
      continue;
    }

    // nz
    if( isSystemNZ(str)) {
      asPtr->UseNZ();
      continue;
    }
  }
  return;
}

void Expression::AddVariablePtr_Dirichlet(Dirichlet *dPtr)
{
  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str)     ) continue; // in check/is
    Variable *vPtr;

    vPtr = feelfemobj.GetVariablePtrWithName( str );
    dPtr ->AddVariablePtr( vPtr );        // already _uniq
  }
  return;
}

void Expression::AddVariablePtr_Neumann(Neumann *nPtr)
{
  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isSystemNX(str) ) {
      nPtr->UseNX();
      continue;
    }
    if( isSystemNY(str) ) {
      nPtr->UseNY();
      continue;
    }
    if( isSystemNZ(str) ) {
      nPtr->UseNZ();
      continue;
    }
    if( isCoordinateX(str)) {
      nPtr->UseX();
      continue;
    }
    if( isCoordinateY(str)) {
      nPtr->UseY();
      continue;
    }
    if( isCoordinateZ(str)) {
      nPtr->UseZ();
      continue;
    }

    Variable *vPtr;
    vPtr = feelfemobj.GetVariablePtrWithName( str );
    nPtr ->AddVariablePtr( vPtr );        // already _uniq
  }
  return;
}


int Expression::HasDifferential1st(void)
{
  int n = 0;

  listIterator <string> itr(functionLst);
  for(itr.init(); !itr ; ++itr) {
    string nm = itr();

    if( isDifferentialOperator1( nm ) ) {    // it has ! (02/09/19)
      n++;
    }
  }
  return(n);
}

void Expression::MakeUserFuncLst( list <string> &funcLst)
{

  listIterator <string> itr(functionLst);
  for(itr.init();  !itr ; ++itr) {

    string str = itr();
    if( feelfemobj.IsUsedUserFunctionName( str ) ) {
      if(!funcLst.includes(str)) {
	funcLst.add(str);
      }
    }
  }
  return;
}

