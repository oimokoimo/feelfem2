/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolve_CHECK.cpp
 *  Date     : 2001/07/27
 *  Modified : 2002/03/22
 *  
 *  Purpose  : check and set parameters in SNsolve class
 *  
 *             2002/03/22 add check boundary geometry
 *  
 */

#include <iostream.h>
#include <assert.h>

#include "string.hpp"
#include "SNsolve.hpp"
#include "Procedure.hpp"
#include "Configure.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"
#include "SNname.hpp"

#include "../../check/check_funcs.hpp"

void SNsolve::errWrtNameNO(ostream &ost, int no)
{
  switch(no) {
  case 1:
    ost << solverName;
    break;

  default:
    ost << "THIS IS errWrtNameNo in SNsolve code=" << no;
    break;
  }

  return;
}


void SNsolve::checkInit(void)
{
  // Set program model name at local   called from scheme_solve_check.cpp
  int pmNo = feelfemproc.GetProgramModel();
  
  feelfemconf.SetProgramModelNameFromCode(pmNo,programModelNameCopy);

  // If solver is not specified explicitly (DEFAULT_STRING) set
  // default actual name to solverName
  if(solverName == DEFAULT_STRING) {
    feelfemconf.SetDefaultSolverName( programModelNameCopy ,
				      solverName             );
  }
  
  return;
  
}


int SNsolve::setNumberOfUnknowns(void) 
{
  int unknowns  = unknownIdentifierList->GetNumberOfElements();
  int testfuncs = testFunctionIdentifierList->GetNumberOfElements();

  if(unknowns != testfuncs) {
    return(YA);
  }

  numberOfUnknowns = unknowns;

  return(NICHT);
}

// check number of equations and unknowns 
int SNsolve::isConsistentNumberOfEqs(void)
{
  int unknowns  = unknownIdentifierList->GetNumberOfElements();
  if(unknowns != weakEquations) {
    return(NO);
  }
  return(YES);
}


int SNsolve::ParametricNameCheck(void)
{
  if(parametricName == DEFAULT_STRING) {
    feelfemconf.SetParametricElementName( refEtype, parametricName );
    return(0); // no error
  }
  else {
    if(! feelfemobj.IsDefinedElementName( parametricName ) ) {

      SystemErrorAStrA(this,"Parametric element ",parametricName,
		       " is not defined.");
      return(1);
    }
    Element *ePtr = feelfemobj.GetElementPtrByName(parametricName);
    if(ePtr->GetEtype() != refEtype ) {

      SystemErrorAStrA(this,"Parametric element ",parametricName,
		       " is invalid.");
      return(1);
    }

    return(0);
  }
  assert(1==0);
  return(0);  // never reach here
}

int SNsolve::SolverNameCheck(void)
{
  int ret;
  ret = feelfemconf.IsValidSolverName( solverName );

  return(ret);
}

int SNsolve::PM_LIBmatchCheck(void)
{
  int ret;

  ret = feelfemconf.IsValidPM_LIB( programModelNameCopy ,solverName);
  // return YES no error (1)
  // return NO  error

  return(ret);
}

int SNsolve::CheckNdataExists()
{
  //  return code
  //
  //  0  No error
  //  1  some weak form has no boundary term
  //  2  no nbc: while there is bounary term

  int ndata            = ncondLst.getNumberOfElements();
  int boundaryIntTerms = 0;
  int weakforms        = 0;

  listIterator <SNsolveWeq *>itrWeq(weqLst);
  
  for(itrWeq.init(); !itrWeq ; ++itrWeq) {
    weakforms++;
    if(itrWeq()->HasBoundaryTerm()==YES) {
      boundaryIntTerms++;
    }
  }

  // boundary term exists, but not all weakform has boundary term
  if(boundaryIntTerms > 0  && weakforms != boundaryIntTerms) {
    return(1);
  }

  // boundary term exists, but no nbc: data 
  if(boundaryIntTerms > 0  && ndata     == 0 ) {
    return(2);
  }

  return(0);
}

int SNsolve::VariableDefinedCheck(void)
{
  int ret;
  
  ret = 0;

  list <string> unknownVarNameLst;

  // unknowns check
  SNname *snnPtr;
  for(int i=0;i<unknownIdentifierList->GetNumberOfElements();i++) {
    snnPtr=(*unknownIdentifierList)[i];
    if(feelfemobj.IsDefinedUnknownVariable( snnPtr->GetName() )
       == NO) {
      
      SystemErrorAAA(this,"variable '",snnPtr->GetName(),"' cannot be unknown.");
      ret++;
      
    }
    else {

      // make unknown variable name lst
      string nm;
      nm = snnPtr->GetName();
      unknownVarNameLst.addlast(nm);
    }
  }

  // test function check
  for(int i=0;i<testFunctionIdentifierList->GetNumberOfElements();i++) {
    snnPtr =(*testFunctionIdentifierList)[i];

    if(feelfemobj.IsDefinedVariable(snnPtr->GetName()) == YES) {
      SystemErrorAAA(this,"test function symbol '",snnPtr->GetName(),"' is already used.");
      ret++;
    }
  }

  // integrand variable check
  listIterator <SNsolveWeq *>itrWeq(weqLst);

  // prepare test function string list
  string testFuncVar;
  list <string>testFuncLst;
  for(int i=0;i<testFunctionIdentifierList->GetNumberOfElements();i++) {
    snnPtr =(*testFunctionIdentifierList)[i];
    testFuncVar = snnPtr->GetName();
    testFuncLst.add(testFuncVar);
  }

  for(itrWeq.init(); !itrWeq ; ++itrWeq) {
    ret+=itrWeq()->VariableDefinedCheck_Regional( testFuncLst );
  }

  // dirichlet variable check
  // use unknownVarNameLst

  listIterator <SNsolveDirichlet *>itrD(dcondLst);
  for(itrD.init(); !itrD ; ++itrD) {
    ret += itrD()->VariableDefinedCheck_Dirichlet( unknownVarNameLst );
  }

  // neumann variable check ( check only neumann data )
  listIterator <SNsolveNeumann *>itrN(ncondLst);
  for(itrN.init(); !itrN ; ++itrN) {
    ret += itrN()->VariableDefinedCheck_NeumannData();
  }

  // no neumann data, did not check
  if(ncondLst.getNumberOfElements() != 0) {

    // boundary integral and neumann data
    list <string>appearedVarLst;
    for(itrN.init(); !itrN ; ++itrN) {   // neumann data loop

      for(itrWeq.init(); !itrWeq ; ++itrWeq) { // Weq equation loop

	ret+=itrWeq()->VariableDefinedCheck_Boundary( testFuncLst ,
						      itrN()      ,
						      appearedVarLst );
      }

      // check all neumann temporary variables are used.
      ret+= itrN()->CheckAllNTVarsAreUsed( appearedVarLst );

      appearedVarLst.deleteAllValues();
    }
  }  // if neumann data exists, check

  return(ret);
}


