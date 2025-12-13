/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNweqTerm_CHECK.cpp
 *  Date     : 2002/01/29
 *  Modified : 
 *  
 *  Purpose  : check functions
 *  
 */

#include "SNweqTerm.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"
#include "Configure.hpp"    // for boundary etype from regional etype

#include "Quadrature.hpp"

#include "../../check/check_funcs.hpp"


int SNweqTerm::VariableDefinedCheck_Regional(list <string>&testFuncLst)
{
  if(integralType ==TYPE_BOUNDARY_INTEGRAND) {
    return(0);
  }

  int ret;

  ret = integrandExprPtr->checkDefinedVariable_RegionalSN((SNunit *)this,
							  testFuncLst);
  return(ret);
}


int SNweqTerm::VariableDefinedCheck_Boundary(list <string>&testFuncLst,
					     SNsolveNeumann *snSNPtr,
					     list <string>&apLst)
{
  if(integralType != TYPE_BOUNDARY_INTEGRAND) {
    return(0);
  }

  int ret;

  ret = integrandExprPtr->checkDefinedVariable_BoundarySN((SNunit *)this,
							  testFuncLst,
							  snSNPtr    ,
							  apLst          );
  return(ret);
}

int SNweqTerm::EtypeConsistencyCheck(int refEtype,
				     list <string>&testFuncLst,
				     list <string>&nVarLst)
{
  int ret;
  
  if(integralType == TYPE_REGIONAL_INTEGRAND) {
    ret = integrandExprPtr->EtypeConsistencyCheckSN((SNunit *)this,refEtype,
						    testFuncLst);
  }
  else {

    // only check  if neumann data is existing.
    if(nVarLst.getNumberOfElements() != 0) {
      ret = integrandExprPtr->EtypeConsistencyCheckSN((SNunit *)this,refEtype,
						      testFuncLst,
						      nVarLst);
    }
  }
  return(ret);
}

int SNweqTerm::QuadratureConsistencyCheck(int refEtype,
					  list <string>&testFuncLst,
					  Quadrature *regionQuadPtr)
{
  int errors;
  errors = 0;
  
  if(quadratureType == TYPE_QUADRATURE_DEFAULT) {

    // check ewise-quad for without term-quadrature specification term
    errors += integrandExprPtr->
      checkQuadratureConsistency_RegionalSN((SNunit*)this,
					    testFuncLst,
					    regionQuadPtr);
    
    
    return(errors);
  }

  // quadrature is defined?
  if(feelfemobj.IsDefinedQuadratureName( quadratureMethod ) == NO) {
    SystemErrorAStrA((SNunit *)this,"quadrature '",quadratureMethod,
		     "' is not defined.");
    errors++;
  }
  else {
    Quadrature *qPtr = feelfemobj.GetQuadraturePtrByName(quadratureMethod);

    // check quadrature
    if(integralType == TYPE_REGIONAL_INTEGRAND) {
      if(qPtr->GetEtype() != refEtype) {
	SystemErrorAStrA((SNunit *)this,"quadrature '",quadratureMethod,
			 "' is a wrong element type.");
	errors++;
      }
    }
    else {
      // boundary quadrature
      if(qPtr->GetEtype() != feelfemconf.GetBoundaryEtypeFromEtype(refEtype)){
	SystemErrorAStrA((SNunit *)this,"quadrature '",quadratureMethod,
			 "' is a wrong boundary element type.");
	errors++;
      }
    }

    // ewise-quad variable check
    if( integralType == TYPE_BOUNDARY_INTEGRAND) {
      ;
    }
    else {
      // TYPE_REGIONAL_INTEGRAND 
      errors+=
	integrandExprPtr->
	checkQuadratureConsistency_RegionalSN((SNunit*)this,
					      testFuncLst,
					      qPtr);
    }
  }
  return(errors);
}
