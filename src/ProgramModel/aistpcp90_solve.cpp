/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000,2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : aistpcp90_solve.cpp
 *  Date     : 2002/06/28  (copy from feelfem90)
 *  Modified : 
 *  
 *  Purpose  : solve routine generator for aistpcp90 program model
 *             (derived from drama routine)
 *  
 *  1. I/O related routines (routine name)
 *  
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
#include "PM_aistpcp90.hpp"

#include "Neumann.hpp"
#include "Dirichlet.hpp"


// 1. I/O related routines

const char *PM_aistpcp90::GetSolveRoutineName( int no )
{
  char *ptr = new char[8];

  if(no >99) { std::cerr <<"Too large solve Number\n"; abortExit(1); }
  sprintf(ptr,"solve%d",no);

  return(ptr);
}

///////////////////////////////////////
// Do Solve functions
///////////////////////////////////////
void PM_aistpcp90::DoSolveStarters()
{
  SourceStarters();   // f90 version has no implicit here


  return;
}

void PM_aistpcp90::F90useSolvePM(Solve *solvePtr)
{
  
  writeSource("! modules for solve");
  writeSource("use femDataType");
  writeSource("use feelP2data");
  writeSource("use subsolveff90p2");     
  com();

  F90useAlways();  
  com();

  int solveNo,dconds,nconds;
  solveNo = solvePtr->GetSolveNo();
  dconds  = solvePtr->GetDconds();
  nconds  = solvePtr->GetNconds();

  writeSource("! solve family");
  pushSource("use mod_elem");
  pushSourceInt(solveNo);
  flushSource();


  for(int i=0;i<dconds;i++) {
    pushSource("use mod_dcond");
    pushSourceInt(solveNo);
    pushSource("_");
    pushSourceInt(i+1);    
    flushSource();
  }
  for(int i=0;i<nconds;i++) {
    pushSource("use mod_ncond");
    pushSourceInt(solveNo);
    pushSource("_");
    pushSourceInt(i+1);    
    flushSource();
  }

  // mod_ipdinfo
  pushSource("use mod_ipdinfo");
  pushSourceInt(solveNo);
  pushSource("_1");                   // P2 limitation, but not necessary enptr has several e
  flushSource();

  // mod_edev 
  pushSource("use mod_edev");
  pushSourceInt(solveNo);
  pushSource("_1");                   // P2 limitation, but not necessary enptr has several e
  flushSource();
  com();

}


// 2-2-1 variable definitions

void PM_aistpcp90::DoSolveVariableDefinitionsPM(Solve *solvePtr)
{
  // MPI related 
  writeSource("include 'mpif.h'");
  com();

  writeInteger4sc("myrank,nprocs");
  writeInteger4Ptr1("iedom");



  // auto variables
  COMMENTlong("auto variables");
  
  // integer(kind=INT4 )                        :: i,j");
  // integer(kind=INT4 )                        :: nelem,np,netype");
  // integer(kind=INT4 ),dimension(:,:),pointer :: ielem");
  // integer(kind=INT4 ),dimension(:)  ,pointer :: matno");
  writeInteger4sc("i,j,no");
  writeInteger4sc("nelem,np,netype");
  writeInteger4Ptr2("ielem");
  writeInteger4Ptr1("matno");

  com();

  // DRAMA auto variables
  // integer,dimension(:),pointer               :: ipd,ipf");
  // integer                                    :: neq");
  writeInteger4Ptr1("ipd,ipf");
  writeInteger4sc("neq");

  com();

  // ipdinfo
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  list <Variable *>vPLst = sePtr->GetUnknownVariablePtrLst();
  listIterator<Variable *>itrFEMv(vPLst);
  for(itrFEMv.init(); !itrFEMv; ++itrFEMv) {
    pushInteger4Ptr1();
    pushSource("ipd_");
    pushSource(itrFEMv()->GetName());
    flushSource();
  }


  // Solve Varible declaration
  // Problem dependent variables
  int dconds = solvePtr->GetDconds();
  int nconds = solvePtr->GetNconds();


  COMMENTlong("Problem dependent parameters");
  // integer                        :: edatno
  // integer                        :: nenfre(maxElementNodes,neg)
  writeInteger4sc("solveNo");
  writeInteger4sc("edatno");
  writeInteger4sc("nenfre(maxElementNodes,neg)");

  writeSource("type(solveInformation),pointer          :: solveInfoPtr");
  writeSource("type(boundaryDataSet) ,pointer          :: bDatSetPtr");

  //  if(dconds) {
    // integer                        :: nsetno(dirichletSets)
  //    writeInteger4sc("nsetno(dirichletSets)");
  //  }
  //  else {
  //    writeSource("! integer                      :: nsetno(dirichletSets)");
  //  }

  //  if(nconds) {
  //    writeSource("integer                        :: nbedtno(neumannSets)");
  //  }
  //  else {
  //    writeSource("! integer                       :: nbedtno(neumannSets)");
  //  }


  writeSource("!------------------------------------------------");
  writeSource("!  Element equation topology variable");
  writeSource("!------------------------------------------------");
  writeSource("integer                        :: ncmax         ! maximum number of elements");
  writeSource("                                                ! connecting one node");
  com();

  writeSource("integer                        :: ndfmax        ! maximum freedom for");
  writeSource("                                                ! one element");
  com();

  writeSource("integer                        :: nenfremax     ! maximum freedom per one node");
  writeSource("                                                ! for each element");
  com();

  writeSource("integer                        :: ncon          ! maximum freedom per one node");
  writeSource("                                                ! including connecting elements");



  return;
}

