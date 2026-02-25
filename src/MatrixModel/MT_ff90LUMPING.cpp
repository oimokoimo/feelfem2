/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90LUMPING.cpp
 *  Date     : 2002/10/07 (copy from MT_ff90SKYLINE.cpp)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 *  1. Constructors/destructors
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

#include "ElemGeneratorTemplate.hpp"
#include "MT_ff90LUMPING.hpp"


// 1. Constructors, destructors

MT_ff90LUMPING::MT_ff90LUMPING() 
{
  return;   // do nothing now
}

MT_ff90LUMPING::~MT_ff90LUMPING()  = default;

// 2. CoSolve Routine definitions
//    ElemGenerator Main  

void MT_ff90LUMPING::GenerateCoSolveElemGenerator (Solve *solvePtr)
{
  ElemGeneratorTemplate<MT_ff90LUMPING> *ptrEG =
    new ElemGeneratorTemplate<MT_ff90LUMPING>();
  ptrEG->NormalAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0)); //P2 limi

  return;
}


void MT_ff90LUMPING::F90useSolveMT( void )
{
  //  writeSource("! Matrix data structure related modules");
  //  com();
  
  return;
}

////////////////////////////////////////////////////
//  General routine
////////////////////////////////////////////////////
void MT_ff90LUMPING::pushMatrixArgumentsCalled()
{
  pushSource("vkgd,vfg,neq");
  return;
}

void MT_ff90LUMPING::writeMatrixDeclarations()
{
  //real(kind=REAL8),dimension(:) ,pointer :: vkgs,vkgd,vkgi")
  //integer,dimension(:)          ,pointer :: kld,kh");
  writeReal8Ptr1("vkgd,vfg"); 
  return;
}

//  solve routine matrix dependent parts
void MT_ff90LUMPING::DoSolveVariableDefinitionsMT()
{
  COMMENTlong("Matrix related variables");

  writeMatrixDeclarations();

  //  writeInteger4Ptr1("kha");      // for work
  com();

  return;
}

void MT_ff90LUMPING::DoSolveInitializerMT(Solve *)
{

  // do nothing for LUMPING
  return;
}


void MT_ff90LUMPING::pushMatrixArgumentsAllocated(void)
{
  pushMatrixArgumentsCalled();             // same in Fortran 90
  return;
}



// ### Matrix allocation in solve routine

void MT_ff90LUMPING::DoSolveMatrixAllocate( Solve *)
{
  COMMENTlong("Matrix array allocation  (Skyline:Program Model feelfem90)");

  MemAllocate("vkgd","neq" ,"neq", TYPE_REAL8);
  MemAllocate("vfg" ,"neq" ,"neq", TYPE_REAL8);
  com();

  MODULEzeroclearD("vkgd","neq" );
  MODULEzeroclearD("vfg" ,"neq" );
  com();

  return;
}


////////////////////////////////////////////////////
//  call assemble routine
////////////////////////////////////////////////////
void MT_ff90LUMPING::DoSolveCallAssembleRoutine( Solve *solvePtr)
{
  int fem_exchange_variables;
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  
  fem_exchange_variables = 0;
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) fem_exchange_variables++;
  }

  
  COMMENTlong(" Assemble routine call");
  pushSource("call ");
  pushElemRoutineName( solvePtr->GetSolveNo());
  pushSource("(ielem,matno,nelem,np,              &");
  flushSource();

  pushSource( "      ");
  pushCoordinateSource();
  pushSource(",ipf,ipd,npmax                       &");
  flushSource();

  // related variables (FEM,EWISE,SCALAR variables)
  pushSource( "     ");
  for(itr.init(); !itr;++itr) {
    pushSource(",");
    pushVariableInCalled(itr());
  }

  pushSource(",");
  pushMatrixArgumentsAllocated();
  pushSource(")");
  flushSource();
  com();

  return;
}


////////////////////////////////////////////////////
//  call Neumann data routine
////////////////////////////////////////////////////
void MT_ff90LUMPING::DoSolveCallLinearNeumannData( Solve *solvePtr)
{
  int nconds = solvePtr->GetNconds();

  if(nconds == 0) {
    COMMENTlong("No Neumann Condition");
    return;
  }

  COMMENTlong("Neumann Conditions");
  
  for(int i=0;i<nconds;i++) {

    doIthNeumannCallInSolvePM(solvePtr,i);

    pushSource(",");
    pushMatrixArgumentsAllocated();
    pushSource(")");
    flushSource();

    doIthNeumannCallInSolvePM2(solvePtr,i);


    com();
  }

  return;
}

////////////////////////////////////////////////////
//  call Dirichlet data routine
////////////////////////////////////////////////////
void MT_ff90LUMPING::DoSolveCallLinearDirichletData( Solve *solvePtr)
{
  int dconds = solvePtr->GetDconds();

  if(dconds == 0) {
    COMMENTlong("No Dirichlet Condition");
    return;
  }

  COMMENTlong("Dirichlet Conditions");
  
  for(int i=0;i<dconds;i++) {

    doIthDirichletCallInSolvePM(solvePtr,i);

    pushSource(",");
    pushMatrixArgumentsCalled();
    pushSource(")");
    flushSource();

    doIthDirichletCallInSolvePM2(solvePtr,i);   // end do
  }

  com();
  return;
}

///////////////////////////////////////
// Edev routine calling sequence to edev
///////////////////////////////////////

void MT_ff90LUMPING::DoSolveCallEdevRoutine( Solve *solvePtr)
{

  COMMENTlong("Call Edev Routine");

  pushSource("call ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), 1 );  // P2FIX  NEG is 1
  pushSource("(vfg,ipd, &");
  flushSource();

  pushSource("  ielem,nelem,np");
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);   // P2FIX NEG is 1
  pushVariableListInCalled( sePtr->GetUnknownVariablePtrLst());
  pushSource(")");
  flushSource();
  
  comment();

  return;
}

void MT_ff90LUMPING::DoSolveFreeMemoryMT()
{
  COMMENTlong("deallocate matrix related arrays");

  writeSource("if(associated(vkgd)) then");
  writeSource(" deallocate(vkgd)");
  writeSource("end if");
  com();

  writeSource("deallocate(vfg)");
  com();
}

void MT_ff90LUMPING::DoSolveMakeUpdateInformationMT()
{
  // AMG make information and initialize amg
  COMMENTlong("Matrix dependent initialization");
  writeSource("! none required for LUMPING");
  //  writeSource("call amg_initialize()");
  //  writeSource("!call initcommon()");
  //  writeSource("!call amg_alloc_clearcounters()");
  com();

  return;
}
