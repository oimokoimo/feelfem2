/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : aistpcp90_assign.cpp
 *  Date     : 2002/04/16 (BCN)
 *  Modified : 
 *  
 *  Purpose  : assign program generator instance for aistpcp90 program model
 *  
 */

#include <assert.h>
#include <iostream.h>
#include <stdio.h>

#include "feeldef.hpp"
#include "feelfuncs.hpp"

#include "Assign.hpp"
#include "PM_aistpcp90.hpp"

#include "list.hpp"
#include "GeomObj.hpp"
#include "RegionObject.hpp"

char *PM_aistpcp90::GetAssignRoutineName(int n)
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
    cerr << "too many assigns\n";
    assert(1==0);
  }
  
  len++;   // for '\0'

  char *ret = new char[len];
  sprintf(ret,"let%d%c",n,'\0');

  return(ret);
}
  
void PM_aistpcp90::pushAssignRoutineName(Assign *asPtr)
{
  pushSource("let");
  pushSourceInt(asPtr->GetAssignNo());
  return;
}

// main routine
void PM_aistpcp90::DoMainScheme_assign(Main *mPtr, Assign *asPtr)
{
  pushSource("call ");
  pushAssignRoutineName(asPtr);
  pushSource("(myrank,nprocs,iedom,");

  pushCoordinateSource();
  pushSource(",npmax");

  // geometry information
  switch( asPtr->GetGeometryType() ) {

  case ASSIGN_TYPE_NORMAL:  // no additional geometry information is needed
    break;             // do nothing
    
  case ASSIGN_TYPE_ELEM:
    pushSource(",firstEdatPtr,matData");
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
void PM_aistpcp90::DoAssignRoutineHeader (Assign *asPtr)
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
  pushSource("(myrank,nprocs,iedom,");

  // coordinates are always sent.
  pushCoordinateSource();
  pushSource(",npmax");

  // geometry information
  switch( asPtr->GetGeometryType() ) {

  case ASSIGN_TYPE_NORMAL:  // no additional geometry information is needed
    break;             // do nothing
    
  case ASSIGN_TYPE_ELEM:
    pushSource(",firstEdatPtr,matData");
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

  // implicit none
  fortImplicit();

  return;
}

void PM_aistpcp90::DoAssignParameters( Assign *asPtr)
{

  // ???  oimokoimo

  return;
}

void PM_aistpcp90::DoAssignVariableDefinitions(Assign *asPtr)
{
  // argument definition of coordinates, and npmax

  comment();

  CoordinateVariableDeclaration();
  writeInteger4sc("myrank,nprocs");
  writeInteger4Ptr1("iedom");
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

    writeSource("type(edatList),pointer                  :: firstEdatPtr");
    writeSource("type(matdat),pointer                    :: matData");
    com();

    writeInteger4sc("i");
    writeInteger4sc("nelem,np,netype");
    writeInteger4Ptr2("ielem");
    writeInteger4Ptr1("matno");

    if(asPtr->IsUseX()) {
      writeReal8sc("ex");
    }
    if(asPtr->IsUseY()) {
      writeReal8sc("ey");
    }
    if(asPtr->IsUseZ()) {
      writeReal8sc("ez");
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

void PM_aistpcp90::DoAssignGetGeometryData(Assign *asPtr)
{

  writeSource("not yet doassigngetgeometrydata");
}

void PM_aistpcp90::DoAssignStatement(Assign *asPtr)
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
void PM_aistpcp90::DoAssignReturnSequence(Assign *asPtr)
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

void PM_aistpcp90::doAssignScalar(Assign *asPtr)
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
  if(asPtr->IsUseX()) {
    tc.storeConvertPair( "y", "y(nd)");
  }
  if(asPtr->IsUseX()) {
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
      cerr << "ewise variable must not be appeared here.\n";
      assert(1==0);  

    case VAR_FEM:
      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"fem_%s(nd)%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_VFEM:
      cerr << "Not implemented...???\n";
      assert(1==0);
    }
  }
  
  string exprF90Str = tc.convertExpressionString(asPtr->GetExprString());
  
  pushSource( exprF90Str );
  
  flushSource();
  com();

  return;
}

void PM_aistpcp90::doAssignFEMnode(Assign *asPtr)
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
  if(asPtr->IsUseX()) {
    tc.storeConvertPair( "y", "y(i)");
  }
  if(asPtr->IsUseX()) {
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
      cerr << "ewise variable must not be appeared here.\n";
      assert(1==0);  

    case VAR_FEM:
      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"fem_%s(i)%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_VFEM:
      cerr << "Not implemented...???\n";
      assert(1==0);
    }
  }
  
  string exprF90Str = tc.convertExpressionString(asPtr->GetExprString());
  
  pushSource( exprF90Str );
  flushSource();
  com();

  writeSource("end do");

  return;
}

void PM_aistpcp90::doAssignEWISEmaterial(Assign *asPtr)
{
  // do loop

  //EDAT1
  writeSource("call setP2edat(1,firstEdatPtr,nelem,np,netype,ielem,matno)");
  com();


  TermConvert tc;

  // x     ->  ex
  // fem_u ->  fe m_u(nd)
  // only material ewise allowed.

  if(asPtr->IsUseX()) {
    tc.storeConvertPair( "x", "ex");
  }
  if(asPtr->IsUseX()) {
    tc.storeConvertPair( "y", "ey");
  }
  if(asPtr->IsUseX()) {
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

    case VAR_EWISE_A:
      cerr << "ewise variable must not be appeared here.\n";
      assert(1==0);  

    case VAR_FEM:
      cerr << "fem var in ewise-material is UC.\n";
      assert(1==0);

      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"fem_%s(i)%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_VFEM:
      cerr << "Not implemented...???\n";
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
      pushSource("   ");
      pushVariableInCalled(asPtr->GetLeftVarPtr());
      pushSource("(i)=");
      pushSource( exprF90Str );
      flushSource();
      
      // endif
      writeSource("  endif");
      com();
    }
  }
  else {

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
