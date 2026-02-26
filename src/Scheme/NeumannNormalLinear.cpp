/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : NeumannNormalLinear.cpp
 *  Date     : 2000/01/19
 *  Modified : 2000/01/19
 *  
 *  Purpose  : Normal linear Neumann condition algorithm
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#include "NeumannScheme.hpp"

void NeumannScheme::NeumannNormalLinear( Solve *solvePtr,Neumann *nPtr)
{
  
  NeumannRoutineInitialize( solvePtr , nPtr);
  
  NeumannRoutineHeader    ( nPtr );
  
  NeumannParameters       ( nPtr );
  
  NeumannVariableDefinitions( nPtr );
  
  NeumannInitializer           ( nPtr );

  NeumannBoundaryElementLoopStart( nPtr );

  NeumannApplyMatrix           ( nPtr );

  NeumannBoundaryElementLoopEnd( nPtr );
  
  NeumannReturnSequence        ( nPtr );
  
  NeumannRoutineTerminate();
  return;
}
