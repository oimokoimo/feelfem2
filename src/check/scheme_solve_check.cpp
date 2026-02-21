/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : scheme_solve_check.cpp
 *  Date     : 2001/07/27
 *  Modified : 2002/01/30
 *  
 *  Purpose  : solve block check
 *  
 *  
 *  functions: check_sn_solve         check number of unknowns and test funcs.
 *             check_solver_name
 *  
 *  
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 *  
 */

// main routine scheme_solve_check() is at the bottom.


#include "feelfem.hpp"              // for command options
#include "check_funcs.hpp"          // for error messages

#include "parseExternals.hpp"       // for parser  treesn


#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNsolve.hpp"


// check unknowns and test function declaration
static int check_sn_solve( SNsolve *snSolvePtr )
{
  int ret,errors;

  errors = 0;

  // check the number of the equation and unknowns are the same
  ret = snSolvePtr->setNumberOfUnknowns();
  if(ret != 0) {
    SystemErrorA(snSolvePtr,"mismatch numbers in unknowns and test functions.");
    errors++;
  }

  // check the number of weak equations and unknowns
  ret = snSolvePtr->isConsistentNumberOfEqs();
  if(ret != YES) {
    SystemErrorA(snSolvePtr,"mismatch number in equations and unknowns.");
    errors++;
  }  
  
  return(errors);
}

static int check_solve_ndata_exists( SNsolve *snSolvePtr )
{
  int errors = 0;
  int ret = snSolvePtr->CheckNdataExists();
  //  0  No error
  //  1  some weak form has no boundary term
  //  2  no nbc: while there is bounary term
  if(ret==1) {
    SystemErrorA(snSolvePtr,"Some weak forms have no boundary terms.");
    errors++;
  }

  if(ret==2) {
    SystemErrorA(snSolvePtr,"Boundary integrand exists, but no neumann data specified.");
    errors++;
  }
  return(ret);
}


static int check_parametric_name( SNsolve *snSolvePtr )
{
  int errors;
  
  NOTE("routine check_parametric_name");

  errors = 0;
  errors = snSolvePtr->ParametricNameCheck();

  return(errors);
}
  

static int check_solver_name( SNsolve *snSolvePtr )
{
  int ret;
  int errors;

  errors = 0;

  NOTE("routine check_solver_name");

  // Solver name defined test 
  ret = snSolvePtr->SolverNameCheck();
  if(ret == NO) {
    errors++;
    
    // following 1 means to write solverName in NameNO series.
    SystemErrorNameNOA((SNunit *)snSolvePtr, 1," is not valid solver name.");
    return ( errors );
  }


  // Match test
  ret = snSolvePtr->PM_LIBmatchCheck();
  if(ret == NO) {
    errors++;
    
    // following 1 means to write solverName in NameNO series.
    SystemErrorNameNOA((SNunit *)snSolvePtr, 1, " cannot be used in the current ProgramModel.");
    return(errors);

  }

  return(errors);
}


static int check_solve_variable( SNsolve *snSolvePtr )
{
  int errors;

  NOTE("routine check_solve_variable");

  // unknown, test function, weak integrand, dirichlet conditions
  errors  = snSolvePtr->VariableDefinedCheck();

  return(errors);
}

static int check_solve_etype(SNsolve *snSolvePtr)
{
  int errors;

  NOTE("routine check_solve_etype");

  errors = snSolvePtr->EtypeConsistencyCheck();

  return(errors);
}
  


static int check_solve_quadrature(SNsolve *snSolvePtr)
{
  int errors;
  errors = 0;

  NOTE("routine check_solve_quadrature");

  // SUBSOLVE 
  errors = snSolvePtr->QuadratureConsistencyCheck();

  return(errors);
}




////////////////////////////////////////////////////////////
int scheme_solve_check(list <void *>&parseSchemeLst)
{
  int ret,errors;

  errors = 0;

  listIterator <void *>itr(parseSchemeLst);
  for(itr.init(); !itr ; ++itr) {

    SNunit *uPtr =(SNunit *)itr();

    SNsolve *snSolvePtr;

    switch(uPtr->GetType()) {
    case SN_SOLVE:

      snSolvePtr = (SNsolve *)itr();

      snSolvePtr->checkInit();             // set program model name

      ret = check_sn_solve( snSolvePtr );  // function in the top
      errors += ret;

      ret = check_solver_name( snSolvePtr ); // check solver name matching
      errors += ret;

      ret = check_solve_ndata_exists( snSolvePtr );
      errors += ret;
      if(ret != 0) continue;

      ret = check_solve_variable( snSolvePtr ); // check variables are defined
      errors += ret;

      if(ret == 0) {  // check only if all variables are defined
	ret = check_solve_etype( snSolvePtr ); // check all etype consistentcy
	errors += ret;
	
	// dependent on check_solve_etype (refEtype)
	ret = check_solve_quadrature( snSolvePtr ); // check quadrature
	errors += ret;

	// etype dependent (refEtype is used.)
	ret = check_parametric_name( snSolvePtr );   // check paametric element
	errors += ret;

      }
      break;

    default:
      break;
    }
  }
  return(errors);
}
