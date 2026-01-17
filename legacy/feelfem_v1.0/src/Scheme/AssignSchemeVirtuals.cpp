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
 */
#include <iostream.h>
#include "AssignScheme.hpp"

void AssignScheme::AssignRoutineInitialize(Assign *)
{
  cerr << "This is virtual AssignScheme::AssignRoutineInitialize(Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignRoutineTerminate(Assign *)
{
  cerr << "This is virtual AssignScheme::AssignRoutineTerminate(Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignRoutineHeader(Assign *)
{
  cerr << "This is virtual AssignScheme::AssignRoutineHeader(Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignParameters(Assign *)
{
  cerr << "This is virtual AssignScheme::AssignParameters(Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignVariableDefinitions(Assign *)
{
  cerr << "This is virtual AssignScheme::AssignVariableDefinitions(Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignGetGeometryData(Assign *)
{
  cerr << "This is virtual AssignScheme::AssignGetGeometryData(Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignStatement(Assign *)
{
  cerr << "This is virtual AssignScheme::AssignStatement(Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignReturnSequence(Assign *)
{
  cerr << "This is virtual AssignScheme::AssignReturnSequence(Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignCoRoutineInitialize (Assign *)
{
  cerr << "This is virtual ASsignScheme::AssignCoRoutineInitialize (Assign *)"
       << endl;
  return;
}
 
void AssignScheme::AssignCoRoutineReturnSequence   (Assign *)
{
  cerr << "This is virtual void AssignScheme::AssignCoRoutineReturnSequence"
       << endl;
  return;
}

void AssignScheme::AssignCoRoutineTerminate        (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignCoRoutineTerminate"
       << endl;
  return;
}


//void AssignScheme::AssignRoutineHeaderEwQuad (Assign *)
//{
//  cerr << "This is virtual AssignScheme::AssignRoutineHeaderEwQuad (Assign *)"
//       << endl;
//  return;
//}

void AssignScheme::AssignParametersEwQuad    (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignParametersEwQuad    (Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignVariableDefinitionsEwQuad (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignVariableDefinitionsEwQuad"
       << endl;
  return;
}

void AssignScheme::AssignInitializeEwQuad(Assign*)
{
  cerr << "This is virtual AssignScheme::AssignInitializeEwQuad    (Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignLoopStartEwQuad     (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignLoopStartEwQuad     (Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignAssignmentEwQuad    (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignAssignmentEwQuad    (Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignLoopEndEwQuad       (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignLoopEndEwQuad       (Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignCoRoutineHeaderEwQuad      (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignCoRoutineHeaderEwQuad"
       << endl;
  return;
}

void AssignScheme::AssignCoRoutineParametersEwQuad  (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignCoRoutineParametersEwQuad"
       << endl;
  return;
}

void AssignScheme::AssignCoRoutineVariableDefinitionsEwQuad (Assign *)
{
  cerr << "This is virtual AssignCoRoutineVariableDefinitionsEwQuad (Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignCoRoutineQuadratureSettingsEwQuad  (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignCoRoutineQuadratureSettingsEwQuad"
       << endl;
  return;
}

void AssignScheme::AssignCoRoutineStatementEwQuad           (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignCoRoutineStatementEwQuad"
       << endl;
  return;
}

void AssignScheme::AssignInitializeIntegral(Assign*)
{
  cerr << "This is virtual AssignScheme::AssignInitializeIntegral    (Assign *)"
       << endl;
  return;
}


void AssignScheme::AssignAssignmentIntegral    (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignAssignmentIntegral    (Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignLoopEndIntegral    (Assign *)
{
  cerr << "This is virtual AssignScheme::AssignLoopEndIntegral     (Assign *)"
       << endl;
  return;
}

void AssignScheme::AssignCoRoutineHeaderIntegral(Assign *)
{
  cerr << "This is virtual AssignScheme::AssignCoRoutineHeaderIntegral"
       << endl;
  return;
}

void AssignScheme::AssignCoRoutineVariableDefinitionsIntegral(Assign *)
{
  cerr << "This is virtual AssignScheme::AssignCoRoutineVariableDefinitionsIntegral"
       << endl;
  return;
}

void AssignScheme::AssignCoRoutineStatementIntegral(Assign *)
{
  cerr << "This is virtual AssignScheme::AssignCoRoutineStatementIntegral"
       << endl;
  return;
}
