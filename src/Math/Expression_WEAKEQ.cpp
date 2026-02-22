/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Expression_WEAKEQ.cpp
 *  Date     : 2002/02/12
 *  Modified : 2002/03/27 (add boundary part)
 *  
 *  Purpose  : Make variable pointer list for IntegrandSet 
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

#include "IntegrandSet.hpp"

void Expression::MakeIntegrandSetInfo(IntegrandSet *isetPtr,list<string>&tLst )
{
  int ret;

  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    if( isCoordinateX(str) ) {
      isetPtr->SetUseX();
      continue;
    }

    if( isCoordinateY(str) ) {
      isetPtr->SetUseY();
      continue;
    }

    if( isCoordinateZ(str) ) {
      isetPtr->SetUseZ();
      continue;
    }

    if( tLst.includes(str)) continue;    // test function symbol

    Variable *vPtr;
    vPtr = feelfemobj.GetVariablePtrWithName( str );

    isetPtr->AddVariablePtr(vPtr);
  }

  // function setting.

  listIterator <string>itrF(functionLst);
  for(itrF.init(); !itrF ; ++itrF ) {
    string str = itrF();

    if(isIntrinsicFunction(str)) continue;

    if(isDifferentialOperator1(str)) continue;

    std::cerr <<"DEBUG WARNING :: Expression_WEAKEQ.cpp\n";
    std::cerr <<"UNKNOWN function is specified. " << str << std::endl;

  }
      
  return;
}

// boundary part
void Expression::MakeIntegrandSetInfoBoundary(BoundaryIntegrandSet *bisetPtr,
					      list<string>&tLst )
{
  int ret;

  ret = 0;

  listIterator <string> itr(identifierLst);

  for(itr.init();  !itr ; ++itr) {

    string str = itr();

    // coordinates
    if( isCoordinateX(str) ) {
      bisetPtr->SetUseX();
      continue;
    }

    if( isCoordinateY(str) ) {
      bisetPtr->SetUseY();
      continue;
    }

    if( isCoordinateZ(str) ) {
      bisetPtr->SetUseZ();
      continue;
    }

    // normals
    if( isSystemNX(str) ) {
      bisetPtr->SetUseNX();
      continue;
    }

    if( isSystemNY(str) ) {
      bisetPtr->SetUseNY();
      continue;
    }

    if( isSystemNZ(str) ) {
      bisetPtr->SetUseNZ();
      continue;
    }

    if( tLst.includes(str)) continue;    // test function symbol

    Variable *vPtr;
    vPtr = feelfemobj.GetVariablePtrWithName( str );

    bisetPtr->AddVariablePtr(vPtr);
  }

  // function setting.

  listIterator <string>itrF(functionLst);
  for(itrF.init(); !itrF ; ++itrF ) {
    string str = itrF();

    if(isIntrinsicFunction(str)) continue;

    if(isDifferentialOperator1(str)) {
	    std::cerr << "Boundary Expression_WEAKEQ, differential is found.\n";
      continue;
    }

    std::cerr <<"DEBUG WARNING :: Expression_WEAKEQ.cpp\n";
    std::cerr <<"UNKNOWN function is specified. " << str << std::endl;
  }
      
  return;
}
