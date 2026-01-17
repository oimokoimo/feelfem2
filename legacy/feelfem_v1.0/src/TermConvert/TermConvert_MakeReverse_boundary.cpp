/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : TermConvert_MakeReverse_boundary.cpp
 *  Date     : 2002/04/03 (copy of TermConvert_MakeReverse.cpp)
 *  Modified : 
 *  
 *  Purpose  : make reverse pointer
 *  
 */
#include <assert.h>
#include <stdio.h>

#include "feeldef.hpp"
#include "TermConvert.hpp"

#include "Element.hpp"
#include "Variable.hpp"

void TermConvert::MakeReverseTC_boundary(void)
{
  reverseTC = new TermConvert;

  // Reverse for system variables (x,y,z)
  reverseTC->storeConvertPair( "x", "qx");
  reverseTC->storeConvertPair( "y", "qy");
  reverseTC->storeConvertPair( "z", "qz");

  // for Normal components
  ReverseAddNormalComponent_boundary();


  // reverse generator for _mXX symbols
  listIterator <Variable *>itrV(varPtrLst);

  for(itrV.init(); !itrV ; ++itrV) {
    Variable *vPtr = itrV();
    switch(vPtr->GetType()) {

    case VAR_FEM:
    case VAR_VFEM:
      ReverseAddVariableFEM_boundary( vPtr );
      break;
    

    case VAR_EWISE_A:
      if(vPtr->GetEwiseType() == EWISE_TYPE_GAUSSPOINT) {
	ReverseAddVariableEWISEquad_boundary( vPtr );
      }
      else {
	ReverseAddVariableFEM_boundary( vPtr );
      }
      break;

    case VAR_EWISE:
      ReverseAddVariableEWISEmaterial_boundary( vPtr );
      break;
    
    case VAR_DOUBLE:
    case VAR_INT:
    case VAR_CONST:
      ReverseAddVariableScalar_boundary( vPtr );
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

    Element *bePtr = itrE()->AcquireBoundaryElementPtr();
    int freedom = bePtr->GetElementFreedom();
    int stno    = itrStno();

    for(int i=0;i<freedom;i++) {
      
      char nbuf[BUFSIZ];
      char  buf[BUFSIZ];

      // interpolation no in boundary  ( i+1 in region is bno here)
      int bno;   
      bno = bePtr->GetIthOriginalIplus1(i);
      
      // function itself
      sprintf(nbuf,"_n%d%c",stno+i,'\0');
      sprintf( buf,"q%s_%d%c",itrE()->GetName(), bno,'\0');  // bno was i+1
      reverseTC->storeConvertPair( nbuf,buf );

      // function x derivative
      sprintf(nbuf,"_n%d_dx%c",stno+i,'\0');
      sprintf( buf,"q%s_%d_x%c",itrE()->GetName(),bno,'\0'); // bno was i+1
      reverseTC->storeConvertPair( nbuf,buf );

      // function y derivative
      sprintf(nbuf,"_n%d_dy%c",stno+i,'\0');
      sprintf( buf,"q%s_%d_y%c",itrE()->GetName(),bno,'\0'); // bno was i+1
      reverseTC->storeConvertPair( nbuf,buf );

      // function z derivative
      sprintf(nbuf,"_n%d_dz%c",stno+i,'\0');
      sprintf( buf,"q%s_%d_z%c",itrE()->GetName(),bno,'\0'); // bno was i+1
      reverseTC->storeConvertPair( nbuf,buf );
    }
    ++itrStno;
  }

  //  reverseTC->print(cerr);
  return;
}

void TermConvert::ReverseAddVariableFEM_boundary( Variable *vPtr)
{
  Element *ePtr;
  ePtr           = vPtr->GetElementPtr();
  Element *bePtr;
  bePtr          = ePtr->AcquireBoundaryElementPtr();

  // get freedom
  int      freedom;
  freedom        = bePtr->GetElementFreedom();   // boundary

  // set startingSblNo
  int stno;
  stno = vPtr->GetSblNo();

  char mbuf[BUFSIZ],buf[BUFSIZ];

  for(int i=0;i<freedom;i++) {

    // interpolation no in boundary  ( i+1 in region is bno here)
    int bno;   
    bno = bePtr->GetIthOriginalIplus1(i);

    // from _mXX
    sprintf(buf,"_m%d%c",i+stno,'\0');

    // to fem_, ew_ etc.
    switch(vPtr->GetType()) {
    case VAR_FEM:
      sprintf(mbuf,"fem_%s_%d%c",vPtr->GetName(),bno,'\0');
      break;

    case VAR_VFEM:
      sprintf(mbuf,"vfem_%s_%d%c",vPtr->GetName(),bno,'\0');
      break;

    case VAR_EWISE_A:
      sprintf(mbuf,"ew_%s_%d%c",vPtr->GetName(),bno,'\0');
      break;

    default:
      assert(1==0);
    }
    reverseTC->storeConvertPair( buf,mbuf );
  }
  return;
}

void TermConvert::ReverseAddVariableEWISEquad_boundary( Variable *vPtr )
{
  
  assert(1==0);  // ewise_quad is not allowd in boundary integrand now

  int stno;
  stno = vPtr->GetSblNo();
  
  char buf[BUFSIZ];
  char mbuf[BUFSIZ];
  sprintf(buf,"_m%d%c",stno,'\0');
  sprintf(mbuf,"ew_%s_q%c",vPtr->GetName(),'\0');
  reverseTC->storeConvertPair( buf,mbuf);

  return;
}
  
void TermConvert::ReverseAddVariableEWISEmaterial_boundary( Variable *vPtr )
{
  assert(1==0);  // ewise_material is not allowd in boundary integrand now

  int stno;
  stno = vPtr->GetSblNo();

  char buf[BUFSIZ];
  char mbuf[BUFSIZ];
  sprintf(buf,"_m%d%c",stno,'\0');
  sprintf(mbuf,"ew_%s_m%c",vPtr->GetName(),'\0');
  reverseTC->storeConvertPair( buf,mbuf);

  return;
}
  
void TermConvert::ReverseAddVariableScalar_boundary( Variable *vPtr )
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

void TermConvert::ReverseAddNormalComponent_boundary(void)
{
  // for nx
  if(nxFlag == YES) {
    int stno = sblNoNX;
    char buf[BUFSIZ];
    sprintf(buf,"_m%d%c",stno,'\0');
    reverseTC->storeConvertPair( buf, "qnx" );
  }

  // for ny
  if(nyFlag == YES) {
    int stno = sblNoNY;
    char buf[BUFSIZ];
    sprintf(buf,"_m%d%c",stno,'\0');
    reverseTC->storeConvertPair( buf, "qny" );
  }

  // for nz
  if(nzFlag == YES) {
    int stno = sblNoNZ;
    char buf[BUFSIZ];
    sprintf(buf,"_m%d%c",stno,'\0');
    reverseTC->storeConvertPair( buf, "qnz" );
  }

  return;
}
