/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : aistpcp90_mainScheme.cpp
 *  Date     : 2002/06/28
 *  Modified : 
 *  
 *  Purpose  : Scheme part of main routine for aistpcp90 program model
 *  
 *           
 *  
 */

#include "PM_aistpcp90.hpp"

// Main pointer is not used...
void PM_aistpcp90::DoMainScheme_solve(Main *mPtr, Solve *solvePtr)
{
  pushSource("call ");
  pushSource( GetSolveRoutineName( solvePtr->GetSolveNo() ));
  pushSource("(myrank,nprocs,iedom,                         &");
  flushSource();

  pushSource("            npmax,");
  pushCoordinateSource();
  pushSource(",firstEdatPtr,firstNsetPtr,solveLst &");
  flushSource();

  pushSource("           ");
  pushVariableListInMain( solvePtr->VariablePtrLst());
  pushSource(")");
  flushSource();

  return;
}
