/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90_assign.cpp
 *  Date     : 2002/04/16 (BCN)
 *  Modified : 
 *  
 *  Purpose  : assign program generator instance for feelfem90 program model
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
#include <iostream>

#include "feeldef.hpp"
#include "feelfuncs.hpp"

#include "Assign.hpp"
#include "PM_feelfem90.hpp"

#include "list.hpp"
#include "GeomObj.hpp"
#include "RegionObject.hpp"

const char *PM_feelfem90::GetAssignRoutineName(int n)
{
  assert(n>0);
  int len = stringLength("let");
  if(n < 10) {
    len++;
  }
  else if(n < 100) {
    len+= 2;
  }
  else if(n < 1000) {
    len+= 3;
  }
  else {
    std::cerr << "too many assigns\n";
    assert(1==0);
  }
  
  len++;   // for '\0'

  char *ret = new char[len];
  sprintf(ret,"let%d%c",n,'\0');

  return(ret);
}
  
void PM_feelfem90::pushAssignRoutineName(Assign *asPtr)
{
  pushSource("let");
  pushSourceInt(asPtr->GetAssignNo());
  return;
}


// CO-ROUTINE
const char *PM_feelfem90::GetAssignCoRoutineName(int n)
{
  assert(n>0);
  int len = stringLength("colet");
  if(n < 10) {
    len++;
  }
  else if(n < 100) {
    len+= 2;
  }
  else if(n < 1000) {
    len+= 3;
  }
  else {
    std::cerr << "too many assigns\n";
    assert(1==0);
  }
  
  len++;   // for '\0'

  char *ret = new char[len];
  sprintf(ret,"colet%d%c",n,'\0');

  return(ret);
}

// CO-ROUTINE
void PM_feelfem90::pushAssignCoRoutineName(Assign *asPtr)
{
  pushSource("colet");
  pushSourceInt(asPtr->GetAssignNo());
  return;
}

void PM_feelfem90::DoAssignCoRoutineReturnSequence(Assign *asPtr)
{
  writeSource("return");
  com();
  
  pushSource("end subroutine ");
  pushAssignCoRoutineName(asPtr);
  flushSource();

  pushSource("end module mod_");
  pushAssignCoRoutineName(asPtr);
  flushSource();

  return;
}


// main routine
void PM_feelfem90::DoMainScheme_assign(Main *mPtr, Assign *asPtr)
{

  // write in main routine for debugging
  pushSource("! [");
  Variable *vvPtr = asPtr->GetLeftVarPtr();
  pushSource(vvPtr->GetName());
  pushSource(" = ");
  pushSource( asPtr->GetOriginalExprString() );
  pushSource("]");
  flushSource();

  pushSource("call ");
  pushAssignRoutineName(asPtr);
  pushSource("(");

  pushCoordinateSource();
  pushSource(",npmax");

  // geometry information
  switch( asPtr->GetGeometryType() ) {

  case ASSIGN_TYPE_NORMAL:  // no additional geometry information is needed
    break;             // do nothing
    
  case ASSIGN_TYPE_ELEM:
  case ASSIGN_TYPE_INTEGRAL:
    pushSource(",meshDat,firstEdatPtr,matData");
    break;

  case ASSIGN_TYPE_NSET:
    pushSource(",firstNsetPtr");
    break;
    
  case ASSIGN_TYPE_NODE:
    pushSource(",ipData");
    break;

  default:
    assert(1==0);

  }

  // variables
  pushVariableListInMain(asPtr->GetVarPtrList());
  pushSource(")");
  flushSource();
  com();

  return;
}

// assign subroutine
void PM_feelfem90::DoAssignRoutineHeader (Assign *asPtr)
{
  // module sentence
  pushSource("module mod_");
  pushAssignRoutineName(asPtr);
  flushSource();

  // contains
  writeSource("contains");
  
  // subroutine sentence
  pushSource("subroutine ");
  pushAssignRoutineName(asPtr);
  pushSource("(");

  // coordinates are always sent.
  pushCoordinateSource();
  pushSource(",npmax");

  // geometry information
  switch( asPtr->GetGeometryType() ) {

  case ASSIGN_TYPE_NORMAL:  // no additional geometry information is needed
    break;             // do nothing
    
  case ASSIGN_TYPE_ELEM:
  case ASSIGN_TYPE_INTEGRAL:
    pushSource(",meshDat,firstEdatPtr,matData");
    break;

  case ASSIGN_TYPE_NSET:
    pushSource(",firstNsetPtr");
    break;
    
  case ASSIGN_TYPE_NODE:
    pushSource(",ipData");
    break;

  default:
    assert(1==0);

  }

  // variables
  pushVariableListInCalled(asPtr->GetVarPtrList());
  pushSource(")");
  flushSource();
 
  //use
  SourceStarters();
  com();

  F90useAlways();
  
  // fem data type
  if(asPtr->GetGeometryType() != ASSIGN_TYPE_NORMAL) {
    F90useFEMDataType();
  }

  // coroutine
  if(asPtr->HasCoroutine()) {
    com();
    pushSource("use mod_");
    pushAssignCoRoutineName(asPtr);
    flushSource();
  }
  
  // user function  (if there is coroutine, it will be done at coroutine
  if(! asPtr->HasCoroutine()) {
    listIterator<string>itrufs(asPtr->GetUsedUserFuncStrList());
    for(itrufs.init();!itrufs;++itrufs) {
      pushSource("use mod_");
      pushSource(itrufs());
      flushSource();
    }
  }


  // implicit none
  com();
  fortImplicit();

  return;
}

