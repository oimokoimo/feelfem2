/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNfunction.cpp
 *  Date     : 2001/03/13
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <stdio.h>                               // for sprintf

#include "Object.hpp"
#include "../../class/feelfuncs.hpp"
#include "SNfunction.hpp"
#include "../../class/list.hpp"

int isIntrinsicFunction(string &);               // defined in check directory

SNfunction::SNfunction(char *name,SNunit *a) 
  : SNunit("function",SN_FUNCTION),exprlst(a) 
{ 
  val = name; 

  arguments = ((SNexprlist *)a)->howManyElements();

  // function name is in small letter
  for(int i=0;i<CstringLength(val);i++) {
    if(val[i] >= 'A' && val[i] <= 'Z') {
      val[i] = val[i] - 'A' + 'a';
    }
  }

  // if function is not intrinsic, store
  if(!isIntrinsicFunction(val)) {
    feelfemobj.StoreSNfunctionPtr( this );
  }

  return;
}

const char *SNfunction::GetName(void)
{
  return (const char *)val;
}

void SNfunction::exprPrint( char *buf, int flag , void *ptr1,void *ptr2) 
{

  int charPointer;
  int wrtLength;

  wrtLength = val.length();
  if(wrtLength < 1) {
    abortExit("Illegal wrtLength for name in SNfunction");
  }

  string small=val;
  small.lower();            // to check "sqrt"

  switch(flag) {
  case EXPRPRINT_NORMAL:
  case EXPRPRINT_SIMPLE:
  case EXPRPRINT_REPLACE_EVAL:
  case EXPRPRINT_REPLACE_EVALPAIR:


    if(small == "sqrt") {
      charPointer = stringLength( buf );
      //      wrtLength = 3; // "pow"   12 means numeric(1,2), 1 comma, 1 ')'
      //      if(charPointer + wrtLength +1+ 12 + 1 + 1> MAX_EXPRPRINT_BUF) {
      //	abortExit("Too long expression in SNfunction");
      //      }
      //      sprintf(buf+charPointer,"%s","pow");
      //      *(buf+charPointer+wrtLength  ) = '(';
      //      *(buf+charPointer+wrtLength+1) = '\0';
      
      //      exprlst->exprPrint( buf,flag,ptr1,ptr2);
      
      //      charPointer = stringLength( buf );    
      //      if(charPointer + 12 + 1 + 1 > MAX_EXPRPRINT_BUF) {
      //	abortExit("Too long expression in SNfunction");
      //      }
      //      sprintf(buf+charPointer,"%s%c",",numeric(1,2))",'\0');

      wrtLength  =1;  // ( ^(1/2))
      if(charPointer + wrtLength +1+ 7+ 1 + 1> MAX_EXPRPRINT_BUF) {
	abortExit("Too long expression in SNfunction");
      }
      sprintf(buf+charPointer,"((");
      *(buf+charPointer+wrtLength+1) = '\0';
      
      exprlst->exprPrint( buf,flag,ptr1,ptr2);
      
      charPointer = stringLength( buf );    
      if(charPointer + 7 + 3 + 1 > MAX_EXPRPRINT_BUF) {
	abortExit("Too long expression in SNfunction");
      }
      sprintf(buf+charPointer,")^(1/2))%c",'\0');
    }


    else {  // not sqrt
      charPointer = stringLength( buf );
      if(charPointer + wrtLength + 2 + 1 > MAX_EXPRPRINT_BUF) {
	abortExit("Too long expression in SNfunction");
      }
      sprintf(buf+charPointer,"%s",(char *)val);
      *(buf+charPointer+wrtLength  ) = '(';
      *(buf+charPointer+wrtLength+1) = '\0';
    
      exprlst->exprPrint( buf,flag,ptr1,ptr2);
    
      charPointer = stringLength( buf );    
      if(charPointer + 1 + 1 > MAX_EXPRPRINT_BUF) {
	abortExit("Too long expression in SNfunction");
      }
      *(buf+charPointer    ) = ')';
      *(buf+charPointer  +1) = '\0';
    }

    break;
      
  default:
    abortExit("Illegal code for flag in SNfunction::exprPrint");
  }

  return;
}

int SNfunction::howManyNotDefinedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret;
  
  ret = 0;   // though, no meaning...

  switch(flag) {
  case EXPRPRINT_NORMAL:
  case EXPRPRINT_SIMPLE:
  case EXPRPRINT_REPLACE_EVAL:
  case EXPRPRINT_REPLACE_EVALPAIR:
    ret = exprlst->howManyNotDefinedVariable(flag,ptr1,ptr2);
    break;
      
  default:
    abortExit("Illegal code for flag in SNfunction::isDefinedVariable");
  }

  return(ret);
}


int SNfunction::howManyNotDefinedFunction(int flag , void *ptr1,void *ptr2) 
{
  int ret;

  ret = 0;   // though, no meaning
  
  switch(flag) {
  case EXPRPRINT_NORMAL:
  case EXPRPRINT_SIMPLE:
  case EXPRPRINT_REPLACE_EVAL:
  case EXPRPRINT_REPLACE_EVALPAIR:
    ret = exprlst->howManyNotDefinedFunction(flag,ptr1,ptr2);
    
    if(!isIntrinsicFunction(val)) {
      ret++;
      list <string> *lstPtr;
      lstPtr = (list <string> *)ptr2;
      lstPtr->adduniq( val );
    }
    break;
  default:
    abortExit("Illegal code for flag in SNfunction::isDefinedFunction");
  }

  return(ret);
}

int SNfunction::howManyNotAssignedVariable(int flag , void *ptr1,void *ptr2) 
{
  int ret;
  
  ret = 0;   // though, no meaning...

  switch(flag) {
  case EXPRPRINT_NORMAL:
  case EXPRPRINT_SIMPLE:
  case EXPRPRINT_REPLACE_EVAL:
  case EXPRPRINT_REPLACE_EVALPAIR:
    ret = exprlst->howManyNotAssignedVariable(flag,ptr1,ptr2);
    break;
      
  default:
    abortExit("Illegal code for flag in SNfunction::isAssignedVariable");
  }

  return(ret);
}

