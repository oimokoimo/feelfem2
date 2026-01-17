/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90Lumping.cpp
 *  Date     : 2002/10/07 (Copy from feelfem90Skyline.cpp)
 *  Modified : 
 *  
 *  Purpose  : Lumping solver
 *  
 */

#include "feelfem.hpp"

#include "Solve.hpp"
#include "MT_ff90LUMPING.hpp"
#include "LIB_feelfem90Lumping.hpp"


//Default constructor 
LIB_feelfem90Lumping <MT_ff90LUMPING>::LIB_feelfem90Lumping()
{
  return;   // do nothing
}


//Default Destructor
LIB_feelfem90Lumping <MT_ff90LUMPING>::~LIB_feelfem90Lumping()
{
  return;  // do nothing;
}

void LIB_feelfem90Lumping <MT_ff90LUMPING>::SolveCallSolverRoutine(Solve *solvePtr)
{
  DoSolveMakeUpdateInformationMT();       // update information making(for some solvers)

  //  COMMENTlong("Allocate solution vector  ");  resvec = vfg
  //  writeSource("allocate( resvec(neq ))");
  //  com();


  COMMENTlong("Lumping solver");
  writeSource("do lump=1,neq");
  writeSource("  vfg(lump) = vfg(lump)/vkgd(lump)");
  writeSource("end do");
  com();
  com();

  return;
}

void LIB_feelfem90Lumping <MT_ff90LUMPING>::F90useSolveLIB(void)
{
  writeSource("! solver related modules");
  //  writeSource("use mod_skyline_solver");
  com();
  
  return;
}


void LIB_feelfem90Lumping <MT_ff90LUMPING>::SolverLibraryParameters(void)
{
  //  doNothingNow("void LIB_feelfem90Lumping <MT_ff90LUMPING>::SolverLibraryParameters(void)");
  return;
}

void LIB_feelfem90Lumping <MT_ff90LUMPING>::SolverLibraryVariableDefinition(void)
{
  COMMENTlong("Solver Library dependent variables(Skyline)");
  //  pushReal8Ptr1();
  //  flushSource("vfg");
  writeInteger4sc("lump");

  com();

  return;
}
//
void LIB_feelfem90Lumping <MT_ff90LUMPING>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  int solveElementNo = 1 ;   // P2 limitation FIX

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  F90useSolveLIB();

  // library dependent co-solve routine module
  //  pushSource("use mod_samg20cparam");
  //  pushSourceInt( solvePtr->GetSolveNo());
  //  pushSource("_");
  //  pushSourceInt(solveElementNo);
  //  flushSource();

  F90useSolveMT();
  F90useSolvePM(solvePtr);
  
  fortImplicit();
  com();

  DoDeclareVariablesFromMainPM( solvePtr->VariablePtrLst());   //Fortran dependent
  

  return;
}

void LIB_feelfem90Lumping<MT_ff90LUMPING>::
GenerateCoSolveSolverParamRoutine(Solve *solvePtr)
{
  // no routine is necessary for lumping
  return;

}


//Library dependent solve-co routine generator
void LIB_feelfem90Lumping <MT_ff90LUMPING>::
GenerateCoSolveRoutinesLIB(Solve *solvePtr)
{
  GenerateCoSolveSolverParamRoutine(solvePtr);
  return;
}
