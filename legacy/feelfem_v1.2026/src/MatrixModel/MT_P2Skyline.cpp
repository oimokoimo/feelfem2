/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2Skyline.cpp
 *  Date     : 1999/11/11
 *  Modified : 1999/11/18
 *  Modified : 2002/02/02 orderedPtrList
 *  
 *  Purpose  : feelP2 Skyline matrix model
 *  
 */
#include "feelfem.hpp"
#include "ElemGeneratorTemplate.hpp"
#include "MT_P2Skyline.hpp"

MT_P2Skyline::MT_P2Skyline() 
{
  return;   // do nothing now
}

MT_P2Skyline::~MT_P2Skyline() 
{
  return;   // do nothing now
}

void MT_P2Skyline::DoSolveVariableDefinitionsMT(void)
{
  doNothingNow("void MT_P2Skyline::DoSolveVariableDefinitionsMT(void)");
  // do nothing now
}


////////////////////////////////////////////////////
//  Matrix allocation
////////////////////////////////////////////////////
void MT_P2Skyline::DoSolveMatrixAllocate( Solve *)
{

  COMMENTlong("Matrix array allocation  (Skyline:Program Model FEELP2)");
  
  MODULEmalloc("np_KLD","solve(KLD)","neq+1","0");
  MODULEmalloc("np_KH" ,"solve(KH) ","neq",  "0");
  MODULEmalloc("np_KHa","solve(KHa)","npmax","0");
  MODULEzeroclearI("feel(np_KHa)","npmax");
  com();

  writeSource("      do 300 i=1,NEG");
  com();

  writeSource("        call cal_ht_a(feel(np_ielem(i)),n_edat(nedtno(i),1),");
  writeSource("     $                n_edat(nedtno(i),2),feel(np_KHa),npmax)");
  com();

  writeSource("  300   continue");
  comment();

  writeSource("*    Make array KH");
  writeSource("      call cal_ht(feel(np_KHa),feel(np_KH),feel(np_IPF),");
  writeSource("     $            feel(np_IPD),npmax,neq)");
  com();

  writeSource("*   Make KLD");
  writeSource("      call make_KLD(feel(np_KH),feel(np_KLD),neq,ncof)");
  com();

  writeSource("* VFG(Solution)");
  MODULEmallocERT("np_VFG","solve(VFG)","neq","1");
  com();

  writeSource("* VKGS(Upper) VKGI(Lower) VKGD(Diagonal)");

  MODULEmallocERT("np_VKGS","solve(VKGS)","ncof","1");
  MODULEmallocERT("np_VKGI","solve(VKGI)","ncof","1");
  MODULEmallocERT("np_VKGD","solve(VKGD)","neq" ,"1");
  MODULEmallocCHK();
  com();

  MODULEzeroclearD("feel(np_VKGS)","ncof");
  MODULEzeroclearD("feel(np_VKGD)","neq" );
  MODULEzeroclearD("feel(np_VKGI)","ncof");
  MODULEzeroclearD("feel(np_VFG)" ,"neq" );
  com();

  writeSource("      call rep_msize(neq,ncof)");
  comment();

  return;
}


////////////////////////////////////////////////////
//  call assemble routine
////////////////////////////////////////////////////
void MT_P2Skyline::DoSolveCallAssembleRoutine( Solve *solvePtr)
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
    pushSource("feel(np_VKGS),feel(np_VKGD),feel(np_VKGI),");
    flushSource();
    
    pushSource("     $     ");
    pushSource("feel(np_VFG),feel(np_KLD),feel(np_IPD)");
    flushSource();
    pushSource("     $     ");
    
    orderedPtrList   <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
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
void MT_P2Skyline::DoSolveCallLinearNeumannData( Solve *solvePtr)
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
    pushSource("(x,y,feel(np_VFG),feel(np_VKGD),feel(np_VKGS),");
    flushSource();
    
    writeSource("     $  feel(np_VKGI),feel(np_KLD),feel(np_KH),feel(np_IPD),neq,");
    
    pushSource ("     $  feel(np_bielem(");
    pushSourceInt(i+1);
    pushSource(")),feel(np_bmatno(");
    pushSourceInt(i+1);
    pushSource(")),neelem,nenode");
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
void MT_P2Skyline::DoSolveCallLinearDirichletData( Solve *solvePtr)
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
    pushSource("(x,y,feel(np_VFG),feel(np_VKGD),feel(np_VKGS),");
    flushSource();
    
    writeSource("     $  feel(np_VKGI),feel(np_KLD),feel(np_KH),feel(np_IPD),neq,");
    
    pushSource ("     $  feel(np_inset(");
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

void MT_P2Skyline::DoSolveCallEdevRoutine( Solve *solvePtr)
{

  COMMENTlong("Call Edev Routine");

  pushSource("      call ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), 1 );  // P2FIX  NEG is 1
  pushSource("(feel(np_VFG),feel(np_IPD),feel(np_ielem(1)),"); //P2FIX NEG is 1
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

void MT_P2Skyline::DoSolveFreeMemoryMT()
{
  PopReturn();
  return;
}



// CoSolve
void MT_P2Skyline::GenerateCoSolveElemGenerator (Solve *solvePtr)
{
  cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
  cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
  cerr << "!! CAUTION: MT_P2Skyline::       !!\n";
  cerr << "!! GeneratoeCoSolveElemGenerator !!\n";
  cerr << "!! Not implemented               !!\n";
  cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
  cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";


  /*  ElemGeneratorTemplate<MT_P2Skyline> *ptrEG =
    new ElemGeneratorTemplate<MT_P2Skyline>();
    ptrEG->DistributedAssembly(solve,solve.GetIthSolveElementPtr(0)); //P2 limi

  */
  return;
}

