/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNassignment_CHECK.cpp
 *  Date     : 2002/04/15 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feeldef.hpp"
#include "feelfuncs.hpp"

#include "Object.hpp"
#include "GeometryObject.hpp"

#include "SNassignment.hpp"
#include "Expression.hpp"
#include "Variable.hpp"

#include "../../check/check_funcs.hpp"

int SNassignment::checkGeometryIsValid(void)
{
  int errors = 0;

  // integral(), bintegral() check extention (2002/11/08)
  // confirm there is only one ElementType
  if(placeFlag      == SN_ASSIGNMENT_NORMAL &&
     ( integralType == ASSIGNMENT_TYPE_INTEGRAL ||
       integralType == ASSIGNMENT_TYPE_BINTEGRAL   ) ) {

    if ( feelfemgeomobj.GetNumberOfEtypes() == 0) {
      SystemErrorA(this,"integral used, but no ElementEtype statement.");
      errors++;
      return(errors);
    }

    if ( feelfemgeomobj.GetNumberOfEtypes() == 1) {
      
      if( integralType == ASSIGNMENT_TYPE_INTEGRAL) {
	refEtypeIntegral = feelfemgeomobj.GetRegionalEtype();
      }
      else {
	assert(1==0);
      }
      return(errors);
    }
    
    errors++;
    SystemErrorA(this,
		 "Integration operator is used, but no geometry specified.");

    return(errors);
  }


  if(placeFlag == SN_ASSIGNMENT_NORMAL) return(errors);

  int numberOfPlaces = placeLst->GetNumberOfElements();
  int varType  = feelfemobj.GetVariableTypeWithName(leftVarName);


  // integral and bintegrals max,min operators
  if(integralType != ASSIGNMENT_TYPE_ORIGINAL) {
    if(varType != VAR_DOUBLE) {
      SystemErrorA(this,"Left variable must be double var.");
      errors++;
      return(errors);
    }

    // place criteria must be here
    return(0);

  }


  // scalara variable can be assigned at one point.
  if(varType == VAR_INT || varType == VAR_DOUBLE) {
    if(numberOfPlaces != 1) {  // 0 means where, but it is also not allowed
      SystemErrorA(this,"Try to assign a scalar value at plural points.");
      errors++;
      return(errors);
    }
  }

  // is defined geometry name?
  for(int i=0;i<numberOfPlaces ; i++) {
    string nm = (*placeLst)[i]->GetName();

    if( feelfemgeomobj.IsUsedName(nm) == NO) {
      SystemErrorStrA(this,nm," is not defined as a geometry.");
      errors++;
      continue;
    }

    int geomType = feelfemgeomobj.GetGeomObjTypeByName( nm );
    if( feelfemgeomobj.IsValidAssignPlace( geomType, placeFlag) != YES) {
      errors++;
      switch(placeFlag) {
      case SN_ASSIGNMENT_AT:
	SystemErrorAStr(this,"'at' cannot be used for ",nm);
	break;
	
      case SN_ASSIGNMENT_ON:
	SystemErrorAStr(this,"'on' cannot be used for ",nm);
	break;
	
      case SN_ASSIGNMENT_IN:
	SystemErrorAStr(this,"'in' cannot be used for ",nm);
	break;

      default:
	assert(1==0);  //SN_ASSIGNMENT_WHERE must not come here...
      }
    }

    if( feelfemgeomobj.IsValidAssignmentGeometry( varType,
						  geomType ) == YES) {
      continue;
    }
    errors++;
    SystemErrorStrA(this,nm, " is not a valid Assignment geometry type.");
  }
  return(errors);
}

int SNassignment::checkExprWellDefined(void)
{
  int ret;

  SNunit *suPtr = this;

  ret  = 0;

  // left hand side is defined?
  if( !isDefinedFEMVariable(leftVarName) ) {       // FEM

    if( !isDefinedEWISEVariable(leftVarName) ) {   // EWISE

      if( isDefinedScalarVariable(leftVarName) ) {        // scalar


	// confirm not constant
	Variable *vPtr = feelfemobj.GetVariablePtrWithName( leftVarName );
	if(vPtr->GetType() == VAR_CONST) {
	  SystemErrorNameA(this," is constant, cannot change.");
	  ret++;
	}
      }
      else {   // here material or not defined variable

	if( isDefinedMaterialVariable(leftVarName) ) { // MATERIAL
	  SystemErrorNameA(this," is material variable, cannot assign here.");
	  ret++;
	}
	else { // not defined.
	
	  SystemErrorNameA(this," is not defined.");
	  ret++;
	}
      }
    }
  }

  // defined expression elements?
  ret += exprPtr->checkDefinedVariableSN(suPtr);
  ret += exprPtr->checkDefinedFunctionSN(suPtr);


  // integral and bintegrals max,min operators, only double var is possible
  if(ret == 0) {
    int varType = feelfemobj.GetVariableTypeWithName(leftVarName);

    // if functional, left var must be double scalar var
    if(integralType != ASSIGNMENT_TYPE_ORIGINAL) {

      if(varType != VAR_DOUBLE) {
	SystemErrorA(this,"Left variable must be double var.");
	ret++;
      }
    }
  }
  return(ret);

}

int SNassignment::checkValidQuadrature()
{
  int ret = 0;
  Variable *vPtr = feelfemobj.GetVariablePtrWithName( leftVarName );

  if(vPtr->GetType()==VAR_DOUBLE && integralType==ASSIGNMENT_TYPE_INTEGRAL) {
    if(integrationMethod == DEFAULT_STRING) {
      return(ret);
    }

    if(! feelfemobj.IsDefinedQuadratureName( integrationMethod)) {
      SystemErrorStrA(this,integrationMethod," is not defined.");
      ret++;
      return(ret);
    }

    Quadrature *qPtr = feelfemobj.GetQuadraturePtrByName( integrationMethod );

    if(! feelfemgeomobj.IsOnlyOneEtype()) return(0);// error message out other

    if(qPtr->GetEtype() != feelfemgeomobj.GetRegionalEtype()) {
      SystemErrorStrA(this,integrationMethod," is not for this element type.");
      ret++;
      return(ret);
    }

  }
  if(vPtr->GetType()==VAR_DOUBLE && integralType==ASSIGNMENT_TYPE_BINTEGRAL) {
    cerr << "NOT CHECK yet" << endl;
    assert(1==0);
  }

  return(ret);
}


int SNassignment::checkValidExpr()
{
  int ret = 0;
  Variable *vPtr = feelfemobj.GetVariablePtrWithName( leftVarName );

  switch(vPtr->GetType()) {
    
  case VAR_FEM:
    ret = checkValidExpr_FEM();
    break;


  case VAR_EWISE:
    ret = checkValidExpr_EWISE();
    break;

  case VAR_EWISE_A:
    ret = checkValidExpr_EWISE_A();
    break;

  case VAR_INT:
    ret = checkValidExpr_INT();
    break;

  case VAR_DOUBLE:
    if(integralType == ASSIGNMENT_TYPE_ORIGINAL) {
      ret = checkValidExpr_DOUBLE();
    }
    else {
      switch(integralType) {
      case ASSIGNMENT_TYPE_INTEGRAL:

	ret = checkValidExpr_INTEGRAL();
	break;
	
      default:
	cerr << "Only integral is now supported." << endl;
	assert(1==0);
      }
    }
    break;

  default:
    abortExit("inner err(SNassignment_CHECK validExprCheck");
  }
  return(ret);
}
