/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2CRS.cpp
 *  Date     : 1999/12/07
 *  Modified : 2001/01/29 np_VFG -> np_resvec in calling sequence of edev 
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  :
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

#include "feelfem.hpp"
#include "ElemGeneratorTemplate.hpp"
#include "MT_P2CRS.hpp"

MT_P2CRS::MT_P2CRS() 
{
  return;   // do nothing now
}

MT_P2CRS::~MT_P2CRS()  = default;

////////////////////////////////////////////////////
//  General routine
////////////////////////////////////////////////////
void MT_P2CRS::pushMatrixArgumentsCalled()
{
  pushSource("valmat,vfg,indrow,iptrcol,neq");
  return;
}

void MT_P2CRS::writeMatrixDeclarations()
{
  writeSource("      real*8  valmat(*)");
  writeSource("      real*8  vfg(*)");
  writeSource("      integer indrow(*)");
  writeSource("      integer iptrcol(*)");
  return;
}


void MT_P2CRS::doElemVariableDefinitionsMT()
{
  writeMatrixDeclarations();
  return;
}

void MT_P2CRS::pushMatrixArgumentsAllocated(void)
{
  pushSource("feel(np_VALMAT),feel(np_VFG),feel(np_INDROW),feel(np_IPTRCOL),neq");
  return;
}

void MT_P2CRS::DoSolveVariableDefinitionsMT(void)
{
  doNothingNow("void MT_P2CRS::DoSolveVariableDefinitionsMT(void)");
  // do nothing now
}

////////////////////////////////////////////////////
//  Matrix allocation   ( it would be template, if CRS is generalized)
////////////////////////////////////////////////////
void MT_P2CRS::DoSolveMatrixAllocate( Solve *)
{

  COMMENTlong("Matrix array allocation (CRS:Program Model FEELP2");
  

  //  writeSource("      np_push2 = np_work");
  writeSource("      call f_alloc_push");
  MODULEmalloc("np_NC"   ,"solve(NC)","npmax","0");
  writeSource("      call NC_connect(feel(np_NC),feel(np_IPF),npmax,");
  writeSource("     $     feel(np_ielem(1)),n_edat(nedtno(1),1),n_edat(nedtno(1),2),");
  writeSource("     $     ncmax,ndf)");
  writeSource("      call f_alloc_pop");

  com();
  writeSource("      ncon = ndf*ncmax");
  MODULEmalloc("np_IP"   ,"solve(IP)","neq+1","0");  

  /* push np_ic */
  writeSource("      call f_alloc_push");
  MODULEmalloc("np_IC"   ,"solve(IC)","neq*ncon","0");
  com();

  writeSource("      call mkCRSindex(feel(np_IC),feel(np_IC),feel(np_IP),");
  writeSource("     $                ncon,neq,ndf,");
  writeSource("     $     feel(np_ielem(1)),n_edat(nedtno(1),1),n_edat(nedtno(1),2),");
  writeSource("     $     feel(np_ipf),feel(np_ipd),npmax,ncof,maxnzpr)");
  writeSource("      call report('mkCRSindex end')");
  com();

  //  writeSource("      call f_move(feel(np_IC),feel(np_NC),ncof)");
  //  writeSource("      call f_move(feel(np_IP),feel(np_push2+ncof),neq)");
  //  writeSource("      call f_puti(feel(np_push2+ncof+neq),ncof+1)");
  //  com();
  //  writeSource("      np_work    = np_push2+ncof+neq+1");
  //  writeSource("      np_INDROW  = np_push2");
  //  writeSource("      np_IPTRCOL = np_push2+ncof");
  //  com();

  writeSource("      if(ncof .gt. neq*ncon) then");
  writeSource("        call abortexit(1,'ncof > neq*ncon,mkcrsindex')");      
  writeSource("      endif");
  com();

  writeSource("      np_iptrcol = np_IP");
  writeSource("      call f_alloc_pop");
  com();
  writeSource("* indrow is built in np_ic section");
  com();
  writeSource("      call f_alloc(np_indrow,'INDROW',ncof,0,0)");
  com();


  COMMENTlong("Allocate matrix array");
  MODULEmallocERT("np_VALMAT","solve(VALMAT)","ncof","1");
  MODULEmallocERT("np_VFG"   ,"solve(VFG)","neq","1");
  MODULEmallocERT("np_V"     ,"solve(V)"  ,"neq","1");
  MODULEmallocCHK();
  com();

  MODULEzeroclearD("feel(np_VALMAT)","ncof");    // matrix
  MODULEzeroclearD("feel(np_VFG)"   ,"neq" );    // right hand side
  MODULEzeroclearD("feel(np_V)"     ,"neq" );    // solution
  com();

  writeSource("      call rep_msize(neq,ncof)");
  comment();

  return;
}


