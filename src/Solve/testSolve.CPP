/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Routines for testing
 *  Date     : 1999/11/11
 *  Modified : 1999/11/16
 *  
 *  Purpose  :
 *  
 */

#include "Solve.hpp"

//void Solve::testSetLibraryType(int type)
//{
//  libraryType = type;
//  return;
//}

void Solve::testSetSolveNo(int no)
{
  solveNo = no;
  return;
}

void Solve::testSetMaxnodes(int nodes)
{
  maxnodes = nodes;
  return;
}

void Solve::testSetNonlinearFlag(int flag)
{
  nonlinearFlag = flag;
  return;
}
void Solve::testSetUnknowns(int num)
{
  unknowns = num;
  return;
}