void PM_feelfem90::DoAssignParameters( Assign *asPtr)
{

  // ???  oimokoimo

  return;
}

void PM_feelfem90::DoAssignVariableDefinitions(Assign *asPtr)
{
  // argument definition of coordinates, and npmax

  comment();

  CoordinateVariableDeclaration();
  writeInteger4sc("npmax");
  com();

  // arguments
  ArgumentVariableDeclarationLst( asPtr->GetVarPtrList() );
  com();

  // auto variables for loop counter
  switch(asPtr->GetLeftVarAssignType()) {
  case AS_VAR_TYPE_FEM_NODE:
    writeInteger4sc("i");
    com();
    break;

  default:
    break;
  }


  // auto variables for geometry
  switch(asPtr->GetGeometryType()){
  case ASSIGN_TYPE_NORMAL:  // no additional geometry information is needed
    break;             // do nothing
    
  case ASSIGN_TYPE_ELEM:
  case ASSIGN_TYPE_INTEGRAL:

    writeSource("type(edatList),pointer                  :: firstEdatPtr");
    writeSource("type(meshInformation)                   :: meshDat");
    writeSource("type(matdat),pointer                    :: matData");
    com();

    writeInteger4sc("edatno");
    writeInteger4sc("i,j");
    writeInteger4sc("nelem,np,netype");
    writeInteger4Ptr2("ielem");
    writeInteger4Ptr1("matno");


    // 
    if(asPtr->GetLeftVarAssignType() == AS_VAR_TYPE_EWISE_M) {

      // for ewise scalar variable
      if(asPtr->IsUseX()) {
	writeReal8sc("ex");
      }
      if(asPtr->IsUseY()) {
	writeReal8sc("ey");
      }
      if(asPtr->IsUseZ()) {
	writeReal8sc("ez");
      }
    }
    else {   

      // for ewise vector variable (use colet routine)
      if(asPtr->IsUseX()) {
	writeReal8sc("ex(NDP)");
      }
      if(asPtr->IsUseY()) {
	writeReal8sc("ey(NDP)");
      }
      if(asPtr->IsUseZ()) {
	writeReal8sc("ez(NDP)");
      }
    }
    com();

    break;

  case ASSIGN_TYPE_NSET:
    writeInteger4sc("i,,,koimo");
    break;
    
  case ASSIGN_TYPE_NODE:
    writeInteger4sc("nd");
    break;

  default:
    assert(1==0);

  }
  comment();
  return;
}

void PM_feelfem90::DoAssignGetGeometryData(Assign *asPtr)
{

  writeSource("not yet doassigngetgeometrydata");
}

void PM_feelfem90::DoAssignStatement(Assign *asPtr)
{

  com();
  switch(asPtr->GetLeftVarAssignType()) {

  case AS_VAR_TYPE_SCALAR:
    doAssignScalar(asPtr);
    break;

  case AS_VAR_TYPE_FEM_NODE:
    doAssignFEMnode(asPtr);
    break;

  case AS_VAR_TYPE_EWISE_M:
    doAssignEWISEmaterial(asPtr);
    break;

  default:
    writeSource(" Not implemented, now.");
    break;
  }

  return;
}

void PM_feelfem90::DoAssignReturnSequence(Assign *asPtr)
{
  writeSource("return");
  com();
  
  pushSource("end subroutine ");
  pushAssignRoutineName(asPtr);
  flushSource();

  pushSource("end module mod_");
  pushAssignRoutineName(asPtr);
  flushSource();

  return;
}

