/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Expression_CHECK.cpp
 *  Date     : 2002/01/21
 *  Modified : 
 *  
 *  Purpose  : isDefinedFEM
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
 */

#include "feelfuncs.hpp"
#include "../check/check_funcs.hpp"   // isCoordinate, SystemError, etc.

#include "Expression.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"

#include "../parser/Syntax/SNsolveNeumann.hpp"  // for check neumann data


int Expression::howManyNotIntrinsicFunctions(void)
{
  int n = 0;

  listIterator <string> itr(functionLst);
  for(itr.init(); !itr ; ++itr) {
    string nm = itr();
    if( !isIntrinsicFunction( nm ) ) {
      n++;
    }
  }
  return(n);
}

int Expression::checkDefinedVariableSN(SNunit *snPtr)
{
  int ret;

  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str) ) continue;   // in check/is

    if( isNormalComponent(str) )  continue;

    if( isDefinedFEMVariable( str ) ) continue;

    if( isDefinedScalarVariable( str ) ) continue;

    if( isDefinedEWISEVariable( str ) ) continue;

    if( isDefinedMaterialVariable( str ) ) continue;

    SystemErrorStrA( snPtr, str , " is not defined.");
    ret++;
  }
  return(ret);
}

int Expression::checkDefinedFunctionSN(SNunit *snPtr)
{
  int ret;

  ret = 0;

  listIterator <string> itr(functionLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();


    if( isIntrinsicFunction( str ) ) continue;
    if( isDifferentialOperator1( str ) ) continue;
    if( feelfemobj.IsUsedUserFunctionName( str ) ) continue;

    SystemErrorStrA( snPtr, str , " is not a defined function.");
    ret++;
  }
  return(ret);
}

int Expression::checkDefinedFEMObjectSN(SNunit *snPtr)
{
  int ret;

  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str)              ) continue;   // in check/is

    if( isDefinedFEMVariable( str )    ) continue;

    if( isDefinedScalarVariable( str ) ) continue;

    if( isDefinedEWISEVariable( str )  ) {

      SystemErrorStrA( snPtr, str , " is EWISE variable.");
      ret++;

      continue;
    }

    if( isDefinedMaterialVariable( str )  ) {

      SystemErrorStrA( snPtr, str , " is material variable.");
      ret++;

      continue;
    }

    SystemErrorStrA( snPtr, str , " is not defined.");
    ret++;
  }
  return(ret);
}


int Expression::checkDefinedVariable_RegionalSN(SNunit *snPtr,
						list<string>&tLst)

  // tLst contains test function symbols
{
  int ret;

  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str) ) continue;   // in check/is

    if( isDefinedFEMVariable( str ) ) continue;

    if( isDefinedScalarVariable( str ) ) continue;

    if( isDefinedEWISEVariable( str ) ) continue;

    if( isDefinedMaterialVariable( str ) ) continue;

    if( tLst.includes(str) ) continue;  // test function

    SystemErrorStrA( snPtr, str , " is not defined.");
    ret++;
  }
  return(ret);
}


int Expression::checkQuadratureConsistency_RegionalSN(SNunit *snPtr,
						      list<string>&tLst,
						      Quadrature *qPtr)

  // tLst contains test function symbols
{
  int ret;

  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str) ) continue;   // in check/is

    if( isDefinedFEMVariable( str ) ) continue;

    if( tLst.includes(str) ) continue;  // test function


    if( isDefinedScalarVariable( str ) ) continue;

    if( isDefinedMaterialVariable( str ) ) continue;  // any quadrature ok

    if( isDefinedEWISEVariable( str ) ) {
      
      Variable *vPtr = feelfemobj.GetVariablePtrWithName( str );
      
      if(vPtr->GetType() == VAR_EWISE_A) {

	if(vPtr ->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
	  
	  Quadrature *qvPtr = vPtr->GetQuadraturePtr();

	  if(qvPtr != qPtr) {
	    ret++;

	    SystemErrorAAA(snPtr, "Use of ewise-quad var '",
			  vPtr->GetName(),
			  "' is a mismatch Quadrature type.");
	  }
	}
      }

    }

  }
  return(ret);
}


// for boundary integrand
int Expression::checkDefinedVariable_BoundarySN(SNunit *snPtr,
						list <string>&tLst,
						SNsolveNeumann *snSNPtr,
						list <string>&apLst     )

  // tLst contains test function symbols
{
  int ret;

  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str) ) continue;   // in check/is

    if( isNormalComponent(str) ) continue;  // normal vectors can be used

    if( isDefinedFEMVariable( str ) ) continue;

    if( isDefinedScalarVariable( str ) ) continue;

    if( isDefinedMaterialVariable( str ) ) {
      SystemErrorAStrA( snPtr, "material variable '",str ,
			"' cannot be used in a boundary integrand. oimo1");
      ret ++;
      continue;
    }

    if( isDefinedEWISEVariable( str ) ) {
      SystemErrorAStrA( snPtr, "ewise variable '",str ,
			"' cannot be used in a boundary integrand. oimo2");
      ret ++;
      continue;
    }

    if( tLst.includes(str) ) continue;  // test function  // [N020204-1]

    // neumann temporary variable ?
    if( snSNPtr->IsTemporaryVariable(str) == YES) {
 
      apLst.add(str);   // appeared neumann temporary variable list 

      continue;
    }
    

    SystemErrorStrA( snPtr, str , " is not defined.");
    ret++;
  }

  return(ret);
}


