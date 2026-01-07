/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2PCG.cpp
 *  Date     : 1999/11/11
 *  Modified : 1999/11/18
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : feelP2 PCG matrix model
 *  
 */
#include "feelfem.hpp"
#include "ElemGeneratorTemplate.hpp"
#include "MT_P2PCG.hpp"

MT_P2PCG::MT_P2PCG() 
{
  return;   // do nothing now
}

MT_P2PCG::~MT_P2PCG() 
{
  return;   // do nothing now
}

void MT_P2PCG::DoSolveVariableDefinitionsMT(void)
{
  doNothingNow("void MT_P2PCG::DoSolveVariableDefinitionsMT(void)");
  // do nothing now
}

////////////////////////////////////////////////////
//  Matrix allocation
////////////////////////////////////////////////////
void MT_P2PCG::DoSolveMatrixAllocate( Solve *)
{
  writeSource("*---------------------------------");
  writeSource("* MT_P2PCG IS under development   ");
  writeSource("*---------------------------------");

  return;
}

////////////////////////////////////////////////////
//  call assemble routine
////////////////////////////////////////////////////
void MT_P2PCG::DoSolveCallAssembleRoutine( Solve *)
{

  writeSource("*---------------------------------");
  writeSource("* MT_P2PCG Call assemble is not y ");
  writeSource("*---------------------------------");

  return;
}



void MT_P2PCG::DoSolveCallLinearNeumannData( Solve *solvePtr)
{
  cout <<"Now MT_P2PCG::DoSolveCallLinearNeumannData is not implemented\n";
}
void MT_P2PCG::DoSolveCallLinearDirichletData( Solve *solvePtr)
{
  cout <<"Now MT_P2PCG::DoSolveCallLinearDirichletData is not implemented\n";
}
void MT_P2PCG::DoSolveCallEdevRoutine( Solve *solvePtr)
{
  cout <<"Now MT_P2PCG::DoSolveCallEdevRoutine( Solve *solvePtr)\n";
}

// CoSolve
void MT_P2PCG::GenerateCoSolveElemGenerator (Solve *solvePtr)
{
  cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
  cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
  cerr << "!! CAUTION: MT_P2PCG::           !!\n";
  cerr << "!! GeneratoeCoSolveElemGenerator !!\n";
  cerr << "!! Not implemented               !!\n";
  cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
  cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

  /*  ElemGeneratorTemplate<MT_P2PCG> *ptrEG =
    new ElemGeneratorTemplate<MT_P2PCG>();
    ptrEG->DistributedAssembly(solve,solve.GetIthSolveElementPtr(0)); //P2 limi
  */

  return;
}


void MT_P2PCG::DoSolveFreeMemoryMT()
{
  PopReturn();
  return;
}