// 2-2-2 Parameters
void PM_aistpcp90::DoSolveParametersPM( Solve *solvePtr)
{
  DefaultParameterBlock();

  // Prolem dependent variables
  COMMENTlong("Problem dependent variables");

  // for P2 NEG is fixed
  writeSource("integer,parameter         :: neg = 1");

  // MAX_ELEMENT_NODES
  pushSource("integer,parameter         :: maxElementNodes = ");
  pushSourceInt(solvePtr->GetMaxnodes());
  flushSource();

  // Number of unknowns  P2 limited
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);  // 0 fix P2 limit
  pushSource("integer,parameter         :: numberOfUnknowns = ");
  pushSourceInt(sePtr->GetNumberOfUnknowns());
  flushSource();

  writeSource("integer,parameter         :: NDF_PCP = numberOfUnknowns");

  // NDC (number of Dirichlet conditions)
  pushSource("integer,parameter         :: dirichletSets =");
  pushSourceInt( solvePtr->GetDconds() );
  flushSource();

  // NNC (number of Neumann conditions)
  pushSource("integer,parameter         :: neumannSets =");  
  pushSourceInt( solvePtr->GetNconds() );
  flushSource();


  comment();
  return;
}

// 2-2-3 data statement

void PM_aistpcp90::DoSolveInitialDefPM(Solve *solvePtr)
{
  int dconds = solvePtr->GetDconds();
  int nconds = solvePtr->GetNconds();
  
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);  // 0 fix P2 limit
  Dirichlet    *dptr;
  Neumann      *nptr;


  // Data statement (Problem depenedent)
  COMMENTlong("Problem parameters");

  // nenfre P2 limited. only one SolveElement assumed.  P2LIMIT
  pushSource("data nenfre/");
  for(int i=0;i<solvePtr->GetMaxnodes();i++) {//maxnodes should be nodes in SE
    if(i!=0) pushSource(",");

    // aistpcp90 correct...
    if(sePtr->GetNode() <= i) pushSourceInt(0);
    else pushSourceInt(sePtr->GetNenfre(i));   // buggy...
  }
  pushSource("/");
  flushSource();
  
  com();

  return;
}

void PM_aistpcp90::DoSolveInitializerPM(Solve *solvePtr)
{
  //  report routine
  writeSource("if(myrank .eq. 0) then");

  pushSource( " call report('SOLVE ");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" START')");
  flushSource();

  writeSource("end if");
  com();

  // set edatno from solveLst
  pushSource("solveNo      =  ");
  pushSourceInt(solvePtr->GetSolveNo());
  flushSource();

  writeSource("solveInfoPtr => solveLst%solveDataList(solveNo)");
  writeSource("edatno       = solveInfoPtr%edatno");
  com();

  /* edatnolst,matnolst,conlst */
  COMMENTlong(" allocate enptr,con,matno in the next subroutine");
  writeSource("call setP2edat(edatno,firstEdatPtr,nelem,np,netype,ielem,matno)");

  com();

  // region edat check
  writeSource("if(np .NE. maxElementNodes) then");
  writeSource("  write(*,*) '**************************************'");
  writeSource("  write(*,*) '*           MESH ERROR               *'");
  writeSource("  write(*,*) '*                                    *'");
  writeSource("  write(*,*) '*  Number of nodes in one element is *'");
  writeSource("  write(*,*) '*  not what is expected.  Maybe mesh *'");
  writeSource("  write(*,*) '*  data mismatch.                    *'");
  writeSource("  write(*,*) '*                                    *'");
  writeSource("  write(*,*) '**************************************'");
  writeSource("  write(*,*)");
  writeSource("  stop '(Element type mismatches linear / quadratic, etc.)'");
  writeSource("endif");
  com();


  // number of dcond check
  writeSource("if(dirichletSets .NE. solveInfoPtr%dconds) then");
  writeSource("  write(*,*) '**************************************'");
  writeSource("  write(*,*) '*           MESH ERROR               *'");
  writeSource("  write(*,*) '*                                    *'");
  writeSource("  write(*,*) '*  Number of dirichlet conditions is *'");
  writeSource("  write(*,*) '*  not what is expect. Maybe mesh    *'");
  writeSource("  write(*,*) '*  data mismatch.                    *'");
  writeSource("  write(*,*) '*                                    *'");
  writeSource("  write(*,*) '**************************************'");
  writeSource("  write(*,*)");
  writeSource("  stop '(Number of Dirichlet condition mismatches.)'");
  writeSource("endif");
  com();

  // number of ncond check
  writeSource("if(neumannSets .NE. solveInfoPtr%nconds) then");
  writeSource("  write(*,*) '**************************************'");
  writeSource("  write(*,*) '*           MESH ERROR               *'");
  writeSource("  write(*,*) '*                                    *'");
  writeSource("  write(*,*) '*  Number of Neumann conditions is   *'");
  writeSource("  write(*,*) '*  not what is expect. Maybe mesh    *'");
  writeSource("  write(*,*) '*  data mismatch.                    *'");
  writeSource("  write(*,*) '*                                    *'");
  writeSource("  write(*,*) '**************************************'");
  writeSource("  write(*,*)");
  writeSource("  stop '(Number of Neumann condition mismatches.)'");
  writeSource("endif");
  com();
	      
  return;
}


