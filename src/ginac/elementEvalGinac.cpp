/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : elementEvalGinac.hpp
 *  Date     : 2001/12/29    (Copy of quadratureEvalGinac.hpp)
 *  Modified : 
 *  
 *  Purpose  : Evaluate coordinates and update SNelement classes
 *  
 *             Different from meshEvalGinac, this class must be
 *             made for each quadrature block.
 *  
 *  
 *  void vertexDefaults(int etype)    // add evalPair("x1",1.0), etc.
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
 */

// #include <ginac/ginac.h>
// using namespace GiNaC;

#include <cassert>
#include "feeldef.hpp"

#include "elementEvalGinac.hpp"
#include "../check/check_funcs.hpp"
#include "evalPair.hpp"

#include "../parser/Syntax/SNelement.hpp"
#include "../parser/Syntax/SNelementDoubleVar.hpp"
#include "../parser/Syntax/SNelementAssignment.hpp"
#include "../parser/Syntax/SNelementIntp.hpp"


elementEvalGinac::elementEvalGinac()
{
  // do nothing 
}

elementEvalGinac::~elementEvalGinac()
{
  // do nothing  (may be delete the list)   // oimo-delete

  // must free evalPair * memory            // oimo-delete
}


void elementEvalGinac::vertexDefaults( int etype )
{
  switch( etype ) {
  case ELEMENT_TYPE_LINE:
    {
      evalPair *ePtr;

      // add (-1.0);
      ePtr = new evalPair("x1", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (+1.0);
      ePtr = new evalPair("x2",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);
    }
    break;
      
  case ELEMENT_TYPE_TRI:
    {
      evalPair *ePtr;

      // add (x1,y1) = (0.0,0.0);
      ePtr = new evalPair("x1", 0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y1", 0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x2,y2) = (1.0,0.0);
      ePtr = new evalPair("x2",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y2",  0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x3,y3) = (0.0,1.0);
      ePtr = new evalPair("x3",  0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y3",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

    }
    break;

  case ELEMENT_TYPE_RECT:
    {
      evalPair *ePtr;

      // add (x1,y1) = (-1.0,-1.0);
      ePtr = new evalPair("x1", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y1", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x2,y2) = ( 1.0,-1.0);
      ePtr = new evalPair("x2",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y2", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x3,y3) = ( 1.0, 1.0);
      ePtr = new evalPair("x3",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y3",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x4,y4) = (-1.0, 1.0);
      ePtr = new evalPair("x4", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y4",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

    }
    break;

  case ELEMENT_TYPE_TETRA:
    {
      evalPair *ePtr;

      // add (x1,y1,z1) = (0.0,0.0,0.0);
      ePtr = new evalPair("x1",  0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y1",  0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z1",  0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x2,y2,z2) = (1.0,0.0,0.0);
      ePtr = new evalPair("x2",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y2",  0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z2",  0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x3,y3,z3) = (0.0,1.0,0.0);
      ePtr = new evalPair("x3",  0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y3",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z3",  0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x4,y4,z4) = (0.0,0.0,1.0);
      ePtr = new evalPair("x4",  0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y4",  0.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z4",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

    }
    break;

  case ELEMENT_TYPE_CUBE:

    {
      evalPair *ePtr;
      // add (x1,y1,z1) = (-1.0,-1.0,-1.0);
      ePtr = new evalPair("x1", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y1", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z1", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x2,y2,z2) = ( 1.0,-1.0,-1.0);
      ePtr = new evalPair("x2",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y2", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z2", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x3,y3,z3) = ( 1.0, 1.0,-1.0);
      ePtr = new evalPair("x3",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y3",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z3", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x4,y4,z4) = (-1.0, 1.0,-1.0);
      ePtr = new evalPair("x4", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y4",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z4", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x5,y5,z5) = (-1.0,-1.0, 1.0);
      ePtr = new evalPair("x5", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y5", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z5",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x6,y6,z6) = ( 1.0,-1.0, 1.0);
      ePtr = new evalPair("x6",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y6", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z6",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x7,y7,z7) = ( 1.0, 1.0, 1.0);
      ePtr = new evalPair("x7",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y7",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z7",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      // add (x8,y8,z8) = (-1.0, 1.0, 1.0);
      ePtr = new evalPair("x8", -1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("y8",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);

      ePtr = new evalPair("z8",  1.0);
      assert(! evalList.includes(ePtr));
      evalList.addlast(ePtr);
    }
    break;

  default:
    assert(1==0);
  }
  
  return;
}


// This function is almost empty, made for using evalList in evaluator
int elementEvalGinac::evalInterpolationNode(SNelementIntp *iPtr)
{
  int ret;

  list <string>nonDefLst;
  ret = iPtr->howManyNotDefinedVariable(EXPRPRINT_REPLACE_EVALPAIR,
					&evalList,&nonDefLst       );
  if(ret != 0) {
    SystemErrorA((SNunit *)iPtr,"Node coordinate has undefined variable.");
    return(1);
  }
  ret = iPtr->howManyNotDefinedFunction(EXPRPRINT_REPLACE_EVALPAIR,
					&evalList,&nonDefLst       );
  if(ret != 0) {
    SystemErrorA((SNunit *)iPtr,"Node coordinate has undefined function.");
    return(1);
  }
  ret = iPtr->howManyNotAssignedVariable(EXPRPRINT_REPLACE_EVALPAIR,
					&evalList,&nonDefLst       );
  if(ret != 0) {
    SystemErrorA((SNunit *)iPtr,"Node coordinate has non assigned variable.");
    return(1);
  }

  ret = iPtr->evalCoordinate(&evalList);  // return 0 if no error

  return(ret);
}




int elementEvalGinac::elementDoubleVar(SNelementDoubleVar *dPtr)
{
  evalPair *newPtr = dPtr->makeEvalPair(&evalList);  // pass the pointer

  if(newPtr == NULL) {
    SystemErrorNameA((SNunit *)dPtr," is multiply declared.");
    return(1);
  }

  int errFlag;
  errFlag = 0;

  if(dPtr->isInitialValue()) {
    errFlag = 0;

    list <string> nonDefList;


    if(dPtr->howManyNotDefinedVariable(EXPRPRINT_REPLACE_EVALPAIR,
    				  &evalList,&nonDefList       ) != 0) {
      errFlag = 1;
      
      listIterator <string> itr1(nonDefList);
      for(itr1.init();!itr1;++itr1) {
	string neuStr = itr1();
	SystemErrorANameStrA(dPtr,neuStr,"In initializing ",
			     " is not defined yet.");
      } 
      nonDefList.deleteAllValues();   // clear strings in nonDefList
    }


    if(dPtr->howManyNotDefinedFunction(EXPRPRINT_REPLACE_EVALPAIR,
				    &evalList,&nonDefList      ) != 0) {
      errFlag = 1;
      listIterator <string> itr1(nonDefList);
      for(itr1.init();!itr1;++itr1) {
	string neuStr = itr1();
	SystemErrorANameStrA(dPtr,neuStr,"In initializing ",
			     " is not intrinsic function.");
      }
      nonDefList.deleteAllValues();   // clear strings in nonDefList
    }


    if(dPtr->howManyNotAssignedVariable(EXPRPRINT_REPLACE_EVALPAIR,
					&evalList,&nonDefList   ) != 0) {
      errFlag = 1;
      listIterator <string> itr1(nonDefList);
      for(itr1.init();!itr1;++itr1) {
	
	string neuStr = itr1();
	SystemErrorANameStrA(dPtr,neuStr,"In initializing ",
			     " is not assigned value.");
      }
      nonDefList.deleteAllValues();
    }

    double evalVal;
    if(errFlag == 0) {
      int evalErrFlag;
      evalVal = dPtr->evalInitialValue(&evalList,evalErrFlag);

      if(evalErrFlag != 0) {
	SystemErrorANameA(dPtr,"Initial value of "," is not numeric.");
	errFlag = 1;
      }
      //  cerr <<"dPtr->evalInitialValue(&evalList) = "<<evalVal << endl;
    }
    else {
      evalVal = ERROR_EVALVAL;
    }
    newPtr->setValue(evalVal);
  }

  evalList.addlast(newPtr);  // it includes cannot evaluate error
  if(errFlag == 0) {
    return(0);
  }
  else {
    return(1);
  }
}

int elementEvalGinac::elementAssignment(SNelementAssignment *dPtr)
{
  int errFlag;
  errFlag = 0;

  evalPair *evalPairPtr = getEvalPairByString(dPtr->leftVarName);
  if(evalPairPtr == NULL) {
    errFlag = 1;
    SystemErrorNameA(dPtr," is not declared.");
    return(1);
  }

  list <string> nonDefList;
  if(dPtr->howManyNotDefinedVariable(EXPRPRINT_REPLACE_EVALPAIR,
				     &evalList,&nonDefList       ) != 0) {
    errFlag = 1;
    listIterator <string> itr1(nonDefList);
    for(itr1.init();!itr1;++itr1) {
      string neuStr = itr1();
      SystemErrorANameStrA(dPtr,neuStr,"In assignement of ",
			   " is not defined yet.");
    } 
    nonDefList.deleteAllValues();   // clear strings in nonDefList
  }

  if(dPtr->howManyNotDefinedFunction(EXPRPRINT_REPLACE_EVALPAIR,
				     &evalList,&nonDefList      ) != 0) {
    errFlag = 1;
    listIterator <string> itr1(nonDefList);
    for(itr1.init();!itr1;++itr1) {
      string neuStr = itr1();
      SystemErrorANameStrA(dPtr,neuStr,"In assignment of ",
			   " is not intrinsic function.");
    }
    nonDefList.deleteAllValues();   // clear strings in nonDefList
  }

  if(dPtr->howManyNotAssignedVariable(EXPRPRINT_REPLACE_EVALPAIR,
				      &evalList,&nonDefList   ) != 0) {
    errFlag = 1;
    listIterator <string> itr1(nonDefList);
    for(itr1.init();!itr1;++itr1) {
      string neuStr = itr1();
      SystemErrorANameStrA(dPtr,neuStr,"In assignment of ",
			     " is not assigned value.");
    }
    nonDefList.deleteAllValues();
  }

  double evalVal;
  if(errFlag == 0) {
    int evalErrFlag;
    evalVal = dPtr->evalValue(&evalList,evalErrFlag);

    if(evalErrFlag != 0) {
      SystemErrorANameA(dPtr,"Initial value of "," is not numeric.");
      errFlag = 1;
      evalVal = ERROR_EVALVAL;
    }
  }
  else {
    evalVal = ERROR_EVALVAL;
  }
  evalPairPtr->setValue(evalVal);       // even if error, assigned flag on

  if(errFlag == 0) {
    return(0);
  }
  else {
    return(1);
  }
}

int elementEvalGinac::elementIntp(SNelementIntp *dPtr)
{
  int errFlag;
  errFlag = 0;

  list <string> nonDefList;
  if(dPtr->howManyNotDefinedVariable(EXPRPRINT_REPLACE_EVALPAIR,
				     &evalList,&nonDefList       ) != 0) {
    errFlag = 1;
    listIterator <string> itr1(nonDefList);
    for(itr1.init();!itr1;++itr1) {
      string neuStr = itr1();
      SystemErrorANameStrA(dPtr,neuStr,"In evaluation of point ",
			   " is not defined.");
    } 
    nonDefList.deleteAllValues();   // clear strings in nonDefList
  }

  if(dPtr->howManyNotDefinedFunction(EXPRPRINT_REPLACE_EVALPAIR,
				     &evalList,&nonDefList      ) != 0) {
    errFlag = 1;
    listIterator <string> itr1(nonDefList);
    for(itr1.init();!itr1;++itr1) {
      string neuStr = itr1();
      SystemErrorANameStrA(dPtr,neuStr,"In evaluation of point ",
			   " is not intrinsic function.");
    }
    nonDefList.deleteAllValues();   // clear strings in nonDefList
  }

  if(dPtr->howManyNotAssignedVariable(EXPRPRINT_REPLACE_EVALPAIR,
				      &evalList,&nonDefList   ) != 0) {
    errFlag = 1;
    listIterator <string> itr1(nonDefList);
    for(itr1.init();!itr1;++itr1) {
      string neuStr = itr1();
      SystemErrorStrA(dPtr,neuStr," is not assigned value.");
    }
    nonDefList.deleteAllValues();
  }

  if(errFlag == 0) {

	  std::cerr << "EVAL COORDINATES IN elementEvalGinac::elementIntp\n";
    //    errFlag = dPtr->evalCoordinateAndWeight(&evalList);

    if(errFlag != 0) {
      SystemErrorANameA(dPtr,"Coordinate of "," is not numeric.");
    }
  }

  //  dPtr->testWrtCoor(cerr);    write point value

  return(errFlag);
}

int elementEvalGinac::isAllAssingedEvalPairList(list <string> &nonEvaledLst)
{
  int errFlag;
  errFlag = 0;
  listIterator <evalPair *> itr(evalList);
  for(itr.init();!itr ; ++itr) {
    if(!(itr()->isNumber())) {
      nonEvaledLst.addlast( itr()->varName );
      errFlag = 1;
    }
  }
  if(errFlag == 1) {
    return(NO);
  }
  else {
    return(YES);
  }
}

evalPair *elementEvalGinac::getEvalPairByString(string &nm)
{
  listIterator <evalPair *>itr(evalList);

  for(itr.init();!itr;++itr) {
    if(itr()->isNameIs( nm ) ) {
      evalPair *retPtr = itr();
      return(retPtr);
    }
  }
  return(NULL);
}