void PM_feelfem90::doAssignScalar(Assign *asPtr)
{
  pushSource("  ");
  pushVariableInCalled(asPtr->GetLeftVarPtr());
  pushSource("=");

  TermConvert tc;

  // x     ->  x(nd)  , etc
  // fem_u ->  fem_u(nd)
  // no ewise variable allowed here

  if(asPtr->IsUseX()) {
    tc.storeConvertPair( "x", "x(nd)");
  }
  if(asPtr->IsUseY()) {
    tc.storeConvertPair( "y", "y(nd)");
  }
  if(asPtr->IsUseZ()) {
    tc.storeConvertPair( "z", "z(nd)");
  }


  listIterator <Variable *>itrV(asPtr->GetVarPtrList());
  for(itrV.init(); !itrV ; ++itrV) {

    char bfrom[VARIABLE_TERMCONVERT_BUFSIZ];
    char bto  [VARIABLE_TERMCONVERT_BUFSIZ];

    switch(itrV()->GetType()) {
    case VAR_INT:
    case VAR_DOUBLE:
    case VAR_CONST:
      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"sc_%s%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_EWISE:
    case VAR_EWISE_A:
      std::cerr << "ewise variable must not be appeared here.\n";
      assert(1==0);  

    case VAR_MATERIAL:
      std::cerr << "material variable must not be appeared here.\n";
      assert(1==0);  

    case VAR_FEM:
      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"fem_%s(nd)%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_VFEM:
      std::cerr << "Not implemented...???\n";
      assert(1==0);

    default:
      assert(1==0);

    }
  }
  
  string exprF90Str = tc.convertExpressionString(asPtr->GetExprString());
  
  pushSource( exprF90Str );
  
  flushSource();
  com();

  return;
}

void PM_feelfem90::doAssignFEMnode(Assign *asPtr)
{
  // do loop
  writeSource("do i=1,npmax");
  com();

  pushSource("  ");
  pushVariableInCalled(asPtr->GetLeftVarPtr());
  pushSource("(i)=");

  TermConvert tc;

  // x     ->  x(nd)  , etc
  // fem_u ->  fem_u(nd)
  // no ewise variable allowed here

  if(asPtr->IsUseX()) {
    tc.storeConvertPair( "x", "x(i)");
  }
  if(asPtr->IsUseY()) {
    tc.storeConvertPair( "y", "y(i)");
  }
  if(asPtr->IsUseZ()) {
    tc.storeConvertPair( "z", "z(i)");
  }


  listIterator <Variable *>itrV(asPtr->GetVarPtrList());
  for(itrV.init(); !itrV ; ++itrV) {

    char bfrom[VARIABLE_TERMCONVERT_BUFSIZ];
    char bto  [VARIABLE_TERMCONVERT_BUFSIZ];

    switch(itrV()->GetType()) {
    case VAR_INT:
    case VAR_DOUBLE:
    case VAR_CONST:
      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"sc_%s%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_EWISE:
    case VAR_EWISE_A:
      std::cerr << "ewise variable must not be appeared here.\n";
      assert(1==0);  

    case VAR_MATERIAL:
      std::cerr << "material variable must not be appeared here.\n";
      assert(1==0);

    case VAR_FEM:
      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"fem_%s(i)%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_VFEM:
      std::cerr << "Not implemented...???\n";
      assert(1==0);

    default:
      assert(1==0);

    }
  }
  
  string exprF90Str = tc.convertExpressionString(asPtr->GetExprString());

  if(strindex(exprF90Str,"^(1/2)")) assert(1==0);
  
  pushSourceHAT( exprF90Str ); 

  flushSource();
  com();

  writeSource("end do");

  return;
}

