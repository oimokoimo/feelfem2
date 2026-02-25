/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90vecCRS.cpp
 *  Date     : 2001/11/29 (copy from MT_ff90AMGCRS.cpp)
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
#include "MT_ff90vecCRS.hpp"


// 1. Constructors, destructors

MT_ff90vecCRS::MT_ff90vecCRS() 
{
  return;   // do nothing now
}

MT_ff90vecCRS::~MT_ff90vecCRS()  = default;




// 2. CoSolve Routine definitions
//    ElemGenerator Main  

void MT_ff90vecCRS::GenerateCoSolveElemGenerator (Solve *solvePtr)
{
  ElemGeneratorTemplate<MT_ff90vecCRS> *ptrEG =
    new ElemGeneratorTemplate<MT_ff90vecCRS>();
  ptrEG->NormalVectorAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0));
  //P2 limitation

  return;
}


void MT_ff90vecCRS::F90useSolveMT( void )
{
  writeSource("! Matrix data structure related modules");
  writeSource("use AMGCRS");
  com();
  
  return;
}

////////////////////////////////////////////////////
//  General routine
////////////////////////////////////////////////////
void MT_ff90vecCRS::pushMatrixArgumentsCalled()
{
  pushSource("valmat,vfg,indrow,iptrcol,neq");
  return;
}

void MT_ff90vecCRS::writeMatrixDeclarations()
{
  writeSource("real   (kind=REAL8),dimension(:),pointer :: valmat,vfg");
  writeSource("integer,dimension(:)            ,pointer :: indrow,iptrcol");
  return;
}

//  solve routine matrix dependent parts
void MT_ff90vecCRS::DoSolveVariableDefinitionsMT()
{
  COMMENTlong("Matrix related variables");

  writeMatrixDeclarations();    // AMG CRS,
  writeSource("integer                                  :: ncof");
  com();

  return;
}

//  elem routine matrix dependent parts
void MT_ff90vecCRS::doElemVariableDefinitionsMT()
{
  writeMatrixDeclarations();
  writeSource("integer                                  :: ncof");
  return;
}

void MT_ff90vecCRS::pushMatrixArgumentsAllocated(void)
{
  pushMatrixArgumentsCalled();             // same in Fortran 90
  return;
}



// ### Matrix allocation in solve routine

void MT_ff90vecCRS::DoSolveMatrixAllocate( Solve *)
{
  COMMENTlong("Calculate maxmal number of element connection to one node");
  writeSource("call nc_connectp2(npmax,ielem,nelem,np, ncmax)");
  com();

  writeSource("call reportmodule('nc_connectp2')");
  com();

  COMMENTlong("Make AMG-CRS array");
  writeSource("nenfremax = 0");
  writeSource("do i=1,neg");       
  writeSource(" do j=1,maxElementNodes");
  writeSource("  if(nenfremax < nenfre(j,i)) nenfremax=nenfre(j,i)");
  writeSource(" end do");
  writeSource("end do");
  com();

  writeSource("ndfmax = nenfremax * maxElementNodes");
  writeSource("ncon   = nenfremax * maxElementNodes * ncmax");
  com();
  
  writeSource("call mkAMGCRSindex( neq,                    &");
  writeSource("                    ndfmax,ncon,            &");
  writeSource("                    ipf,ipd,npmax,          &");
  writeSource("                    ielem,nelem,np,         &");
  writeSource("                    iptrcol,indrow,ncof     )");
  com();
  
  writeSource("call reportmodule('mkAMGCRSindex')");
  com();

  // allocate matrix array
  COMMENTlong("Allocate matrix, right hand side");
  MODULEmallocERT("valmat","AMG/CRS matrix","ncof","1");
  MODULEmallocERT("vfg","Right hand side","neq","1");
  MODULEzeroclearD("valmat","ncof");
  MODULEzeroclearD("vfg"   ,"neq" );
  com();

  return;
}


////////////////////////////////////////////////////
//  call assemble routine
////////////////////////////////////////////////////
void MT_ff90vecCRS::DoSolveCallAssembleRoutine( Solve *solvePtr)
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
  pushSource(",ncof)");
  flushSource();
  com();

  return;
}


