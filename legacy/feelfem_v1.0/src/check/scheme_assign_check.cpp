/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : shcme_assign_check.cpp
 *  Date     : 2002/04/15 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feeldef.hpp"
#include "feelfem.hpp"              // NOTE()
#include "check_funcs.hpp"
#include "parseExternals.hpp"       // for parser  trees

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNassignment.hpp"

static int check_assign_well_defined( SNassignment *aPtr )
{
  int ret;

  // variables are all defined or not.
  ret = aPtr->checkExprWellDefined();

  return(ret);
}

static int check_assign_valid_geom( SNassignment *aPtr )
{
  int ret;
  
  ret = aPtr->checkGeometryIsValid();
  
  return(ret);
}

static int check_assign_valid_expr( SNassignment *aPtr )
{
  int ret;
  
  ret = aPtr->checkValidExpr();
  
  return(ret);
}

static int check_assign_valid_quadrature(SNassignment *aPtr)
{
  int ret;
  ret = aPtr->checkValidQuadrature();
  return(ret);
}


int scheme_assign_check(list <void *>&parseSchemeLst)
{
  int ret,errors;

  errors = 0;

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {

    SNunit *suPtr = (SNunit*)itr();

    switch(suPtr->GetType()) {


    case SN_ASSIGNMENT:


      // confirm all variables appear in expression is defined

      NOTE("check_assign_well_defined(scheme_assign_check)");
      ret = check_assign_well_defined( (SNassignment *)suPtr);
      errors += ret;

      // if all variables are defined, check its validity
      if(ret == 0) {

	// geometry validity
	NOTE("check_assign_valid_geom(scheme_assign_check)");
	ret = check_assign_valid_geom( (SNassignment *)suPtr);
	errors += ret;

	if(ret == 0) {
	  // expression validity

	  NOTE("check_assign_valid_expr(scheme_assign_check)");
	  errors += check_assign_valid_expr( (SNassignment *)suPtr);
	}
      }

      // integral, and bintegral assignment
      errors+= check_assign_valid_quadrature((SNassignment *)suPtr); 

      break;


    default:
      break;
    }
  }
  return(errors);
}