int Expression::EtypeConsistencyCheckSN(SNunit *snPtr,int refEtype,
					list<string>&tLst)
  // tLst contains test function symbols
{
  int ret;
  ret = 0;

  listIterator <string> itr(identifierLst);
  Variable *varPtr;

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str)              ) continue; // in check/is
    //    if( isNormalComponent(str)         ) continue;(no normal in regional)
    if( isDefinedScalarVariable( str ) ) continue;    
    if( tLst.includes(str)             ) continue; // test function

    //        Variable *GetVariablePtrWithName(const char * );
    varPtr = feelfemobj.GetVariablePtrWithName( str );
    if(varPtr->IsConsistentEtypeWith( refEtype ) == NO) {
      SystemErrorStrA( snPtr, str , " is a different etype variable.");
      ret++;
    }
  }
  return(ret);
}

// for Boundary integrand
int Expression::EtypeConsistencyCheckSN(SNunit *snPtr,int refEtype,
					list<string>&tLst,
					list<string>&nLst)
  // tLst contains test function symbols
  // nLst contains neumann temporary variables
{
  int ret;
  ret = 0;

  listIterator <string> itr(identifierLst);
  Variable *varPtr;

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str)              ) continue; // in check/is
    if( isNormalComponent(str)         ) continue;
    if( isDefinedScalarVariable( str ) ) continue;    
    if( tLst.includes(str)             ) continue;  // test function
    if( nLst.includes(str)             ) continue;  // neumann temp variable

    //        Variable *GetVariablePtrWithName(const char * );
    varPtr = feelfemobj.GetVariablePtrWithName( str );
    if(varPtr->IsConsistentEtypeWith( refEtype ) == NO) {
      SystemErrorStrA( snPtr, str , " is a different etype variable.");
      ret++;
    }
  }
  return(ret);
}


int Expression::checkDefinedVariable_DirichletSN(SNunit *snPtr,
						list<string>&unknownLst)
  // tLst contains test function symbols
{
  int ret;
  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str) ) continue;      

    if( isDefinedScalarVariable( str ) ) continue;

    if( unknownLst.includes(str) ) {
           SystemErrorAStrA( snPtr, 
			     "unknown var '",str,
			     "' cannot be used in Diriclet data.");
      ret++;
      continue;
    } 
    
    // THIS MUST BE BELOW unknownLst.includes check
    if( isDefinedFEMVariable( str ) ) continue;

    if( isDefinedEWISEVariable( str ) ) {
      SystemErrorAStrA( snPtr, "ewise var '",str,"' cannot be used in Diriclet data.");
      ret++;
      continue;
    }

    SystemErrorStrA( snPtr, str , " is not defined.");
    ret++;
  }
  return(ret);
}


int Expression::checkDefinedVariable_NeumannDataSN(SNunit *snPtr,
						   list<string>&nVarLst)
  // tLst contains test function symbols
{
  int ret;
  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate(str)              ) continue;      
    if( isNormalComponent(str)         ) continue;
    if( isDefinedScalarVariable( str ) ) continue;

    if( nVarLst.includes(str) ) {
           SystemErrorAStrA( snPtr, 
			     "virtual variable '",str,
			     "' appeared in right hand side.");
      ret++;
      continue;
    } 
    
    // THIS MUST BE BELOW unknownLst.includes check
    if( isDefinedFEMVariable( str ) ) continue;

    if( isDefinedEWISEVariable( str ) ) {
      SystemErrorAStrA( snPtr, "ewise var '",str,"' cannot be used in Neumann data.");
      ret++;
      continue;
    }

    SystemErrorStrA( snPtr, str , " is not defined.");
    ret++;
  }
  return(ret);
}


int Expression::checkNoCoordinateSN(SNunit *snPtr)
{
  int ret = 0;
  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinate( str ) ) {
      SystemErrorAStrA( snPtr, "Coordinate ",str," cannot be used here.");
      ret++;
      continue;
    }

  }
  return(ret);
}

int Expression::checkNoFemSN(SNunit *snPtr)
{
  int ret = 0;
  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isDefinedFEMVariable( str ) ) {
      SystemErrorAStrA( snPtr, "fem variable '",str,"' cannot be used here.");
      ret++;
      continue;
    }

  }
  return(ret);
}


int Expression::checkNoEwiseSN(SNunit *snPtr)
{
  int ret = 0;
  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isDefinedEWISEVariable( str ) ) {
      SystemErrorAStrA( snPtr, "ewise var '",str,"' cannot be used here.");
      ret++;
      continue;
    }

  }
  return(ret);
}

int Expression::checkNoMaterialSN(SNunit *snPtr)
{
  int ret = 0;
  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isDefinedMaterialVariable( str ) ) {
      SystemErrorAStrA( snPtr, "material var '",str,"' cannot be used here.");
      ret++;
      continue;
    }

  }
  return(ret);
}

int Expression::checkNoNormalSN(SNunit *snPtr)
{
  int ret = 0;
  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isNormalComponent(str)   ) {
      SystemErrorAStrA( snPtr, "Normal component '",str,"' cannot be used here.");
      ret++;
      continue;
    }

  }
  return(ret);
}

int Expression::checkNoDifferentialFuncSN(SNunit *snPtr)
{
  int ret;

  ret = 0;

  listIterator <string> itr(functionLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isDifferentialOperator1( str ) ) {
      SystemErrorA( snPtr, "Differential operator cannot be used here.");
      ret++;
    }
  }
  return(ret);
}  