////////////////////////////////////////////////////
//  call Neumann data routine
////////////////////////////////////////////////////
void MT_ff90vecCRS::DoSolveCallLinearNeumannData( Solve *solvePtr)
{
  int nconds = solvePtr->GetNconds();

  if(nconds == 0) {
    COMMENTlong("No Neumann Condition");
    return;
  }

  COMMENTlong("Neumann Conditions");
  
  for(int i=0;i<nconds;i++) {


    pushSource("call ");
    pushNeumannRoutineName(solvePtr->GetSolveNo(),i+1);
    pushSource("(nbedtno(");
    pushSourceInt(i+1);
    pushSource("),firstEdatPtr,                   &");
    flushSource();

    pushSource("     npmax,");
    pushCoordinateSource();
    pushSource(",ipf,ipd                             &");
    flushSource();  

    pushSource("    ");
    /* Additional variables */
    orderedPtrList<Variable *>varPtrLst = solvePtr->GetIthNeumannVariablePtrLst(i);
    listIterator <Variable *>itr(varPtrLst);

    /* Domain variables */
    pushVariableListInSolve( varPtrLst );
    
    pushSource(",");
    pushMatrixArgumentsAllocated();
    pushSource(")");
    flushSource();

    com();
  }

  return;
}

////////////////////////////////////////////////////
//  call Dirichlet data routine
////////////////////////////////////////////////////
void MT_ff90vecCRS::DoSolveCallLinearDirichletData( Solve *solvePtr)
{
  int dconds = solvePtr->GetDconds();

  if(dconds == 0) {
    COMMENTlong("No Dirichlet Condition");
    return;
  }

  COMMENTlong("Dirichlet Conditions");
  
  for(int i=0;i<dconds;i++) {
    pushSource("! No.");
    pushSourceInt(i+1);
    flushSource();

    pushSource("call ");
    pushDirichletRoutineName(solvePtr->GetSolveNo(),i+1);
    pushSource("(nsetno(");
    pushSourceInt(i+1);
    pushSource("),firstNsetPtr,                &");
    flushSource();

    pushSource( "       ");
    pushCoordinateSource();
    pushSource(",ipf,ipd,npmax                           &");
    flushSource();

    pushSource("       ");
    pushVariableListInCalled(solvePtr->GetIthDirichletVariablePtrLst(i));
    pushSource(",");
    pushMatrixArgumentsCalled();
    pushSource(")");
    flushSource();

  }

  com();
  return;
}

///////////////////////////////////////
// Edev routine calling sequence to edev
///////////////////////////////////////

void MT_ff90vecCRS::DoSolveCallEdevRoutine( Solve *solvePtr)
{

  COMMENTlong("Call Edev Routine");

  pushSource("call ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), 1 );  // P2FIX  NEG is 1
  pushSource("(resvec,ipd, &");
  flushSource();

  pushSource("  ielem,nelem,np");
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);   // P2FIX NEG is 1
  pushVariableListInCalled( sePtr->GetUnknownVariablePtrLst());
  pushSource(")");
  flushSource();
  
  comment();

  return;
}

void MT_ff90vecCRS::DoSolveFreeMemoryMT()
{
  COMMENTlong("deallocate matrix related arrays");

  writeSource("if(associated(indrow)) then");
  writeSource(" deallocate(indrow)");
  writeSource("end if");
  com();

  writeSource("if(associated(iptrcol)) then");
  writeSource(" deallocate(iptrcol)");
  writeSource("end if");
  com();

  writeSource("if(associated(valmat)) then");
  writeSource(" deallocate(valmat)");
  writeSource("end if");
  com();

  writeSource("deallocate(vfg)");
  writeSource("deallocate(resvec)");
  com();
}

void MT_ff90vecCRS::DoSolveMakeUpdateInformationMT()
{
  // AMG make information and initialize amg
  COMMENTlong("Matrix dependent initialization");
  writeSource("! none required for AMGCRS");
  //  writeSource("call amg_initialize()");
  //  writeSource("!call initcommon()");
  //  writeSource("!call amg_alloc_clearcounters()");
  com();

  return;
}