int SNsolve::EtypeConsistencyCheck(void)
{
  int errors;
  errors = 0;

  refEtype = -1;

  // This is not for SUBSOLVE

  // check for unknown variables
  Variable *varPtr;
  SNname *snnPtr;
  for(int i=0;i<unknownIdentifierList->GetNumberOfElements();i++) {
    snnPtr=(*unknownIdentifierList)[i];
    varPtr = feelfemobj.GetVariablePtrWithName(snnPtr->GetName());
    if(refEtype == -1) {
      refEtype = varPtr->GetEtype();
    }
    else {
      if(varPtr->IsConsistentEtypeWith(refEtype) == NO) {
	SystemErrorAAA((SNunit *)this,
		       "unknown variable '",
		       snnPtr->GetName(),
		       "' has different element type.");
	errors++;
	infoGeneratePossibleFlag = NO;
      }
    }
  }

  // etype consistency check
  string testFuncVar;
  list <string>testFuncLst;
  for(int i=0;i<testFunctionIdentifierList->GetNumberOfElements();i++) {
    snnPtr =(*testFunctionIdentifierList)[i];
    testFuncVar = snnPtr->GetName();
    testFuncLst.add(testFuncVar);
  }

  // make neumann temporary variable list
  string neumannTempVar;
  list <string>neumannTVarLst;
  listIterator <SNsolveNeumann *>itrN(ncondLst);
  for(itrN.init(); !itrN; ++itrN) {
    itrN()->AddTVarStrToList( neumannTVarLst );
  }


  listIterator <SNsolveWeq *>itr(weqLst);
  for(itr.init(); !itr ; ++itr) {
    int ret;

    ret = itr()->EtypeConsistencyCheck( refEtype ,testFuncLst ,neumannTVarLst);
    if(ret != 0) {
      infoGeneratePossibleFlag = NO;
    }
    errors+= ret;
  }  

  return(errors);
}

int SNsolve::QuadratureConsistencyCheck(void)
{
  int errors;

  errors = 0;

  Quadrature *qPtr;

  if(quadratureMethod != DEFAULT_STRING) {
    
    if(feelfemobj.IsDefinedQuadratureName( quadratureMethod ) == NO) {
      SystemErrorAStrA((SNunit *)this,"quadrature '",quadratureMethod,
		       "' is not defined.");
      errors++;
      return(errors);   // do not check ewise-quad
    }
    else {
      qPtr = feelfemobj.GetQuadraturePtrByName(quadratureMethod);

      if(qPtr->GetEtype() != refEtype) {
	SystemErrorAStrA((SNunit *)this,"quadrature '",quadratureMethod,
			 "' is a wrong element type.");
	errors++;
	
	return(errors);  // do not check ewise-quad
      }
    }
  }
  else {
    //quadrature is not explicitly defined.
    cerr << "quadrature is not explicitly defined. \n";
    qPtr = feelfemconf.GetDefaultQuadraturePtrByEtype( refEtype );
  }

  // here, "qPtr" has right quadrature.


  // prepare test function string list
  string testFuncVar;
  list <string>testFuncLst;
  for(int i=0;i<testFunctionIdentifierList->GetNumberOfElements();i++) {
    SNname *snnPtr;
    snnPtr =(*testFunctionIdentifierList)[i];
    testFuncVar = snnPtr->GetName();
    testFuncLst.add(testFuncVar);
  }

  listIterator <SNsolveWeq *>itr(weqLst);
  for(itr.init(); !itr ; ++itr) {
    errors+=itr()->QuadratureConsistencyCheck( refEtype ,testFuncLst ,qPtr);
  }  
  
  return(errors);
}

int SNsolve::BoundaryGeometryCheck(void)
{
  int errors=0;

  listIterator <SNsolveDirichlet *>itrD(dcondLst);
  for(itrD.init();!itrD;++itrD) {
    errors += itrD()->GeometryCheck();
  }

  listIterator <SNsolveNeumann *>itrN(ncondLst);
  for(itrN.init();!itrN;++itrN) {
    errors += itrN()->GeometryCheck();
  }
  return(errors);
}
