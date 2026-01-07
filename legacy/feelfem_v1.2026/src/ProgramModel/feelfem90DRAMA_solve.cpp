/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90DRAMA_solve.cpp
 *  Date     : 2000/10/19
 *  Modified : 2000/10/19
 *  
 *  Purpose  : solve routine generator for feelfem90DRAMA program model
 *  
 *  1. I/O related routines (routine name)
 *  
 *  
 *  
 *  
 */
#include <stdlib.h>
#include "PM_feelfem90DRAMA.hpp"



// 1. I/O related routines

char *PM_feelfem90DRAMA::GetSolveRoutineName( int no )
{
  char *ptr = new char[8];

  if(no >99) { cerr <<"Too large solve Number\n"; exit(1); }
  sprintf(ptr,"solve%d",no);

  return(ptr);
}

///////////////////////////////////////
// Do Solve functions
///////////////////////////////////////
void PM_feelfem90DRAMA::DoSolveStarters()
{
  SourceStarters();   // f90 version has no implicit here

  return;
}

void PM_feelfem90DRAMA::F90useSolvePM(Solve *solvePtr)
{
  
  writeSource("! modules for solve");
  writeSource("use subSolveDrama");
  writeSource("use femDataType");
  writeSource("use dramaDataModel");
  com();

  F90useAlways();  
  com();

  int solveNo,dconds,nconds;
  solveNo = solvePtr->GetSolveNo();
  dconds = solvePtr->GetDconds();
  nconds = solvePtr->GetNconds();

  writeSource("! solve family");
  pushSource("use mod_elem");
  pushSourceInt(solveNo);
  flushSource();

  pushSource("use mod_mksolve");
  pushSourceInt(solveNo);
  pushSource("extdata");
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

void PM_feelfem90DRAMA::DoSolveVariableDefinitionsPM(Solve *solvePtr)
{
  // auto variables
  COMMENTlong("auto variables");

  writeInteger4sc("i,j");
  writeInteger4sc("ierror");
  writeInteger4sc("nelem");
  writeInteger4Ptr2("enptr,con");
  writeInteger4Ptr1("matno");
  writeInteger4sc("netype      !P2 limit");
  com();

  // DRAMA auto variables
  writeInteger4Ptr1("ipd,ipf");
  writeInteger4sc("neq");
  writeInteger4Ptr1("isumup");
  com();


  // ipdinfo (03/02/19) for dirichlet routines
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  list <Variable *>vPLst = sePtr->GetUnknownVariablePtrLst();
  listIterator<Variable *>itrFEMv(vPLst);
  for(itrFEMv.init(); !itrFEMv; ++itrFEMv) {
    pushInteger4Ptr1();
    pushSource("ipd_");
    pushSource(itrFEMv()->GetName());
    flushSource();
  }


  writeInteger4sc("nelem_ex,nouter");
  writeInteger4Ptr2("enptr_ex,con_ex");
  writeInteger4Ptr1("matno_ex");
  writeInteger4Ptr1("ndno,peno");
  writeInteger4Ptr1("ipf_ex,ipd_ex");
  com();
  
  CoordinateExternalVariableDeclaration();
  FEMExternalVariableDeclarationLst(solvePtr->VariablePtrLst());

  // Solve Varible declaration
  // Problem dependent variables
  int dconds = solvePtr->GetDconds();
  int nconds = solvePtr->GetNconds();


  COMMENTlong("Problem dependent parameters");
  writeInteger4sc("edatno");
  writeInteger4sc("nenfre(maxElementNodes,neg)");

  //  03/02/19 removed, using solveList information
  //  if(dconds) {
  //    writeSource("integer                        :: nsetno(dirichletSets)");
  //  }
  //  else {
  //    writeSource("! integer                      :: nsetno(dirichletSets)");
  //  }

  //  if(nconds) {
  //    writeSource("integer                        :: nbedtno(neumannSets)");
  //  }
  //  else {
  //    writeSource("! integer                      :: nbedtno(neumannSets)");
  //  }
  writeSource("!------------------------------------------------");
  writeSource("!  Element equation topology variable");
  writeSource("!------------------------------------------------");
  writeInteger4sc("ncmax         ! maximum number of elements");
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
void PM_feelfem90DRAMA::DoSolveParametersPM( Solve *solvePtr)
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

void PM_feelfem90DRAMA::DoSolveInitialDefPM(Solve *solvePtr)
{
  int dconds = solvePtr->GetDconds();
  int nconds = solvePtr->GetNconds();
  
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);  // 0 fix P2 limit
  Dirichlet    *dptr;
  Neumann      *nptr;


  // Data statement (Problem depenedent)
  COMMENTlong("Problem parameters");

  //  /* EDATNO oimo P2 limited */     // removed 03/02/19
  //  pushSource("data edatno/");
  //  pushSourceInt(sePtr->GetEdatno());
  //  pushSource("/");
  //  flushSource();


  pushSource("data nenfre/");
  for(int i=0;i<solvePtr->GetMaxnodes();i++) { //maxnodes should be nodes in SE
    if(i!=0) pushSource(",");
    pushSourceInt(sePtr->GetNenfre(i));
  }
  pushSource("/");
  flushSource();

  //  removed, (03/02/19) for using solveList
  //    
  //  if(dconds) {
  //    pushSource("data nsetno/");
  //    for(int i=0;i<dconds;i++) {
  //      if(i!=0) pushSource(",");
  //      pushSourceInt(solvePtr->GetIthDirichletNsetno(i));
  //    }
  //    pushSource("/");
  //    flushSource();
  //  }
  //  if(nconds) {
  //    pushSource("data nbedtno/");
  //    for(int i=0;i<nconds;i++) {
  //      if(i!=0) pushSource(",");
  //      pushSourceInt(solvePtr->GetIthNeumannNbedtno(i));
  //    }
  //    pushSource("/");
  //    flushSource();
  //  }

  com();
  return;
}

void PM_feelfem90DRAMA::DoSolveInitializerPM(Solve *solvePtr)
{

  // set edatno from solveLst   (add 03/02/19)
  pushSource("solveNo      =  ");
  pushSourceInt(solvePtr->GetSolveNo());
  flushSource();

  writeSource("solveInfoPtr => solveLst%solveDataList(solveNo)");
  writeSource("edatno       = solveInfoPtr%edatno");
  com();

  /* edatnolst,matnolst,conlst */
  COMMENTlong(" allocate enptr,con,matno in the next subroutine");
  writeSource("call setdramaedat(edatno,firstDramaEdatPtr,      &");
  writeSource("                  nelem,enptr,con,matno,netype    )");

  com();

  // region edat check
  writeSource("np = enptr(1,1)-(enptr(1,2)-1)+1 ! P2 limit, only one e-type");
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

  //  report routine
  pushSource("if(myrank == 0) ");
  pushSource( "call preport('SOLVE ");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" START')");
  flushSource();
  
  return;
}



