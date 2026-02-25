/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : TermConvert_SpecialStore_Boundary.cpp
 *  Date     : 2002/03/31 (copy of TermConvert_SpecialStore.cpp)
 *  Modified : 
 *  
 *  Purpose  : TermConvert special store routine
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

#include <cassert>

#include "feeldef.hpp"

#include "TermConvert.hpp"
#include "Element.hpp"
#include "Variable.hpp"

void TermConvert::UseNX(void)
{
  nxFlag = YES;
  return;
}
void TermConvert::UseNY(void)
{
  nyFlag = YES;
  return;
}
void TermConvert::UseNZ(void)
{
  nzFlag = YES;
  return;
}

void TermConvert::SetNormalComponent_boundary(void)
{
  // nx is used.
  if(nxFlag == YES) {
    int stno;
    stno    = startingSblNo;
    sblNoNX = stno;
  
    // update startingSblNo
    int freedom;

    freedom = 1;     // only one symbol is necessary for quad ewise
    startingSblNo += freedom;

    char buf[BUFSIZ];
    makeNthSymbol_boundary(buf,BUFSIZ,stno);

    storeConvertPair( NAME_NORMAL_X , buf );
  }  //end of nx

  // ny is used.
  if(nyFlag == YES) {
    int stno;
    stno    = startingSblNo;
    sblNoNY = stno;
  
    // update startingSblNo
    int freedom;

    freedom = 1;     // only one symbol is necessary for quad ewise
    startingSblNo += freedom;

    char buf[BUFSIZ];
    makeNthSymbol_boundary(buf,BUFSIZ,stno);

    storeConvertPair( NAME_NORMAL_Y , buf );
  }  //end of ny

  // nz is used.
  if(nzFlag == YES) {
    int stno;
    stno    = startingSblNo;
    sblNoNZ = stno;
  
    // update startingSblNo
    int freedom;

    freedom = 1;     // only one symbol is necessary for quad ewise
    startingSblNo += freedom;

    char buf[BUFSIZ];
    makeNthSymbol_boundary(buf,BUFSIZ,stno);

    storeConvertPair( NAME_NORMAL_Z , buf );
  }  //end of nx

  return;
}

void TermConvert::AddVariableBoundary( Variable *vPtr)
{
  
  if(!varPtrLst.includes(vPtr)) {    // this is for making reverse term convert
    varPtrLst.addlast(vPtr);
  }

  switch(vPtr->GetType()) {
  case VAR_FEM:
  case VAR_VFEM:

    AddVariableFEM_boundary( vPtr );
    break;
    

  case VAR_EWISE_A:
    if(vPtr->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
      AddVariableEWISEquad_boundary( vPtr );
    }
    else {
      AddVariableFEM_boundary( vPtr );
    }
    break;

  case VAR_EWISE:
    AddVariableEWISEmaterial_boundary( vPtr );
    break;
    
  case VAR_DOUBLE:
  case VAR_INT:
  case VAR_CONST:
    AddVariableScalar_boundary( vPtr );
    break;
    
  default:
    assert(1==0);
  }

  return;
}

void TermConvert::AddVariableFEM_boundary( Variable *vPtr)
{
  Element *ePtr;
  Element *bePtr;
  int      freedom;

  ePtr           = vPtr->GetElementPtr();
  bePtr          = ePtr->AcquireBoundaryElementPtr();

  // set startingSblNo
  int stno;
  stno = startingSblNo;
  
  // update startingSblNo
  freedom        = bePtr->GetElementFreedom();  // boundary element
  startingSblNo += freedom;

  // set elementTermConvertNumber
  int etcno;
  if( !elementPtrLst.includes(ePtr) ) {     // elementPtrLst has region element

    // Add element list
    elementPtrLst.addlast(ePtr);

    // Set elementstno list
    if(elementTypes == 0) {
      elementStnoLst.addlast( 1 );

      // set estno (Used region element area)
      ePtr->SetEstNo(1);

    }
    else {
      Element *ecPtr = elementPtrLst.getNthElement(elementTypes);
      int current = elementStnoLst.getNthElement(elementTypes);
      Element *ecBPtr;
      ecBPtr = ecPtr->AcquireBoundaryElementPtr();      // get boundary element
      current = current + ecBPtr->GetElementFreedom();  // boundary element
      elementStnoLst.addlast( current );

      ePtr->SetEstNo(current);        // Use region element area
    }
    elementTypes++;
  }

  int estno;

  etcno = elementPtrLst.getPosition(ePtr);  
  assert(etcno != 0);
  estno = elementStnoLst.getNthElement(etcno);

  vPtr->SetElementTCNo( etcno );    // element no.  (not use 020218)
  vPtr->SetElementStno( estno );    // function no.  _nXX
  vPtr->SetSblNo      ( stno  );    // symbol no.  _mXX

  char buf[BUFSIZ];
  makeLinearCombi_boundary(buf,BUFSIZ,stno,estno,freedom);

  storeConvertPair( vPtr->GetName(), buf );
  
  return;
}


