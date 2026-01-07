/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelP2iwashita.cpp
 *  Date     : 2000/11/23
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include "MT_P2SID.hpp"
#include "Solve.hpp"
#include "LIB_feelP2iwashita.hpp"


//Default constructor 
LIB_feelP2iwashita <MT_P2SID>::LIB_feelP2iwashita()
{
  return;   // do nothing
}



//Default Destructor
LIB_feelP2iwashita <MT_P2SID>::~LIB_feelP2iwashita()
{
  return;  // do nothing;
}

void LIB_feelP2iwashita <MT_P2SID>::SolveCallSolverRoutine(Solve *solvePtr)
{
  writeSource("*=========================");
  writeSource("* CALL iwashita SOLVER    ");
  writeSource("*=========================");
  
  MODULEmallocERT("np_RES"   ,"residual(RES(NA))"    ,"neq"       ,"1");
  MODULEmallocERT("np_YYY"   ,"           Y(NA))"    ,"neq"       ,"1");
  MODULEmallocERT("np_CGPN"  ,"        CGPN(NA))"    ,"neq"       ,"1");
  MODULEmallocERT("np_CGQN"  ,"        CGQN(NA))"    ,"neq"       ,"1");
  MODULEmallocERT("np_CGDIAG","      CGDIAG(NA))"    ,"neq"       ,"1");
  MODULEmallocERT("np_CGLT"  ,"        CGLT(NA,MJ-1)","neq*(mj-1)","1");
  MODULEmallocERT("np_JCGLT" ,"       JCGLT(NA,MJ-1)","neq*(mj-1)","0");
  MODULEmallocERT("np_DDIAG" ,"       DDIAG(NA))"    ,"neq"       ,"1");
  MODULEmallocCHK();
  com();

  writeSource("      ERR = 1.0d-9");
  com();

  writeSource("      call PARAICCGB_feel(neq,mj,");
  writeSource("     $     feel(np_ja),feel(np_a),feel(np_b),feel(np_solx),");
  writeSource("     $     feel(np_RES),feel(np_YYY),feel(np_CGPN),");
  writeSource("     $     feel(np_CGQN),feel(np_CGDIAG),feel(np_CGLT),");
  writeSource("     $     feel(np_JCGLT),feel(np_DDIAG),ERR)");
  com();

  pushSource("      call report('P2 iwashita Solver for solve ");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" END')");
  flushSource();
  comment();

  return;
}

//
void LIB_feelP2iwashita <MT_P2SID>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  DoDeclareVariablesFromMainPM( solvePtr->VariablePtrLst());   //Fortran dependent

  return;
}

