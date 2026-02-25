/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2SID.cpp
 *  Date     : 1999/12/07
 *  Modified : 1999/12/07
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
#include "MT_P2SID.hpp"

MT_P2SID::MT_P2SID() 
{
  return;   // do nothing now
}

MT_P2SID::~MT_P2SID()  = default;

////////////////////////////////////////////////////
//  General routine
////////////////////////////////////////////////////
void MT_P2SID::pushMatrixArgumentsCalled()
{
  pushSource("a,b,ja,mj,neq");
  return;
}

void MT_P2SID::writeMatrixDeclarations()
{
  writeSource("      real*8   a(neq,mj)");
  writeSource("      integer ja(neq,mj)");
  writeSource("      real*8   b(neq)");

  return;
}

void MT_P2SID::doElemVariableDefinitionsMT()
{
  writeMatrixDeclarations();
  return;
}

void MT_P2SID::pushMatrixArgumentsAllocated(void)
{
  pushSource("feel(np_a),feel(np_b),feel(np_ja),mj,neq");
  return;
}

void MT_P2SID::DoSolveVariableDefinitionsMT(void)
{
  doNothingNow("void MT_P2SID::DoSolveVariableDefinitionsMT(void)");
  // do nothing now
}

////////////////////////////////////////////////////
//  Matrix allocation   ( it would be template, if CRS is generalized)
////////////////////////////////////////////////////
void MT_P2SID::DoSolveMatrixAllocate( Solve *)
{

  COMMENTlong("Matrix array allocation (CRS:Program Model FEELP2");
  

  writeSource("      np_push2 = np_work");
  MODULEmalloc("np_NC"   ,"solve(NC)","npmax","0");
  writeSource("      call NC_connect(feel(np_NC),feel(np_IPF),npmax,");
  writeSource("     $     feel(np_ielem(1)),n_edat(nedtno(1),1),n_edat(nedtno(1),2),");
  writeSource("     $     ncmax,ndf)");

  com();
  writeSource("      ncon = ndf*ncmax");
  MODULEmalloc("np_JAx"   ,"solve(JAx)","neq*ncon","0");  
  MODULEmalloc("np_IP"   ,"solve(IP)","neq","0");  

  writeSource("      call mkSIDindex(feel(np_JAx),feel(np_IP),ncon,neq,ndf,");
  writeSource("     $     feel(np_ielem(1)),n_edat(nedtno(1),1),n_edat(nedtno(1),2),");
  writeSource("     $     feel(np_ipf),feel(np_ipd),npmax,mj)");
  com();
  writeSource("      np_work = np_push2");
  writeSource("      call f_alloc(np_ja,'(JA)',neq*mj,0,0)");
  writeSource("      call f_move(feel(np_JAx),feel(np_JA),neq*mj)");
  com();
  writeSource("      call report('mkSIDindex end')");
  com();

  MODULEmallocERT("np_a"   ,"solve(a)"  ,"neq*mj","1");
  MODULEmallocERT("np_b"   ,"solve(b)"  ,"neq"   ,"1");
  MODULEmallocERT("np_solx","solve(solx)","neq"   ,"1");
  MODULEmallocCHK();
  com();

  MODULEzeroclearD("feel(np_a)","neq*mj");    // matrix
  MODULEzeroclearD("feel(np_b)","neq"   );    // right hand side
  com();

  writeSource("      call rep_msize(neq,mj*neq)");
  comment();

  return;
}


////////////////////////////////////////////////////
//  call assemble routine
////////////////////////////////////////////////////
void MT_P2SID::DoSolveCallAssembleRoutine( Solve *solvePtr)
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
    orderedPtrList  <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
    listIterator <Variable *> itr(varPtrLst);
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
void MT_P2SID::DoSolveCallLinearNeumannData( Solve *solvePtr)
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
void MT_P2SID::DoSolveCallLinearDirichletData( Solve *solvePtr)
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

void MT_P2SID::DoSolveCallEdevRoutine( Solve *solvePtr)
{

  COMMENTlong("Call Edev Routine");

  pushSource("      call ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), 1 );  // P2FIX  NEG is 1
  pushSource("(feel(np_solx),feel(np_IPD),feel(np_ielem(1)),"); //P2FIX NEG is 1
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

void MT_P2SID::DoSolveFreeMemoryMT()
{
  PopReturn();
  return;
}


// CO SOLVE
void MT_P2SID::GenerateCoSolveElemGenerator (Solve *solvePtr)
{
  ElemGeneratorTemplate<MT_P2SID> *ptrEG =
    new ElemGeneratorTemplate<MT_P2SID>();
    ptrEG->DistributedAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0)); //P2 limi

  return;
}
