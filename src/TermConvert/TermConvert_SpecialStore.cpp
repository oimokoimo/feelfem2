/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : TermConvert_SpecialStore.cpp
 *  Date     : 2002/01/22
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

#include "TermConvert.hpp"
#include "Element.hpp"
#include "Variable.hpp"

void TermConvert::AddVariable ( Variable *vPtr)
{
  StoreVariableList(vPtr);      // 020724  with uniq check

  switch(vPtr->GetType()) {
  case VAR_FEM:
  case VAR_VFEM:

    AddVariableFEM( vPtr );
    break;
    

  case VAR_EWISE_A:
    if(vPtr->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
      AddVariableEWISEquad( vPtr );
    }
    else {
      AddVariableFEM( vPtr );
    }
    break;

  case VAR_EWISE:
    AddVariableEWISEmaterial( vPtr );
    break;
    
  case VAR_DOUBLE:
  case VAR_INT:
  case VAR_CONST:
    AddVariableScalar( vPtr );
    break;

  case VAR_MATERIAL:
    AddVariableMaterial( vPtr );
    break;
    
  default:
    assert(1==0);
  }

  return;
}

void TermConvert::AddVariableFEM( Variable *vPtr)
{
  Element *ePtr;
  int      freedom;

  ePtr           = vPtr->GetElementPtr();

  // set startingSblNo
  int stno;
  stno = startingSblNo;
  
  // update startingSblNo
  freedom        = ePtr->GetElementFreedom();
  startingSblNo += freedom;

  // set elementTermConvertNumber
  int etcno;
  if( !elementPtrLst.includes(ePtr) ) {

    // Add element list
    elementPtrLst.addlast(ePtr);

    // Set elementstno list
    if(elementTypes == 0) {
      elementStnoLst.addlast( 1 );

      // set estno
      ePtr->SetEstNo(1);

    }
    else {
      Element *ecPtr = elementPtrLst.getNthElement(elementTypes);
      int current = elementStnoLst.getNthElement(elementTypes);
      current = current + ecPtr->GetElementFreedom();
      elementStnoLst.addlast( current );

      ePtr->SetEstNo(current);
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
  makeLinearCombi(buf,BUFSIZ,stno,estno,freedom);

  storeConvertPair( vPtr->GetName(), buf );
  
  return;
}


void TermConvert::AddVariableEWISEquad( Variable *vPtr )
{
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
  
void TermConvert::AddVariableEWISEmaterial( Variable *vPtr )
{
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

void TermConvert::AddVariableMaterial( Variable *vPtr )
{
  int stno;
  stno = startingSblNo;
  vPtr->SetSblNo( stno );
  
  // update startingSblNo
  int freedom;

  freedom = 1;     // only one symbol is necessary for material
  startingSblNo += freedom;

  char buf[BUFSIZ];
  makeNthSymbol(buf,BUFSIZ,stno);

  storeConvertPair( vPtr->GetName(), buf );

  return;
}
  
void TermConvert::AddVariableScalar( Variable *vPtr )
{
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

void TermConvert::makeNthSymbol(char *buf,int bufferSize, int no)
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

void TermConvert::makeLinearCombi(char *buf,int bufferSize,
				  int stno,     // starting no for coefficient
				  int estno,    // element starting no;
				  int freedom)  // number of freedom
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
void TermConvert::SetTestFunctionSymbol( string &testfuncStr, int funcNo)
{
  char buf[38];
  
  sprintf(buf,"_n%d(x,y,z)%c",funcNo,'\0');
  
  replaceConvertPair( testfuncStr, buf );

  return;
}
