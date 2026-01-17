/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElemNormalAssembly.cpp
 *  Date     : 1999/12/10
 *  Modified : 1999/12/10
 *  
 *  Purpose  : Normal assemble scheme 
 *  
 */

#include "ElemScheme.hpp"

void ElemScheme::DistributedAssembly( Solve *solvePtr,SolveElement *sePtr)
{

  ElemRoutineInitialize(solvePtr,sePtr);
  ////////////////////////////////
  ElemRoutineHeader         ( sePtr );
  
  ElemParameters          ( sePtr );

  ElemVariableDefinitions ( sePtr );

  ElemInitializer         ( sePtr );
  
  /* My PE's element roop */
  ElemElementLoopStart    ( sePtr ,MY_ELEMENT);

  ElemCallEcalRoutine     ( sePtr ,MY_ELEMENT);
  
  ElemAssembleMatrix      ( sePtr ,MY_ELEMENT);

  ElemElementLoopEnd      ( sePtr ,MY_ELEMENT);

  /* Other PE's element roop */
  ElemElementLoopStart    ( sePtr ,OTHER_ELEMENT);

  ElemCallEcalRoutine     ( sePtr ,OTHER_ELEMENT);
  
  ElemAssembleMatrix      ( sePtr ,OTHER_ELEMENT);

  ElemElementLoopEnd      ( sePtr ,OTHER_ELEMENT);
  

  ElemReturnSequence      ( sePtr);   // Language dependent

  /////////////////////////////////
  ElemRoutineTerminate();

  return;
}


