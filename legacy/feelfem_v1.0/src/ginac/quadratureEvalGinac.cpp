/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : quadratureEvalGinac.hpp
 *  Date     : 2001/12/12    (Copy of meshEvalGinac.hpp)
 *  Modified : 
 *  
 *  Purpose  : Evaluate coordinates and update SNquadrature classes
 *  
 *             Different from meshEvalGinac, this class must be
 *             made for each quadrature block.
 *  
 */

// #include <ginac/ginac.h>
// using namespace GiNaC;

#include "quadratureEvalGinac.hpp"
#include "../check/check_funcs.hpp"
#include "evalPair.hpp"

#include "../parser/Syntax/SNquadrature.hpp"
#include "../parser/Syntax/SNquadratureDoubleVar.hpp"
#include "../parser/Syntax/SNquadratureAssignment.hpp"
#include "../parser/Syntax/SNquadratureGaussP.hpp"


quadratureEvalGinac::quadratureEvalGinac()
{
  // do nothing 
}

quadratureEvalGinac::~quadratureEvalGinac()
{
  // do nothing  (may be delete the list)   // oimo-delete

  // must free evalPair * memory            // oimo-delete
}


int quadratureEvalGinac::quadratureDoubleVar(SNquadratureDoubleVar *dPtr)
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

int quadratureEvalGinac::quadratureAssignment(SNquadratureAssignment *dPtr)
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

int quadratureEvalGinac::quadratureGaussP(SNquadratureGaussP *dPtr)
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
    errFlag = dPtr->evalCoordinateAndWeight(&evalList);

    if(errFlag != 0) {
      SystemErrorANameA(dPtr,"Coordinate of "," is not numeric.");
    }
  }

  //  dPtr->testWrtCoor(cerr);    write point value

  return(errFlag);
}

int quadratureEvalGinac::isAllAssingedEvalPairList(list <string> &nonEvaledLst)
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

evalPair *quadratureEvalGinac::getEvalPairByString(string &nm)
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