// 2-3 start report routine

void PM_feelfem90DRAMA::DoSolveReport( int no, const char *s)
{
  pushSource("if(myrank == 0)");
  pushSource(" call preport('solve");
  pushSourceInt(no);
  pushSource(" : ");
  pushSource(s);
  pushSource("')");
  flushSource();

  return;
}



// Degree of freedom
void PM_feelfem90DRAMA::DoSolveDegreeOfFreedom(Solve *solvePtr)
{

  COMMENTlong(" Construct ipf,ipd");
  MODULEmallocERT("ipf","D.O.F of each node","npmax","1");
  MODULEmallocERT("ipd","Sumup D.O.F.",      "npmax","1");
  com();

  MODULEzeroclearI("ipd","npmax");
  MODULEzeroclearI("ipf","npmax");
  com();

  writeSource("call makeipfdrama(mypeid,nenfre,maxElementNodes,neg, &");
  writeSource("                  enptr,con,nelem,npmax,ipf          )");
  com();

  writeSource("call makeipddrama(ipf,ipd,npmax,neq)");
  com();

  writeSource("if(myrank == 0) call preportmodule('makeipfdrama,makeipddrama')");
  com();

  return;
}


// Assemble preparation, especially for parallel computation
void PM_feelfem90DRAMA::DoSolveAssemblyPreparation(Solve *solvePtr)
{
  // DRAMA-double index distributed matrix
  SubDoSolveMakeExtData(solvePtr);              // generate calling sequence in solve

  return;
}


// Boundary data preparation

void PM_feelfem90DRAMA::DoSolveBoundaryDataPreparation(Solve *solvePtr)
{
  /* Neumann data preparation */
  
  comment();
  writeSource("! Boundary Data is prepared before solve 1");
  writeSource("! in DRAMA MPI parallel version.");
  comment();

  return;
}


///////////////////////////////////////
void PM_feelfem90DRAMA::DoSolveReturnSequence(Solve *solvePtr)
{
  
  pushSource("end subroutine ");
  pushSolveRoutineName( solvePtr->GetSolveNo());
  flushSource();

  pushSource("end module mod_");
  pushSolveRoutineName( solvePtr->GetSolveNo());
  flushSource();


  return;
}


void PM_feelfem90DRAMA::doSolveFreeMemoryPM(Solve *solvePtr)
{
  writeSource("void PM_feelfem90DRAMA::doSolveFreeMemoryPM(Solve *solvePtr)");
  return;
}
