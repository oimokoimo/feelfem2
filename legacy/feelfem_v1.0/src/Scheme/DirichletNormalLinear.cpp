/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DirichletNormalLinear.cpp
 *  Date     : 2000/01/12
 *  Modified : 2000/01/12
 *  
 *  Purpose  : Normal linear Dirichlet condition
 *  
 */

#include "DirichletScheme.hpp"

void DirichletScheme::DirichletNormalLinear( Solve *solvePtr,Dirichlet *dPtr)
{
  
  DirichletRoutineInitialize( solvePtr , dPtr);
  
  DirichletRoutineHeader    ( dPtr );
  
  DirichletParameters       ( dPtr );
  
  DirichletVariableDefinitions( dPtr );

  DirichletInitializer           ( dPtr );    // PM dependent
  
  DirichletLoopStart             ( dPtr );    // PM dependent

  DirichletCalcBoundaryValue     ( dPtr );    // PM dependent

  DirichletApplyMatrix           ( dPtr );    // MT dependent

  DirichletLoopEnd               ( dPtr );    // PM dependent
  
  DirichletReturnSequence        ( dPtr );
  
  DirichletRoutineTerminate(  );
  return;
}
