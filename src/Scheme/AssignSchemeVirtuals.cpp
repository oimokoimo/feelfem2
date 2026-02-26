/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : AssignSchemeVirtuals.cpp
 *  Date     : 2002/04/16 (BCN)
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
#include "AssignScheme.hpp"

void AssignScheme::AssignRoutineInitialize(Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignRoutineInitialize(Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignRoutineTerminate(Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignRoutineTerminate(Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignRoutineHeader(Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignRoutineHeader(Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignParameters(Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignParameters(Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignVariableDefinitions(Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignVariableDefinitions(Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignGetGeometryData(Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignGetGeometryData(Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignStatement(Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignStatement(Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignReturnSequence(Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignReturnSequence(Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignCoRoutineInitialize (Assign *)
{
  std::cerr << "This is virtual ASsignScheme::AssignCoRoutineInitialize (Assign *)"
       << std::endl;
  return;
}
 
void AssignScheme::AssignCoRoutineReturnSequence   (Assign *)
{
  std::cerr << "This is virtual void AssignScheme::AssignCoRoutineReturnSequence"
       << std::endl;
  return;
}

void AssignScheme::AssignCoRoutineTerminate        (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignCoRoutineTerminate"
       << std::endl;
  return;
}


//void AssignScheme::AssignRoutineHeaderEwQuad (Assign *)
//{
//  std::cerr << "This is virtual AssignScheme::AssignRoutineHeaderEwQuad (Assign *)"
//       << std::endl;
//  return;
//}

void AssignScheme::AssignParametersEwQuad    (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignParametersEwQuad    (Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignVariableDefinitionsEwQuad (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignVariableDefinitionsEwQuad"
       << std::endl;
  return;
}

void AssignScheme::AssignInitializeEwQuad(Assign*)
{
  std::cerr << "This is virtual AssignScheme::AssignInitializeEwQuad    (Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignLoopStartEwQuad     (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignLoopStartEwQuad     (Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignAssignmentEwQuad    (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignAssignmentEwQuad    (Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignLoopEndEwQuad       (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignLoopEndEwQuad       (Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignCoRoutineHeaderEwQuad      (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignCoRoutineHeaderEwQuad"
       << std::endl;
  return;
}

void AssignScheme::AssignCoRoutineParametersEwQuad  (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignCoRoutineParametersEwQuad"
       << std::endl;
  return;
}

void AssignScheme::AssignCoRoutineVariableDefinitionsEwQuad (Assign *)
{
  std::cerr << "This is virtual AssignCoRoutineVariableDefinitionsEwQuad (Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignCoRoutineQuadratureSettingsEwQuad  (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignCoRoutineQuadratureSettingsEwQuad"
       << std::endl;
  return;
}

void AssignScheme::AssignCoRoutineStatementEwQuad           (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignCoRoutineStatementEwQuad"
       << std::endl;
  return;
}

void AssignScheme::AssignInitializeIntegral(Assign*)
{
  std::cerr << "This is virtual AssignScheme::AssignInitializeIntegral    (Assign *)"
       << std::endl;
  return;
}


void AssignScheme::AssignAssignmentIntegral    (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignAssignmentIntegral    (Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignLoopEndIntegral    (Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignLoopEndIntegral     (Assign *)"
       << std::endl;
  return;
}

void AssignScheme::AssignCoRoutineHeaderIntegral(Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignCoRoutineHeaderIntegral"
       << std::endl;
  return;
}

void AssignScheme::AssignCoRoutineVariableDefinitionsIntegral(Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignCoRoutineVariableDefinitionsIntegral"
       << std::endl;
  return;
}

void AssignScheme::AssignCoRoutineStatementIntegral(Assign *)
{
  std::cerr << "This is virtual AssignScheme::AssignCoRoutineStatementIntegral"
       << std::endl;
  return;
}