void PM_feelfem90::doAssignEWISEmaterial(Assign *asPtr)
{
  // do loop

  //EDAT1
  writeSource("edatno = meshDat%mainEdatNo");
  writeSource("call setP2edat(edatno,firstEdatPtr,nelem,np,netype,ielem,matno)");
  com();


  TermConvert tc;

  // x     ->  ex
  // fem_u ->  fe m_u(nd)
  // only material ewise allowed.

  if(asPtr->IsUseX()) {
    tc.storeConvertPair( "x", "ex");
  }
  if(asPtr->IsUseY()) {
    tc.storeConvertPair( "y", "ey");
  }
  if(asPtr->IsUseZ()) {
    tc.storeConvertPair( "z", "ez");
  }

  listIterator <Variable *>itrV(asPtr->GetVarPtrList());
  for(itrV.init(); !itrV ; ++itrV) {

    char bfrom[VARIABLE_TERMCONVERT_BUFSIZ];
    char bto  [VARIABLE_TERMCONVERT_BUFSIZ];

    switch(itrV()->GetType()) {
    case VAR_INT:
    case VAR_DOUBLE:
    case VAR_CONST:
      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"sc_%s%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_EWISE:
      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"ew_%s(i)%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );      
      break;

    case VAR_MATERIAL:
      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"m_%s(matno(i))%c",itrV()->GetName(),'\0');
      tc.storeConvertPair( bfrom, bto );      
      break;

    case VAR_EWISE_A:
      std::cerr << "ewise variable must not be appeared here.\n";
      assert(1==0);  

    case VAR_FEM:
      std::cerr << "fem var in ewise-material is UC.\n";
      assert(1==0);

      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"fem_%s(i)%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_VFEM:
      std::cerr << "Not implemented...???\n";
      assert(1==0);

    default:
      assert(1==0);

    }
  }
  // Right hand side formula
  string exprF90Str = tc.convertExpressionString(asPtr->GetExprString());

  // Geometry is specified,
  int matGeoms = asPtr->GetNumberOfPlaces();

  // check program for materials are assigned are not.
  if(matGeoms > 0) {

    listIterator <GeomObj *> itrRGeom(asPtr->GetGeomObjPtrList());
    for(itrRGeom.init();!itrRGeom;++itrRGeom) {

      RegionObject *robjPtr = (RegionObject *)itrRGeom();

      // if corresponding no is -1
      pushSource("if(matData%regmat(");
      pushSourceInt(robjPtr->GetPropertyNo());
      pushSource(") == -1) then");
      flushSource();

      // write warting
      pushSource("  write(*,*) 'Warning: Material [");
      pushSource(robjPtr->GetName());
      pushSource("] is not assigned.'");
      flushSource();

      // endif
      writeSource("end if");
      com();
      com();
    }
  }

  // Element loop starts here
  writeSource("do i=1,nelem");
  com();


  if(matGeoms > 0) {
    
    listIterator <GeomObj *> itrRGeom(asPtr->GetGeomObjPtrList());
    for(itrRGeom.init();!itrRGeom;++itrRGeom) {
      RegionObject *robjPtr = (RegionObject *)itrRGeom();
      pushSource("  if(matno(i) == ");

      pushSource("matData%regmat(");
      pushSourceInt(robjPtr->GetPropertyNo());    // matData%regmat(*) is crsp
      pushSource(")");

      pushSource(" ) then          ! Region ");
      pushSource(robjPtr->GetName());
      flushSource();

      // assignment

      // ewise material(duplicate No.1 of 2)
      if( asPtr->IsUseX() ||  asPtr->IsUseY() ||  asPtr->IsUseZ() ) {

	com();
	if( asPtr->IsUseX() ) writeSource("   ex = 0.0");
	if( asPtr->IsUseY() ) writeSource("   ey = 0.0");
	if( asPtr->IsUseZ() ) writeSource("   ez = 0.0");
    
	writeSource("   do j=1,np");

	if( asPtr->IsUseX() ) writeSource("    ex = ex+x(ielem(j,i))");
	if( asPtr->IsUseY() ) writeSource("    ey = ey+y(ielem(j,i))");
	if( asPtr->IsUseZ() ) writeSource("    ez = ez+z(ielem(j,i))");
    
	writeSource("   end do");

	if( asPtr->IsUseX() ) writeSource("   ex = ex/np");
	if( asPtr->IsUseY() ) writeSource("   ey = ey/np");
	if( asPtr->IsUseZ() ) writeSource("   ez = ez/np");
	com();
      }
      // end of duplicate No. 1. of 2

      pushSource("   ");
      pushVariableInCalled(asPtr->GetLeftVarPtr());
      pushSource("(i)=");
      pushSource( exprF90Str );
      flushSource();
      com();
      
      // endif
      writeSource("  endif");
      com();
    }
  }
  else {

    // ewise material (duplicate  No.2 of 2)
    if( asPtr->IsUseX() ||  asPtr->IsUseY() ||  asPtr->IsUseZ() ) {

      if( asPtr->IsUseX() ) writeSource("  ex = 0.0");
      if( asPtr->IsUseY() ) writeSource("  ey = 0.0");
      if( asPtr->IsUseZ() ) writeSource("  ez = 0.0");
    
      writeSource("  do j=1,np");
      
      if( asPtr->IsUseX() ) writeSource("   ex = ex+x(ielem(j,i))");
      if( asPtr->IsUseY() ) writeSource("   ey = ey+y(ielem(j,i))");
      if( asPtr->IsUseZ() ) writeSource("   ez = ez+z(ielem(j,i))");
    
      writeSource("  end do");

      if( asPtr->IsUseX() ) writeSource("  ex = ex/np");
      if( asPtr->IsUseY() ) writeSource("  ey = ey/np");
      if( asPtr->IsUseZ() ) writeSource("  ez = ez/np");
      com();
    }  // end of duplicate (No. 2  of 2)

    pushSource("  ");
    pushVariableInCalled(asPtr->GetLeftVarPtr());
    pushSource("(i)=");
  
    pushSource( exprF90Str );
    flushSource();
    com();
  }

  writeSource("end do");
  com();

  return;
}
