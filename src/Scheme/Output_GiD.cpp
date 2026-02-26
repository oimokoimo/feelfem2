/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Output_GiD.cpp
 *  Date     : 2002/07/17
 *  Modified : 
 *  
 *  Purpose  : output program for GiD post processor
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

#include "OutputScheme.hpp"


void OutputScheme::GiDOutput(Output *outputPtr)
{
  OutputRoutineInitialize   (outputPtr);
  
  // Basic subroutine procedures
  OutputRoutineHeader       (outputPtr);

  OutputParameters          (outputPtr);

  OutputVariableDefinitions (outputPtr);
  
  OutputMeshData            (outputPtr);

  OutputStatement           (outputPtr);
  
  OutputReturnSequence      (outputPtr);

  OutputRoutineTerminate    (outputPtr);

  return;
}
