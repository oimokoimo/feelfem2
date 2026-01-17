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
 */
#include <iostream.h>
#include "OutputScheme.hpp"

void OutputScheme::OutputRoutineInitialize(Output *)
{
  cerr << "This is virtual OutputScheme::OutputRoutineInitialize(Output *)"
       << endl;
  return;
}

void OutputScheme::OutputRoutineTerminate(Output *)
{
  cerr << "This is virtual OutputScheme::OutputRoutineTerminate(Output *)"
       << endl;
  return;
}

void OutputScheme::OutputRoutineHeader(Output *)
{
  cerr << "This is virtual OutputScheme::OutputRoutineHeader(Output *)"
       << endl;
  return;
}

void OutputScheme::OutputParameters(Output *)
{
  cerr << "This is virtual OutputScheme::OutputParameters(Output *)"
       << endl;
  return;
}

void OutputScheme::OutputVariableDefinitions(Output *)
{
  cerr << "This is virtual OutputScheme::OutputVariableDefinitions(Output *)"
       << endl;
  return;
}

void OutputScheme::OutputStatement(Output *)
{
  cerr << "This is virtual OutputScheme::OutputStatement(Output *)"
       << endl;
  return;
}

void OutputScheme::OutputReturnSequence(Output *)
{
  cerr << "This is virtual OutputScheme::OutputReturnSequence(Output *)"
       << endl;
  return;
}


// GiD related
void OutputScheme::OutputMeshData(Output *)  // for gid
{
  cerr << "This is virtual OutputScheme::OutputMeshData(Output *)"
       << endl;
  return;
}
