/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : OutputSchemeVirtuals.cpp
 *  Date     : 2002/07/17
 *  Modified : 
 *  
 *  Purpose  : virtuals
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

#include <iostream>
#include "OutputScheme.hpp"

void OutputScheme::OutputRoutineInitialize(Output *)
{
  std::cerr << "This is virtual OutputScheme::OutputRoutineInitialize(Output *)"
       << std::endl;
  return;
}

void OutputScheme::OutputRoutineTerminate(Output *)
{
  std::cerr << "This is virtual OutputScheme::OutputRoutineTerminate(Output *)"
       << std::endl;
  return;
}

void OutputScheme::OutputRoutineHeader(Output *)
{
  std::cerr << "This is virtual OutputScheme::OutputRoutineHeader(Output *)"
       << std::endl;
  return;
}

void OutputScheme::OutputParameters(Output *)
{
  std::cerr << "This is virtual OutputScheme::OutputParameters(Output *)"
       << std::endl;
  return;
}

void OutputScheme::OutputVariableDefinitions(Output *)
{
  std::cerr << "This is virtual OutputScheme::OutputVariableDefinitions(Output *)"
       << std::endl;
  return;
}

void OutputScheme::OutputStatement(Output *)
{
  std::cerr << "This is virtual OutputScheme::OutputStatement(Output *)"
       << std::endl;
  return;
}

void OutputScheme::OutputReturnSequence(Output *)
{
  std::cerr << "This is virtual OutputScheme::OutputReturnSequence(Output *)"
       << std::endl;
  return;
}


// GiD related
void OutputScheme::OutputMeshData(Output *)  // for gid
{
  std::cerr << "This is virtual OutputScheme::OutputMeshData(Output *)"
       << std::endl;
  return;
}
