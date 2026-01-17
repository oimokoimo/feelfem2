/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsymbol.cpp
 *  Date     : 2001/03/12
 *  Modified : 2001/12/30
 *  
 *  Purpose  :
 *  
 */

#include <stdio.h>                               // for sprintf
#include "../../class/feelfuncs.hpp"
#include "../../class/string.hpp"
#include "../../class/ptrList.hpp"
#include "SNsymbol.hpp"
#include "../../class/evalPair.hpp"        // evalPair definition

void SNsymbol::exprPrint( char *buf, int flag , void *ptr1,void *ptr2) 
{

  int charPointer = stringLength( buf );
  int wrtLength;
  int pos;

  evalPair *tmpEvalPairPtr;

  switch(flag) {
  case EXPRPRINT_NORMAL:
  case EXPRPRINT_SIMPLE:

    wrtLength = val.length();

    if(wrtLength < 1) {
      abortExit("Illegal wrtLength for EXPRPRINT_NORMAL SNsymbol");
    }

    if(charPointer + wrtLength + 1 > MAX_EXPRPRINT_BUF) {
      abortExit("Too long expression in SNsymbol");
    }
    sprintf(buf+charPointer,"%s",(char *)val);
    *(buf+charPointer+wrtLength) = '\0';
    break;

  case EXPRPRINT_REPLACE_EVAL:
    list <string> *listPtr;
    listPtr = (list <string> *)ptr1;

    pos   = listPtr->getPosition(val);
    if(pos == 0) {
      abortExit("VARIABLE IS NOT IN THE DEFINED LIST, SNsymbol.cpp");
    }
    wrtLength = REPLACE_EVAL_HEADER_LENGTH + REPLACE_EVAL_NUMBER_LENGTH;

    if(charPointer + wrtLength + 1 > MAX_EXPRPRINT_BUF) {
      abortExit("Too long expression in SNsymbol");
    }
    *(buf+charPointer          ) = 'a';
    if(pos <10) {
      sprintf(buf+charPointer+1,"0%d",pos);
    }
    else if (pos < 100) {
      sprintf(buf+charPointer+1,"%d",pos);      
    }
    else {
      abortExit("POS NUMBER OVER 99, in SNsymbol");
    }

    *(buf+charPointer+wrtLength) = '\0';
    break;

  case EXPRPRINT_REPLACE_EVALPAIR:
    ptrList <evalPair *> *ptrLstPtr;
    ptrLstPtr = (ptrList <evalPair *> *)ptr1;

    tmpEvalPairPtr = new evalPair(val);
    pos   = ptrLstPtr->getPosition(tmpEvalPairPtr);
    delete tmpEvalPairPtr;                             // no delete oimo string in eval Pair


    if(pos == 0) {
      abortExit("VARIABLE IS NOT IN THE DEFINED LIST, SNsymbol.cpp");
    }
    wrtLength = REPLACE_EVAL_HEADER_LENGTH + REPLACE_EVAL_NUMBER_LENGTH;

    if(charPointer + wrtLength + 1 > MAX_EXPRPRINT_BUF) {
      abortExit("Too long expression in SNsymbol");
    }
    *(buf+charPointer          ) = 'a';
    if(pos <10) {
      sprintf(buf+charPointer+1,"0%d",pos);
    }
    else if (pos < 100) {
      sprintf(buf+charPointer+1,"%d",pos);      
    }
    else {
      abortExit("POS NUMBER OVER 99, in SNsymbol");
    }

    *(buf+charPointer+wrtLength) = '\0';
    break;
      
  default:
    abortExit("Illegal code for flag in SNsymbol::exprPrint");
  }

  return;
}


int SNsymbol::howManyNotDefinedVariable(int flag , void *ptr1,void *ptr2) 
{

  list <string> *undefinedNameLstPtr;    // ptr 2 is undefined name list
  evalPair *tmpEvalPairPtr;

  undefinedNameLstPtr = (list <string> *)ptr2;

  switch(flag) {
  case EXPRPRINT_NORMAL:
  case EXPRPRINT_SIMPLE:

    abortExit("EXPRPRINT_NORMAL,SIMPLE option is not used in howManyNotdefinedVariable in SNsymbol.cpp");


  case EXPRPRINT_REPLACE_EVAL:
    list <string> *listPtr;
    listPtr = (list <string> *)ptr1;

    if(listPtr->includes(val)) {
      return(0);
    }
    else {
      undefinedNameLstPtr->addlast(val);
      return(1);
    }
    break;

  case EXPRPRINT_REPLACE_EVALPAIR:
    ptrList <evalPair *> *ptrLstPtr;
    ptrLstPtr = (ptrList <evalPair *> *)ptr1;

    tmpEvalPairPtr = new evalPair(val);
    
    if(ptrLstPtr->includes(tmpEvalPairPtr)) {
      delete tmpEvalPairPtr;    // no delete oimo string in eval Pair
      return(0);
    }
    else {
      delete tmpEvalPairPtr;    // no delete oimo string in eval Pair
      undefinedNameLstPtr->addlast(val);
      return(1);
    }
      
  default:
    abortExit("Illegal code for flag in SNsymbol::howManyNotDefinedVariable");
  }
  cerr << "NEVER COME HERE (SNsymbol.cpp)" << endl;
  return(1);
}

int SNsymbol::howManyNotAssignedVariable(int flag , void *ptr1,void *ptr2) 
{

  list <string> *notAssignedNameLstPtr;    // ptr 2 is not defined name list
  evalPair *tmpEvalPairPtr;

  notAssignedNameLstPtr = (list <string> *)ptr2;

  switch(flag) {
  case EXPRPRINT_NORMAL:
  case EXPRPRINT_SIMPLE:

    abortExit("EXPRPRINT_NORMAL,simple option is not used in howManyNotAssignedVariable in SNsymbol.cpp");


  case EXPRPRINT_REPLACE_EVAL:
    abortExit("EXPRPRINT_REPLACE_EVAL option is not used in howManyNotAssignedVariable in SNsymbol.cpp");


  case EXPRPRINT_REPLACE_EVALPAIR:
    ptrList <evalPair *> *ptrLstPtr;
    ptrLstPtr = (ptrList <evalPair *> *)ptr1;

    tmpEvalPairPtr = new evalPair(val);
    
    if(ptrLstPtr->includes(tmpEvalPairPtr)) {          // declared, but,,,,
      int pos;
      pos = ptrLstPtr->getPosition( tmpEvalPairPtr );
      delete tmpEvalPairPtr;                           // oimo 

      evalPair *evalPairPtr;
      evalPairPtr = ptrLstPtr->getNthElement( pos );
      if(evalPairPtr->isNumber() == YES) {
	return(0);                                     // assigned,
      }
      else {
	notAssignedNameLstPtr->addlast(val);	
	return(1);                                     // not assigned
      }
    }
    else {
      delete tmpEvalPairPtr;    // no delete oimo string in eval Pair
      return(0);                // this error is detected in not declared,
                                // here not assigned, hense return 0
    }
      
  default:
    abortExit("Illegal code for flag in SNsymbol::howManyNotAssignedVariable");
  }
  cerr << "NEVER COME HERE (SNsymbol.cpp)" << endl;
  return(1);
}

int SNsymbol::howManyNotDefinedFunction(int flag , void *ptr1,void *ptr2) 
{
  return(0);
}
