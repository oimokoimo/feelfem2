/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNoutput_CHECK.cpp
 *  Date     : 2002/04/23 (BCN)
 *  Modified : 
 *  
 *  Purpose  : check output program
 *  
 */

#include "SNoutput.hpp"
#include "Expression.hpp"
#include "Variable.hpp"
#include "Quadrature.hpp"
#include "Object.hpp"
#include "feelfuncs.hpp"

#include "../../check/check_funcs.hpp"

int SNoutput::checkIdentifierWellDefined(void)
{
  int ret=0;

  int scalars     = 0;
  int ewises      = 0;
  int fems        = 0;
  int vfems       = 0;
  int coordinates = 0;

  Quadrature *qPtr= 0;

  // make Expression array
  components = snIdentifierlistPtr->GetNumberOfElements();
  for(int i=0;i<components;i++) {
    SNname *snnPtr;

    snnPtr     = (*snIdentifierlistPtr)[i];
    string str = snnPtr->GetName();

    if(isCoordinate( str )) {
      coordinates++;
      continue;
    }
    
    if(isDefinedFEMVariable(str)) {
      fems++;
      continue;
    }

    if(isDefinedEWISEVariable(str)) {
      Variable *eVarPtr;
      eVarPtr = feelfemobj.GetVariablePtrWithName( str );
      
      if(eVarPtr->GetEwiseType() != EWISE_TYPE_GAUSSPOINT ) {
	SystemErrorA(this,"Only gauss point ewise can be used.");
	ret++;
      }
      else {
	ewises++;
	if(ewises == 1) {   // first ewise quad variable
	  qPtr = eVarPtr->GetQuadraturePtr();
	}
	else {
	  if(qPtr != eVarPtr->GetQuadraturePtr()) {
	    ret++;
	    SystemErrorAStrA(this,"ewise variable ",
			     str," has different quadrautre attribute.");
	  }
	}
	
      }
      
      continue;
    }

    if(isDefinedScalarVariable(str)) {
      scalars++;
      continue;
    }

    // VFEM is not supported now.

    SystemErrorStrA(this,str," is not defined or not valid variable.");
    ret++;
  }

  if(ret != 0) return (ret);


  if(coordinates > 0 && ewises > 0) {
    SystemErrorA(this,"Coordinates cannot be used with ewise variables.");
    ret++;
  }
  
  if(ewises > 0 && fems > 0) {
    SystemErrorA(this,"fem and ewise variables cannot be used simultaneously.");
  }

  // variable defined check

  return(ret);

}

  //int SNoutput::checkValidExpr(void)
  //{
  //  cerr << "now coding,,, int SNoutput::checkValidExpr(void)\n";
  //
  //  return(0);
  //}

int SNoutput::checkOptions(void)
{
  
  // option check

  return(0);
}