void TermConvert::AddVariableEWISEquad_boundary( Variable *vPtr )
{

  assert(1==0);    // boundary ewise is not allowed now.



  int stno;
  stno = startingSblNo;
  vPtr->SetSblNo( stno );
  
  // update startingSblNo
  int freedom;

  freedom = 1;     // only one symbol is necessary for quad ewise
  startingSblNo += freedom;

  char buf[BUFSIZ];
  makeNthSymbol(buf,BUFSIZ,stno);

  storeConvertPair( vPtr->GetName(), buf );

  return;
}
  
void TermConvert::AddVariableEWISEmaterial_boundary( Variable *vPtr )
{
  assert(1==0);   // boundary material hopefully will be allowed in the future


  int stno;
  stno = startingSblNo;
  vPtr->SetSblNo( stno );
  
  // update startingSblNo
  int freedom;

  freedom = 1;     // only one symbol is necessary for quad ewise
  startingSblNo += freedom;

  char buf[BUFSIZ];
  makeNthSymbol_boundary(buf,BUFSIZ,stno);

  storeConvertPair( vPtr->GetName(), buf );

  return;
}
  
void TermConvert::AddVariableScalar_boundary( Variable *vPtr )
{
  int stno;
  stno = startingSblNo;
  vPtr->SetSblNo( stno );
  
  // update startingSblNo
  int freedom;

  freedom = 1;     // only one symbol is necessary for quad ewise
  startingSblNo += freedom;

  char buf[BUFSIZ];
  makeNthSymbol_boundary(buf,BUFSIZ,stno);

  storeConvertPair( vPtr->GetName(), buf );

  return;
}

void TermConvert::makeNthSymbol_boundary(char *buf,int bufferSize, int no)
{
  int len;
  
  len =1;
  if(no > 9 && no < 100) len = 2;
  if(no > 99)            len = 3;

  assert(no < 1000);

  assert( 2 + len   + 1 <= bufferSize);
  //    "_m"  number '\0'

  sprintf(buf,"_m%d%c",no,'\0');
  
  return;
}

void TermConvert::makeLinearCombi_boundary(char *buf,int bufferSize,
				  int stno,     // starting no for coefficient
				  int estno,    // element starting no;
				  int freedom ) // number of freedom
{
  int length;


  *buf = '(';
  buf++;

  length = 3;  // with final ')\0';


  for(int i=0;i<freedom;i++) {

    int symblNo;
    int symblNoLength;

    symblNo = stno + i;
    if(symblNo < 10) symblNoLength = 1;
    if(symblNo >  9 && symblNo < 100) symblNoLength = 2;
    if(symblNo > 99) symblNoLength = 3;
    assert(symblNo < 1000);

    int funcNo;
    int funcNoLength;
    
    funcNo = estno + i;

    if(funcNo < 10) funcNoLength = 1;  // from 1 to 9
    if(funcNo > 9 ) funcNoLength = 2;
    assert(funcNo < 100);

    int termLength;

    termLength = 2 + funcNoLength+ 7      +   1  +  2  + symblNoLength ;
    //         "_n"  number        (x,y,z)   "*"   "_m"    number
    if(i!=0) termLength = termLength + 1;  // for '+'

    assert(termLength + length  < bufferSize );

    if(i == 0) {
      sprintf(buf,"_n%d(x,y,z)*_m%d",funcNo,symblNo);
    }
    else {
      sprintf(buf,"+_n%d(x,y,z)*_m%d",funcNo,symblNo);
    }

    buf+= termLength;
  }
  *buf= ')';
  buf++;
  *buf= '\0';

  return;
}

// called from GalerkinMethod::GalerkinTestFunction
void TermConvert::SetTestFunctionSymbol_boundary( string &testfuncStr, int funcNo)
{
  char buf[38];

  sprintf(buf,"_n%d(x,y,z)%c",funcNo,'\0');

  replaceConvertPair( testfuncStr, buf );

  return;
}
