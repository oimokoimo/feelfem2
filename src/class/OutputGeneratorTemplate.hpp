/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : OutputGeneratorTemplate.hpp
 *  Date     : 2002/07/17
 *  Modified :
 *
 *  Purpose  :
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

#ifndef FEM_CLASS_OUTPUTGENERATORTEMPLATE
#define FEM_CLASS_OUTPUTGENERATORTEMPLATE

#include "OutputScheme.hpp"
#include "Output.hpp"

template <class PgMODEL>
class OutputGeneratorTemplate : public PgMODEL, public OutputScheme {
public:
  OutputGeneratorTemplate() = default;
  ~OutputGeneratorTemplate() = default;

  // Scheme procedures (implemented here)
  void OutputRoutineInitialize(Output *) ;
  void OutputRoutineTerminate(Output *) ;

  void OutputRoutineHeader(Output *) ;
  void OutputParameters(Output *) ;              // note: your file had both ...RoutineParameters and OutputParameters
  void OutputVariableDefinitions(Output *) ;

  void OutputGetGeometryData(Output *) ;
  void OutputStatement(Output *) ;

  void OutputReturnSequence(Output *) ;

  // Gid
  void OutputMeshData(Output *) ;

private:
  int outputNo = 0;

  // Prefer const char*; if your legacy APIs truly require char*, change back.
  const char *routineName = nullptr;
  const char *sourceName  = nullptr;
};

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

template <class PgMODEL>
void OutputGeneratorTemplate<PgMODEL>::OutputRoutineInitialize(Output *outputPtr)
{
  outputNo    = outputPtr->GetOutputNo();
  routineName = this->GetOutputRoutineName(outputNo);
  sourceName  = this->GetSourceName(routineName);
  this->OpenSource(sourceName, LINKLEVEL_OUTPUT);
}

template <class PgMODEL>
void OutputGeneratorTemplate<PgMODEL>::OutputRoutineTerminate(Output * /*outputPtr*/)
{
  this->CloseSource();
}

template <class PgMODEL>
void OutputGeneratorTemplate<PgMODEL>::OutputRoutineHeader(Output *outputPtr)
{
  this->DoOutputRoutineHeader(outputPtr);
}

template <class PgMODEL>
void OutputGeneratorTemplate<PgMODEL>::OutputParameters(Output *outputPtr)
{
  this->DoOutputParameters(outputPtr);
}

template <class PgMODEL>
void OutputGeneratorTemplate<PgMODEL>::OutputVariableDefinitions(Output *outputPtr)
{
  this->DoOutputVariableDefinitions(outputPtr);
}

template <class PgMODEL>
void OutputGeneratorTemplate<PgMODEL>::OutputGetGeometryData(Output *outputPtr)
{
  this->DoOutputGetGeometryData(outputPtr);
}

template <class PgMODEL>
void OutputGeneratorTemplate<PgMODEL>::OutputStatement(Output *outputPtr)
{
  this->DoOutputStatement(outputPtr);
}

template <class PgMODEL>
void OutputGeneratorTemplate<PgMODEL>::OutputReturnSequence(Output *outputPtr)
{
  this->DoOutputReturnSequence(outputPtr);
}

template <class PgMODEL>
void OutputGeneratorTemplate<PgMODEL>::OutputMeshData(Output *outputPtr)
{
  this->DoOutputMeshData(outputPtr);
}

#endif // FEM_CLASS_OUTPUTGENERATORTEMPLATE
