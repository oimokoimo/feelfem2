/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : VariableSetParameters.cpp
 *  Date     : 2001/03/29
 *  Modified : 
 *  
 *  Purpose  : Variable::SetParameters()
 *  
 *                Set Element *, Quadrature * pointers,
 *  important->   Set elementFreedom,ewiseType !!!!!
 *  
 */

#include "feelfuncs.hpp"
#include "Variable.hpp"
#include "Object.hpp"

void Variable::SetParameters(void)
{

  switch(varType) {

  case VAR_FEM:
    ePtr = feelfemobj.GetElementPtrByName( functionName );
    if(ePtr == NULL) {
      cerr << "Element type " << functionName << " not exist.\n";
      abortExit("SetParameters for FEM.(Solve/VariableSetParameters.cpp)");
    }
    elementFreedom = ePtr->GetElementFreedom();
    break;

  case VAR_EWISE:
    elementFreedom = 1;
    ewiseType = EWISE_TYPE_MATERIAL;
    break;

  case VAR_EWISE_A:
    ePtr = feelfemobj.GetElementPtrByName( functionName );
    if(ePtr != NULL) {
      ewiseType = EWISE_TYPE_INTERPOLATION;
      qPtr = NULL;
      elementFreedom = ePtr->GetElementFreedom();
    }
    else {
      qPtr = feelfemobj.GetQuadraturePtrByName( functionName );
      if(qPtr != NULL) {
	ePtr = NULL;
	ewiseType = EWISE_TYPE_GAUSSPOINT;
	elementFreedom = qPtr->GetQuadraturePoints();
      }
      else {
	cerr << "cannot find "<< functionName << " in quadraturePtrbyname\n";
      }
    }
    if(ePtr == NULL && qPtr == NULL) {
      cerr << "functionName = " << functionName << endl;
      abortExit("VariableSetParameters for EWISE_A failed.(Solve/VairableSetParameters.cpp)");
    }
    break;

  default:
    abortExit("VariableSetParameters.cpp is called with an illegal varType");
  }

  return;
}

