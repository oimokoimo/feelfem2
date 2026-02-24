/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90vec_solve.cpp
 *  Date     : 2001/11/29 (Copy from feelfem90_solve.cpp)
 *  Modified : 
 *  
 *  Purpose  : solve routine generator for feelfem90vec program model
 *             (derived from drama routine)
 *  
 *  1. I/O related routines (routine name)
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
#include "PM_feelfem90vec.hpp"


// 1. I/O related routines

const char *PM_feelfem90vec::GetSolveRoutineName( int no )
{
  char *ptr = new char[8];

  if(no >99) { std::cerr <<"Too large solve Number\n"; abortExit(1); }
  sprintf(ptr,"solve%d",no);

  return(ptr);
}

///////////////////////////////////////
// Do Solve functions
///////////////////////////////////////
void PM_feelfem90vec::DoSolveStarters()
{
  SourceStarters();   // f90 version has no implicit here

  return;
}

void PM_feelfem90vec::F90useSolvePM(Solve *solvePtr)
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

  // mod_edev 
  pushSource("use mod_edev");
  pushSourceInt(solveNo);
  pushSource("_1");                   // P2 limitation, but not necessary enptr has several e
  flushSource();
  com();

}


// 2-2-1 variable definitions

void PM_feelfem90vec::DoSolveVariableDefinitionsPM(Solve *solvePtr)
{
  // auto variables
  COMMENTlong("auto variables");
  
  writeSource("integer(kind=INT4 )                        :: i,j");
  writeSource("integer(kind=INT4 )                        :: nelem,np,netype");
  writeSource("integer(kind=INT4 ),dimension(:,:),pointer :: ielem");
  writeSource("integer(kind=INT4 ),dimension(:)  ,pointer :: matno");
  com();

  // DRAMA auto variables
  writeSource("integer,dimension(:),pointer               :: ipd,ipf");
  writeSource("integer                                    :: neq");
  com();

  // Solve Varible declaration
  // Problem dependent variables
  int dconds = solvePtr->GetDconds();
  int nconds = solvePtr->GetNconds();


  COMMENTlong("Problem dependent parameters");
  writeSource("integer                        :: edatno");
  writeSource("integer                        :: nenfre(maxElementNodes,neg)");

  if(dconds) {
    writeSource("integer                        :: nsetno(dirichletSets)");
  }
  else {
    writeSource("! integer                        :: nsetno(dirichletSets)");
  }

  if(nconds) {
    writeSource("integer                        :: nbedtno(neumannSets)");
  }
  else {
    writeSource("! integer                        :: nbedtno(neumannSets)");
  }
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
void PM_feelfem90vec::DoSolveParametersPM( Solve *solvePtr)
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

void PM_feelfem90vec::DoSolveInitialDefPM(Solve *solvePtr)
{
  int dconds = solvePtr->GetDconds();
  int nconds = solvePtr->GetNconds();
  
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);  // 0 fix P2 limit
  Dirichlet    *dptr;
  Neumann      *nptr;


  // Data statement (Problem depenedent)
  COMMENTlong("Problem parameters");
  /* EDATNO oimo P2 limited */
  pushSource("data edatno/");
  pushSourceInt(sePtr->GetEdatno());
  pushSource("/");
  flushSource();


  pushSource("data nenfre/");
  for(int i=0;i<solvePtr->GetMaxnodes();i++) {//maxnodes should be nodes in SE
    if(i!=0) pushSource(",");
    pushSourceInt(sePtr->GetNenfre(i));
  }
  pushSource("/");
  flushSource();
  
  if(dconds) {
    pushSource("data nsetno/");
    for(int i=0;i<dconds;i++) {
      if(i!=0) pushSource(",");
      pushSourceInt(solvePtr->GetIthDirichletNsetno(i));
    }
    pushSource("/");
    flushSource();
  }
  
  if(nconds) {
    pushSource("data nbedtno/");
    for(int i=0;i<nconds;i++) {
      if(i!=0) pushSource(",");
      pushSourceInt(solvePtr->GetIthNeumannNbedtno(i));
    }
    pushSource("/");
    flushSource();
  }

  com();
  return;
}

void PM_feelfem90vec::DoSolveInitializerPM(Solve *solvePtr)
{

  //  report routine
  pushSource( "call report('SOLVE ");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" START')");
  flushSource();
  

  /* edatnolst,matnolst,conlst */
  COMMENTlong(" allocate enptr,con,matno in the next subroutine");
  writeSource("call setP2edat(edatno,firstEdatPtr,nelem,np,netype,ielem,matno)");

  
  return;
}



// 2-3 start report routine

void PM_feelfem90vec::DoSolveReport( int no, const char *s)
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
void PM_feelfem90vec::DoSolveDegreeOfFreedom(Solve *solvePtr)
{

  COMMENTlong(" Construct ipf,ipd");
  MODULEmallocERT("ipf","D.O.F of each node","npmax","1");
  MODULEmallocERT("ipd","Sumup D.O.F.",      "npmax","1");
  com();

  writeSource("call makeipfp2(nenfre,maxElementNodes,neg, &");
  writeSource("               ielem,nelem,np,npmax,ipf    )");
  com();

  writeSource("call makeipdp2(ipf,ipd,npmax,neq)");
  com();

  writeSource("call reportmodule('makeipf,makeipd')");
  com();

  return;
}


// Assemble preparation, especially for parallel computation
void PM_feelfem90vec::DoSolveAssemblyPreparation(Solve *solvePtr)
{
  // do nothing for scalar

  //  SubDoSolveMakeExtData(solve);   // generate calling sequence in solve

  return;
}


// Boundary data preparation

void PM_feelfem90vec::DoSolveBoundaryDataPreparation(Solve *solvePtr)
{
  /* Neumann data preparation */
  
  comment();
  writeSource("! Boundary Data is prepared before solve 1");
  writeSource("! in DRAMA MPI parallel version.");
  comment();

  return;
}


///////////////////////////////////////
void PM_feelfem90vec::DoSolveReturnSequence(Solve *solvePtr)
{
  
  pushSource("end subroutine ");
  pushSolveRoutineName( solvePtr->GetSolveNo());
  flushSource();

  pushSource("end module mod_");
  pushSolveRoutineName( solvePtr->GetSolveNo());
  flushSource();


  return;
}
