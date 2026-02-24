/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90DRAMA_dirichlet.cpp
 *  Date     : 2000/10/18
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : feelfem90 programming style implementation 
 *             DRAMA double index parallel version
 *
 *             DIRICHLET related generator routines
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
 *
 */

#include "feelfuncs.hpp"
#include "Dirichlet.hpp"
#include "PM_feelfem90DRAMA.hpp"

// Routine name

void PM_feelfem90DRAMA::pushDirichletRoutineName(int solveNo, int dcondNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"dcond%d_%d",solveNo,dcondNo);
  pushSource(buf);

  return;

}


void PM_feelfem90DRAMA::F90useDirichletPM()
{
  F90useFEMDataType();
  writeSource("use subSolveDrama     ! nd_search function");
  F90useAlways();
}

//////////////////////////////////////////
// Dirichlet Conditions related functions
//////////////////////////////////////////
//char *PM_feelfem90DRAMA::dirichletP2DOTEMP( char *st )
//{
//  int strindex(const char *,const char *);
//  int i;
//  static char buf[BUFSIZ];
//  for(i=0;*st != '\0'; i++) {
//    buf[i] = *st;
//    st++;
//  }
//  buf[i] = '\0';
//  
//  int n;
//  while( n = strindex(buf,"(ip)")) {
//    buf[n-1] = '_';
//    buf[n  ] = 'd';
//    buf[n+1] = 'p';
//    buf[n+2] = 't';
//  }
//
//  return(buf);
//}


const char *PM_feelfem90DRAMA::GetDirichletRoutineName(int solveNo, int dcondNo)
{
  int length = stringLength("dcond?_?");
  if(solveNo > 9) {
    length++;
    if(solveNo >99) {
      std::cerr <<"solve number too large(GetDirichletRoutineName)\n";
      abortExit(1);
    }
  }

  if(dcondNo > 9){
    length++;
    if(dcondNo >99) {
      std::cerr <<"dcond number too large(GetDirichletRoutineName)\n";
      abortExit(1);
    }
  }

  char *ptr = new char[length];

  sprintf(ptr,"dcond%d_%d",solveNo,dcondNo);    // PMDependent

  return(ptr);
}


void PM_feelfem90DRAMA::DoDirichletArgumentVariableDefinitionsPM(Dirichlet *dPtr)
{
  writeSource("integer,intent(in)           :: mypeid,nprocs");
  writeSource("integer,intent(in)           :: nsetno");
  writeSource("type(dramaNsetList),pointer  :: firstDramaNsetPtr");
  com();

  writeSource("integer,dimension(nprocs)    :: isumup");
  writeSource("integer,intent(in)           :: neq");
  com();

  writeSource("integer,dimension(:,:)       :: enptr,con");
  writeSource("integer,intent(in)           :: nelem");
  com();

  writeSource("integer,intent(in)           :: npmax");
  CoordinateVariableDeclaration();
  writeSource("integer,dimension(npmax)     :: ipf,ipd");
  com();
  
  writeSource("integer,dimension(:,:)       :: enptr_ex,con_ex");
  writeSource("integer,intent(in)           :: nelem_ex");
  writeSource("integer,intent(in)           :: nouter");
  writeSource("integer,dimension(nouter)    :: ndno,peno,ipf_ex,ipd_ex");
  CoordinateExternalVariableDeclaration();
  com();

  orderedPtrList <Variable *> varPtrLst = dPtr->GetVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);

  // FEM variables for EX 
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;
    FEMExternalVariableDeclaration( itr());
  }
  com();

  return;
}

void PM_feelfem90DRAMA::doDirichletAutoVariableDefinitionsPM(Dirichlet *dPtr)
{
  COMMENTlong(" auto variables for dirichlet");
  writeSource("integer                        :: i,j,k");
  writeSource("integer                        :: nd");
  writeSource("integer                        :: ind,ipe");
  writeSource("integer                        :: ieq,jeq");
  writeSource("integer                        :: nodes");
  writeSource("integer                        :: np");
  writeSource("integer,dimension(:,:),pointer :: dcon,dinfo");
  writeSource("integer                        :: myeqfrom,myeqto");
  com(); 

  switch(getSpaceDimension()) {
  case 1:
    writeSource("real(kind=REAL8)               :: x_dpt,u");
    break;
  case 2:
    writeSource("real(kind=REAL8)               :: x_dpt,y_dpt,u");
    break;
  case 3:
    writeSource("real(kind=REAL8)               :: x_dpt,y_dpt,z_dpt,u");
    break;
  }
  orderedPtrList <Variable *> varPtrLst = dPtr->GetVariablePtrLst();
  // FEM variables for EX 
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;
    pushSource("real(kind=REAL8)               :: ");
    pushFEMVariableInCalled(itr());
    pushSource("_dpt");
    flushSource();
  }
  com();


  return;
}




void PM_feelfem90DRAMA::DoDirichletReturnSequencePM(Dirichlet *dPtr)
{
  com();
  pushSource("end subroutine ");
  pushSource(GetDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo() ));
  flushSource();

  pushSource("end module mod_");
  pushSource(GetDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo() ));
  flushSource();

  return;
}