////////////////////////////////////////////////////
//  call assemble routine
////////////////////////////////////////////////////
void MT_P2CRS::DoSolveCallAssembleRoutine( Solve *solvePtr)
{
  
  comment();
  for(int i=0;i<solvePtr->GetSolveElements();i++) {
    SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(i);
    
    pushSource("*  Element No.");
    pushSourceInt(i+1);
    flushSource();
    comment();
    
    pushSource("      call ");
    pushElemRoutineName( solvePtr->GetSolveNo(),i+1);
    pushSource("(x,y,");
    pushSource("feel(np_ielem(");pushSourceInt(i+1);pushSource(")),");
    pushSource("feel(np_matno(");pushSourceInt(i+1);pushSource(")),");
    flushSource();

    pushSource("     $     ");
    pushSource("n_edat(nedtno(");pushSourceInt(i+1);pushSource("),1),");
    pushSource("n_edat(nedtno(");pushSourceInt(i+1);pushSource("),2),");
    flushSource();
    
    pushSource("     $     ");
    pushMatrixArgumentsAllocated();
    pushSource(",feel(np_ipd)");
    flushSource();

    pushSource("     $     ");

    orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
    listIterator   <Variable *> itr(varPtrLst);
    for(itr.init(); !itr;++itr) {
      string a;
      pushSource(",");
      NameVariableInCalled(itr(),a);
      pushSource(a);
    }
    pushSource(")");
    flushSource();
  }
  return;
}


////////////////////////////////////////////////////
//  call Neumann data routine
////////////////////////////////////////////////////
void MT_P2CRS::DoSolveCallLinearNeumannData( Solve *solvePtr)
{
  int nconds = solvePtr->GetNconds();

  if(nconds == 0) {
    COMMENTlong("No Neumann Condition");
    return;
  }

  COMMENTlong("Neumann Conditions");
  
  for(int i=0;i<nconds;i++) {
    pushSource("      neelem = n_edat(nbedtno(");
    pushSourceInt(i+1);
    pushSource("),1)");
    flushSource();

    pushSource("      nenode = n_edat(nbedtno(");
    pushSourceInt(i+1);
    pushSource("),2)");
    flushSource();

    pushSource("      call ");
    pushNeumannRoutineName(solvePtr->GetSolveNo(),i+1);
    pushSource("(x,y,");
    flushSource();

    pushSource("     $");
    pushMatrixArgumentsAllocated();
    pushSource(",");
    flushSource();
    
    pushSource ("     $  feel(np_bielem(");
    pushSourceInt(i+1);
    pushSource(")),feel(np_bmatno(");
    pushSourceInt(i+1);
    pushSource(")),neelem,nenode,feel(np_IPD)");
    flushSource();

    pushSource("     $");
    pushVariableListInCalled( solvePtr->GetIthNeumannVariablePtrLst(i));

    pushSource(")");
    flushSource();
    
    comment();
  }

  return;
}

////////////////////////////////////////////////////
//  call Dirichlet data routine
////////////////////////////////////////////////////
void MT_P2CRS::DoSolveCallLinearDirichletData( Solve *solvePtr)
{
  int dconds = solvePtr->GetDconds();

  if(dconds == 0) {
    COMMENTlong("No Dirichlet Condition");
    return;
  }

  COMMENTlong("Dirichlet Conditions");
  
  for(int i=0;i<dconds;i++) {

    pushSource("      call ");
    pushDirichletRoutineName(solvePtr->GetSolveNo(),i+1);
    pushSource("(x,y,");
    flushSource();
    
    pushSource("     $");
    pushMatrixArgumentsAllocated();
    pushSource(",");
    flushSource();
    
    pushSource ("     $  feel(np_IPD),feel(np_inset(");
    pushSourceInt(i+1);
    pushSource(")),n_nset(nsetno(");
    pushSourceInt(i+1);
    pushSource("),1)");
    flushSource();

    pushSource("     $");
    pushVariableListInCalled( solvePtr->GetIthDirichletVariablePtrLst(i));
 
    pushSource(")");
    flushSource();
    
    comment();
  }

  return;
}

///////////////////////////////////////
// Edev routine
///////////////////////////////////////

void MT_P2CRS::DoSolveCallEdevRoutine( Solve *solvePtr)
{

  COMMENTlong("Call Edev Routine");

  pushSource("      call ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), 1 );  // P2FIX  NEG is 1
  pushSource("(feel(np_resvec),feel(np_IPD),feel(np_ielem(1)),"); //P2FIX NEG is 1
  flushSource();

  writeSource("     $      n_edat(nedtno(1),1),n_edat(nedtno(1),2)"); //P2FIX
  

  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0);   // P2FIX NEG is 1
  pushSource("     $");
  pushVariableListInCalled( sePtr->GetUnknownVariablePtrLst());
  pushSource(")");
  flushSource();
  
  comment();

  return;
}

void MT_P2CRS::DoSolveFreeMemoryMT()
{
  PopReturn();
  return;
}


// CO SOLVE
void MT_P2CRS::GenerateCoSolveElemGenerator (Solve *solvePtr)
{
  ElemGeneratorTemplate<MT_P2CRS> *ptrEG =
    new ElemGeneratorTemplate<MT_P2CRS>();
    ptrEG->DistributedAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0)); //P2 limi

  return;
}
