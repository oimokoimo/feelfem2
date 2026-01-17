/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90_mainScheme.cpp
 *  Date     : 2001/08/24
 *  Modified : 
 *  
 *  Purpose  : Scheme part of main routine for feelfem90 program model
 *  
 */

#include "PM_feelfem90DRAMA.hpp"


void PM_feelfem90DRAMA::DoMainScheme_solve(Main *mPtr, Solve *solvePtr)
{
  // call solve subroutine for feelfem90DRAMA 

  pushSource("call ");
  pushSource( GetSolveRoutineName( solvePtr->GetSolveNo() ));
  pushSource("(myrank,nprocs,mypeid, &");
  flushSource();

  pushSource("    npmax,");

  pushCoordinateSource();
  pushSource(",                          &");
  flushSource();

  writeSource("   firstDramaEdatPtr,firstDramaNsetPtr,solveLst &");

  pushVariableListInMain( solvePtr->VariablePtrLst());
  pushSource(")");
  flushSource();

  com();

  return;
}
