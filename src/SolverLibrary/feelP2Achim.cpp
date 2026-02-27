/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelP2Achim.cpp
 *  Date     : 1999/12/09
 *  Modified : 1999/12/09
 *  
 *  Purpose  :
 *  
 */
#include "MT_P2CRS.hpp"
#include "Solve.hpp"
#include "LIB_feelP2Achim.hpp"


//Default constructor 
template<> LIB_feelP2Achim <MT_P2CRS>::LIB_feelP2Achim()
{
  return;   // do nothing
}



//Default Destructor
template<>  LIB_feelP2Achim <MT_P2CRS>::~LIB_feelP2Achim() = default;

template<> void LIB_feelP2Achim <MT_P2CRS>::SolveCallSolverRoutine(Solve *solvePtr)
{
  wrtDEBUGcode("* LIB_feelP2Achim <MT_P2CRS>::SolveCallSolverRoutine");

  writeSource("*=========================");
  writeSource("* CALL Achim SOLVER     ");
  writeSource("*=========================");
  
  writeSource("      call wrtcrsfil(NO,neq,ncof,maxnzpr,");
  writeSource("     $     feel(np_VALMAT),feel(np_INDROW),feel(np_IPTRCOL),");
  writeSource("     $     feel(np_VFG),feel(np_V))");
  com();

  pushSource("      call report('P2 Achim Solver for solve ");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" END')");
  flushSource();
  comment();

  return;
}

//
template<> void LIB_feelP2Achim <MT_P2CRS>::DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) 
{
  wrtDEBUGcode("* LIB_feelP2Achim <MT_P2CRS>::DoSolveRoutineHeaderInLIB");

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  DoDeclareVariablesFromMainPM( solvePtr->VariablePtrLst());   //Fortran dependent

  return;
}
