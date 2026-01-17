/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90SAMG20c.cpp
 *  Date     : 2000/12/07
 *  Modified : 
 *  
 *  Purpose  : Baserman's distributed CRS matrix library solver
 *  
 */

#include "feelfem.hpp"

#include "Solve.hpp"
#include "MT_ff90SKYLINE.hpp"
#include "LIB_feelfem90Skyline.hpp"


//Default constructor 
LIB_feelfem90Skyline <MT_ff90SKYLINE>::LIB_feelfem90Skyline()
{
  return;   // do nothing
}


//Default Destructor
LIB_feelfem90Skyline <MT_ff90SKYLINE>::~LIB_feelfem90Skyline()
{
  return;  // do nothing;
}

void LIB_feelfem90Skyline <MT_ff90SKYLINE>::SolveCallSolverRoutine(Solve *solvePtr)
{
  DoSolveMakeUpdateInformationMT();       // update information making(for some solvers)

  //  COMMENTlong("Allocate solution vector  ");  resvec = vfg
  //  writeSource("allocate( resvec(neq ))");
  //  com();


  COMMENTlong("Solver parameters");
  writeSource("  IFAC = 1");
  writeSource("  ISOL = 1");
  writeSource("  NSYM = 1");
  com();

  COMMENTlong(" Call Skyline solver");
  writeSource("  call skyline_sol(vkgs,vkgd,vkgi,vfg,kld,neq,5,IFAC,ISOL,NSYM,ENERG)");

  com();

  return;
}

void LIB_feelfem90Skyline <MT_ff90SKYLINE>::F90useSolveLIB(void)
{
  writeSource("! skyline solver related modules");
  writeSource("use mod_skyline_solver");
  com();
  
  return;
}


void LIB_feelfem90Skyline <MT_ff90SKYLINE>::SolverLibraryParameters(void)
{
  doNothingNow("void LIB_feelfem90Skyline <MT_ff90SKYLINE>::SolverLibraryParameters(void)");
  return;
}

void LIB_feelfem90Skyline <MT_ff90SKYLINE>::SolverLibraryVariableDefinition(void)
{
  COMMENTlong("Solver Library dependent variables(Skyline)");
  //  pushReal8Ptr1();
  //  flushSource("vfg");
  
  writeInteger4sc("IFAC,ISOL,NSYM");
  writeReal8sc("ENERG        ! not used");

  com();

  return;
}
//
void LIB_feelfem90Skyline <MT_ff90SKYLINE>::
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

void LIB_feelfem90Skyline<MT_ff90SKYLINE>::
GenerateCoSolveSolverParamRoutine(Solve *solvePtr)
{
  // no routine is necessary for skyline
  return;

}


//Library dependent solve-co routine generator
void LIB_feelfem90Skyline <MT_ff90SKYLINE>::
GenerateCoSolveRoutinesLIB(Solve *solvePtr)
{
  GenerateCoSolveSolverParamRoutine(solvePtr);
  return;
}