void PM_feelfem90DRAMA::doSetDirichletValue(Dirichlet *dPtr)
{
  pushSource( "   u = ");

  // Make termconvert

  TermConvert tc;

  tc.storeConvertPair("x","x_dpt");
  tc.storeConvertPair("y","y_dpt");
  tc.storeConvertPair("z","z_dpt");

  listIterator <Variable *>itrV(dPtr->GetVariablePtrLst());

  char from[MAX_VARNAME_LENGTH],to[MAX_VARNAME_LENGTH];
  
  for(itrV.init(); !itrV ; ++itrV ) {
    
    switch(itrV()->GetType() ) {
      
    case VAR_FEM:
      sprintf(from,"%s%c",itrV()->GetName(),'\0');
      sprintf(to  ,"fem_%s_dpt%c",itrV()->GetName(),'\0');
      tc.storeConvertPair(from,to);
      break;

    case VAR_DOUBLE:
    case VAR_CONST:
    case VAR_INT:
      sprintf(from,"%s%c",itrV()->GetName(),'\0');
      sprintf(to  ,"sc_%s%c",itrV()->GetName(),'\0');
      tc.storeConvertPair(from,to);
      break;

    default:
      assert(1==0);
    }
  }

  pushSource( tc.convertExpressionString( dPtr->GetExprStr() ));



  flushSource();  
  com();

  return;
}

void PM_feelfem90DRAMA::DoDirichletInitializer(Dirichlet *dPtr)
{
  com();
  writeSource("myeqfrom = 1   ! AMG/CRS Global number for my equation");
  writeSource("myeqto   = neq ! AMG/CRS Global number for my equation");
  com();
  
  writeSource("call setdramanset(nsetno,firstDramaNsetPtr,nodes,np,dcon,dinfo)");
}

void PM_feelfem90DRAMA::DoDirichletLoopStart(Dirichlet *dPtr)
{
  comment();
  writeSource("do 100 i=1,nodes");
  return;
}

void PM_feelfem90DRAMA::DoDirichletCalcBoundaryValue(Dirichlet *dPtr)
{
  com();

  writeSource("  ind = dcon(1,i)");
  writeSource("  ipe = dcon(2,i)");

  comment();
  writeSource("! If the Dirichlet node is in my PE region, row and column");
  writeSource("! If the Dirichlet node is NOT in my PE region,");
  writeSource("! and it relates my region, column");
  comment();

  writeSource("  if(ipe .NE. mypeid) then");
  writeSource("    nd = ndsearch_ex2(ind,ipe,ndno,peno,nouter)");
  writeSource("    if(nd .LT. 1) goto 100");
  com();

  writeSource("    ieq = 0");
  writeSource("    jeq = ipd_halo(nd)+dinfo(1,i)+neq      ! PAMG/CRS");
  com();

  switch(getSpaceDimension()) {
  case 1:
    writeSource("    x_dpt = x_ex(nd)");
    break;

  case 2:
    writeSource("    x_dpt = x_ex(nd)");
    writeSource("    y_dpt = y_ex(nd)");
    break;

  case 3:
    writeSource("    x_dpt = x_ex(nd)");
    writeSource("    y_dpt = y_ex(nd)");
    writeSource("    z_dpt = z_ex(nd)");
    break;
  }

  /* External FEM Variable */
  orderedPtrList <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);

  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;

    pushSource("    ");
    pushFEMVariableInCalled(itr());
    pushSource("_dpt = ");
    pushFEMVariableExternalInCalled(itr());      // external variable
    pushSource("(nd)");
    flushSource();
  }

  com();
  writeSource("   else");
  com();

  writeSource("    ieq = ipd(ind)+dinfo(1,i)");
  writeSource("    jeq = ieq                   ! AMG/CRS local eq number for my own");
  com();

  switch(getSpaceDimension()) {
  case 1:
    writeSource("    x_dpt = x(ind)");
    break;

  case 2:
    writeSource("    x_dpt = x(ind)");
    writeSource("    y_dpt = y(ind)");
    break;

  case 3:
    writeSource("    x_dpt = x(ind)");
    writeSource("    y_dpt = y(ind)");
    writeSource("    z_dpt = z(ind)");
    break;
  }


  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;
    
    pushSource("        ");
    pushFEMVariableInCalled(itr());
    pushSource("_dpt = ");
    pushFEMVariableInCalled(itr());              // own variable
    pushSource("(ind)");
    flushSource();
  }
  com();

  writeSource("  endif");
  com();  


  doSetDirichletValue(dPtr);

  return;
}

void PM_feelfem90DRAMA::DoDirichletLoopEnd(Dirichlet *dPtr)
{
  com();
  writeSource(" 100  continue");
  comment();

  return;
}

void PM_feelfem90DRAMA::doIthDirichletCallInSolvePM(Solve *solvePtr,int i)
{

  pushSource("! No.");
  pushSourceInt(i+1);
  flushSource();

  com();

  pushSource("bdatSetPtr => solveInfoPtr%dlst(");
  pushSourceInt(i+1);
  pushSource(")");
  flushSource();
  com();

  writeSource("do i=1,bdatSetPtr%nofsets");
  com();

  writeSource("  no = bDatSetPtr%datlist(i)");

  pushSource("  call ");
  pushDirichletRoutineName(solvePtr->GetSolveNo(),i+1);
  pushSource("(mypeid,nprocs,                       &");
  flushSource();

  pushSource("       no,firstDramaNsetPtr,                &");
  flushSource();

  writeSource("       isumup,                                     &");
  writeSource("       enptr,con,nelem,                            &");

  pushSource( "       ");
  pushCoordinateSource();
  pushSource(",ipf,ipd,npmax,                          &");
  flushSource();

  writeSource("       enptr_ex,con_ex,nelem_ex,                   &");
 
  pushSource("       ndno,peno,");
  pushCoordinateExternalSource();
  pushSource(",ipf_ex,ipd_ex,nouter    &");
  flushSource();

  pushSource("       ");
  pushVariableAndFEMExternalListInCalled(solvePtr->GetIthDirichletVariablePtrLst(i));

  return;

}

void PM_feelfem90DRAMA::doIthDirichletCallInSolvePM2(Solve *solvePtr,int i)
{
  writeSource("end do");
  com();
}