// 2-3 start report routine

void PM_aistpcp90::DoSolveReport( int no, const char *s)
{
  pushSource(" call report('solve");
  pushSourceInt(no);
  pushSource(" : ");
  pushSource(s);
  pushSource("')");
  flushSource();

  return;
}



// Degree of freedom
void PM_aistpcp90::DoSolveDegreeOfFreedom(Solve *solvePtr)
{

  COMMENTlong(" Construct ipf,ipd");
  MODULEmallocERT("ipf","D.O.F of each node","npmax","1");
  MODULEmallocERT("ipd","Sumup D.O.F.",      "npmax","1");

  // ipdinfo
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  list <Variable *>vPLst = sePtr->GetUnknownVariablePtrLst();
  listIterator<Variable *>itrFEMv(vPLst);
  for(itrFEMv.init(); !itrFEMv; ++itrFEMv) {
    pushSource("allocate(");
    pushSource("ipd_");
    pushSource(itrFEMv()->GetName());
    pushSource("(npmax))");
    flushSource();
  }

  com();

  writeSource("call makeipfp2(nenfre,maxElementNodes,neg, &");
  writeSource("               ielem,nelem,np,npmax,ipf    )");
  com();

  writeSource("call makeipdp2(ipf,ipd,npmax,neq)");
  com();

  writeSource("call reportmodule('makeipf,makeipd')");
  com();

  // ipdinfo
  pushSource("call ipdinfo");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("_1(");                        // p2 limitation

  pushSource("npmax,ielem,nelem,np");

  for(itrFEMv.init(); !itrFEMv; ++itrFEMv) {
    pushSource(",");
    pushSource("ipd_");
    pushSource(itrFEMv()->GetName());
  }
  pushSource(")");
  flushSource();

  return;
}


// Assemble preparation, especially for parallel computation
void PM_aistpcp90::DoSolveAssemblyPreparation(Solve *solvePtr)
{
  // do nothing for scalar

  //  SubDoSolveMakeExtData(solve);   // generate calling sequence in solve

  return;
}


// Boundary data preparation

void PM_aistpcp90::DoSolveBoundaryDataPreparation(Solve *solvePtr)
{
  /* Neumann data preparation */
  
  comment();
  writeSource("! HALO area calcuration (if necessory)");
  comment();

  return;
}


///////////////////////////////////////
void PM_aistpcp90::DoSolveReturnSequence(Solve *solvePtr)
{
  
  pushSource("end subroutine ");
  pushSolveRoutineName( solvePtr->GetSolveNo());
  flushSource();

  pushSource("end module mod_");
  pushSolveRoutineName( solvePtr->GetSolveNo());
  flushSource();


  return;
}


void PM_aistpcp90::doSolveFreeMemoryPM(Solve *solvePtr)
{
  COMMENTlong("ProgramModel dependent memory deallocation");
  writeSource("deallocate(ipd,ipf)");
  
  // ipdinfo
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  list <Variable *>vPLst = sePtr->GetUnknownVariablePtrLst();
  listIterator<Variable *>itrFEMv(vPLst);
  for(itrFEMv.init(); !itrFEMv; ++itrFEMv) {
    pushSource("deallocate(");
    pushSource("ipd_");
    pushSource(itrFEMv()->GetName());
    pushSource(")");
    flushSource();  
  }
  
  return;
}
