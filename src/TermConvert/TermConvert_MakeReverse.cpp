/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : TermConvert_MakeReverse.cpp
 *  Date     : 2002/02/18
 *  Modified : 
 *  
 *  Purpose  : make reverse pointer
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
#include <cstdio>

#include "feeldef.hpp"
#include "TermConvert.hpp"

#include "Element.hpp"
#include "Variable.hpp"

void TermConvert::MakeReverseTC(void)
{
  reverseTC = new TermConvert;


  // Reverse for system variables (x,y,z)
  reverseTC->storeConvertPair( "x", "qx");
  reverseTC->storeConvertPair( "y", "qy");
  reverseTC->storeConvertPair( "z", "qz");
  

  // reverse generator for _mXX symbols
  listIterator <Variable *>itrV(varPtrLst);

  for(itrV.init(); !itrV ; ++itrV) {
    Variable *vPtr = itrV();
    switch(vPtr->GetType()) {

    case VAR_FEM:
    case VAR_VFEM:
      ReverseAddVariableFEM( vPtr );
      break;
    

    case VAR_EWISE_A:
      if(vPtr->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
	ReverseAddVariableEWISEquad( vPtr );
      }
      else {
	ReverseAddVariableFEM( vPtr );
      }
      break;

    case VAR_EWISE:
      ReverseAddVariableEWISEmaterial( vPtr );
      break;

    case VAR_MATERIAL:
      ReverseAddVariableMaterial( vPtr );
      break;
    
    case VAR_DOUBLE:
    case VAR_INT:
    case VAR_CONST:
      ReverseAddVariableScalar( vPtr );
      break;
    
    default:
      assert(1==0);
    }
  }

  // element symbol _nXX converter
  listIterator <Element *>itrE(elementPtrLst);
  listIterator <int>      itrStno(elementStnoLst);

  itrStno.init();
  for(itrE.init(); !itrE; ++itrE) {

    int freedom = itrE()->GetElementFreedom();
    int stno    = itrStno();

    for(int i=0;i<freedom;i++) {
      
      char nbuf[BUFSIZ];
      char  buf[BUFSIZ];
      
      // function itself
      sprintf(nbuf,"_n%d%c",stno+i,'\0');
      sprintf( buf,"q%s_%d%c",itrE()->GetName(), i+1,'\0');
      reverseTC->storeConvertPair( nbuf,buf );

      // function x derivative
      sprintf(nbuf,"_n%d_dx%c",stno+i,'\0');
      sprintf( buf,"q%s_%d_x%c",itrE()->GetName(), i+1,'\0');
      reverseTC->storeConvertPair( nbuf,buf );

      // function y derivative
      sprintf(nbuf,"_n%d_dy%c",stno+i,'\0');
      sprintf( buf,"q%s_%d_y%c",itrE()->GetName(), i+1,'\0');
      reverseTC->storeConvertPair( nbuf,buf );

      // function z derivative
      sprintf(nbuf,"_n%d_dz%c",stno+i,'\0');
      sprintf( buf,"q%s_%d_z%c",itrE()->GetName(), i+1,'\0');
      reverseTC->storeConvertPair( nbuf,buf );
    }
    ++itrStno;
  }

  //  reverseTC->print(cerr);
  return;
}

void TermConvert::ReverseAddVariableFEM( Variable *vPtr)
{
  Element *ePtr;
  ePtr           = vPtr->GetElementPtr();

  // get freedom
  int      freedom;
  freedom        = ePtr->GetElementFreedom();

  // set startingSblNo
  int stno;
  stno = vPtr->GetSblNo();

  char mbuf[BUFSIZ],buf[BUFSIZ];

  for(int i=0;i<freedom;i++) {

    // from _mXX
    sprintf(buf,"_m%d%c",i+stno,'\0');

    // to fem_, ew_ etc.
    switch(vPtr->GetType()) {
    case VAR_FEM:
      sprintf(mbuf,"fem_%s_%d%c",vPtr->GetName(),i+1,'\0');
      break;

    case VAR_VFEM:
      sprintf(mbuf,"vfem_%s_%d%c",vPtr->GetName(),i+1,'\0');
      break;

    case VAR_EWISE_A:
      sprintf(mbuf,"ew_%s_%d%c",vPtr->GetName(),i+1,'\0');
      break;

    default:
      assert(1==0);
    }
    reverseTC->storeConvertPair( buf,mbuf );
  }
  return;
}

void TermConvert::ReverseAddVariableEWISEquad( Variable *vPtr )
{
  int stno;
  stno = vPtr->GetSblNo();
  
  char buf[BUFSIZ];
  char mbuf[BUFSIZ];
  sprintf(buf,"_m%d%c",stno,'\0');
  sprintf(mbuf,"ew_%s_q%c",vPtr->GetName(),'\0');
  reverseTC->storeConvertPair( buf,mbuf);

  return;
}
  
void TermConvert::ReverseAddVariableEWISEmaterial( Variable *vPtr )
{
  int stno;
  stno = vPtr->GetSblNo();

  char buf[BUFSIZ];
  char mbuf[BUFSIZ];
  sprintf(buf,"_m%d%c",stno,'\0');
  sprintf(mbuf,"ew_%s_m%c",vPtr->GetName(),'\0');
  reverseTC->storeConvertPair( buf,mbuf);

  return;
}

void TermConvert::ReverseAddVariableMaterial( Variable *vPtr )
{
  int stno;
  stno = vPtr->GetSblNo();

  char buf[BUFSIZ];
  char mbuf[BUFSIZ];
  sprintf(buf,"_m%d%c",stno,'\0');
  sprintf(mbuf,"m_%s%c",vPtr->GetName(),'\0');
  reverseTC->storeConvertPair( buf,mbuf);

  return;
}
  
void TermConvert::ReverseAddVariableScalar( Variable *vPtr )
{
  int stno;
  stno = vPtr->GetSblNo();

  char buf[BUFSIZ];
  char mbuf[BUFSIZ];
  sprintf(buf,"_m%d%c",stno,'\0');
  sprintf(mbuf,"sc_%s%c",vPtr->GetName(),'\0');
  reverseTC->storeConvertPair( buf,mbuf);

  return;
}
