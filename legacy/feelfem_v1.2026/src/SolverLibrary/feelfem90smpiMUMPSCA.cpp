/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90smpiMUMPSCA.cpp
 *  Date     : 2003/01/01
 *  Modified : 2003/01/04
 *  
 *  Purpose  : MUMPS Centralized assembled matrix input
 *  
 */

#include "feelfem.hpp"

#include "Solve.hpp"
#include "MT_ff90smpiMUMPSCA.hpp"
#include "LIB_feelfem90smpiMUMPSCA.hpp"


//Default constructor 
LIB_feelfem90smpiMUMPSCA <MT_ff90smpiMUMPSCA>::LIB_feelfem90smpiMUMPSCA()
{
  return;   // do nothing
}


//Default Destructor
LIB_feelfem90smpiMUMPSCA <MT_ff90smpiMUMPSCA>::~LIB_feelfem90smpiMUMPSCA()
{
  return;  // do nothing;
}

void LIB_feelfem90smpiMUMPSCA <MT_ff90smpiMUMPSCA>::SolveCallSolverRoutine(Solve *solvePtr)
{
  DoSolveMakeUpdateInformationMT();       // update information making(for some solvers)

  com();

  // version 8.1 additionals
  int solveElements = 1;                // P2 FIX

  writeSource("end if");  // if statement is in MT_ff90smpiMUMPSCA
  com();
  com();

  COMMENTlong("Version MUMPSCA parameters");
  com();


  writeSource("! Call packeage for solution");
  writeSource("mumps_par%JOB = 6");
  com();

  writeSource("call DMUMPS(mumps_par)");
  com();


  pushSource("call reportmodule('MUMPSCA solve No.");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" Finished')");
  flushSource();
  comment();

  com();

  return;
}

void LIB_feelfem90smpiMUMPSCA <MT_ff90smpiMUMPSCA>::F90useSolveLIB(void)
{
  writeSource("! MUMPSCA solver related modules");
  //  writeSource("! inclue 'amg_samg'  ! interface definition");
  com();
  
  return;
}


void LIB_feelfem90smpiMUMPSCA <MT_ff90smpiMUMPSCA>::SolverLibraryParameters(void)
{
  doNothingNow("void LIB_feelfem90smpiMUMPSCA <MT_ff90smpiMUMPSCA>::SolverLibraryParameters(void)");
  return;
}

void LIB_feelfem90smpiMUMPSCA <MT_ff90smpiMUMPSCA>::SolverLibraryVariableDefinition(void)
{
  COMMENTlong("Solver Library dependent variables(MUMPSCA)");
  writeSource("! all values are in type(DMUMPS_STRUC) ");

  com();

  return;
}
//
void LIB_feelfem90smpiMUMPSCA <MT_ff90smpiMUMPSCA>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  int solveElementNo = 1 ;   // P2 limitation FIX

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  F90useSolveLIB();
  // library dependent co-solve routine module
  pushSource("! no use for MUMPS solver");

  F90useSolveMT();
  F90useSolvePM(solvePtr);
  
  
  fortImplicit();
  com();

  DoDeclareVariablesFromMainPM( solvePtr->VariablePtrLst());   //Fortran dependent
  

  return;
}

void LIB_feelfem90smpiMUMPSCA<MT_ff90smpiMUMPSCA>::
GenerateCoSolveSolverParamRoutine(Solve *solvePtr)
{
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED

  char  hereRoutineName[BUFSIZ];
  char *hereSourceName;

  int solveElementNo = 1;   // P2 FIXED to 1

  int ivars;                // number of unknowns


  // no CoSolveSolverParmeter routine is needed for MUMPSCA model  

  return;

}


//Library dependent solve-co routine generator
void LIB_feelfem90smpiMUMPSCA <MT_ff90smpiMUMPSCA>::
GenerateCoSolveRoutinesLIB(Solve *solvePtr)
{
  GenerateCoSolveSolverParamRoutine(solvePtr);  // nothing in MUMPSCA
  return;
}
