/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : AssignGeneratorTemplate.hpp
 *  Date     : 2002/04/16 (BCN)
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
 *    - C++ templates + dependent base lookup fix:
 *      add this-> for member lookup (two-phase lookup).
 *
 */

#ifndef FEM_CLASS_ASSIGNGENERATORTMPLATE
#define FEM_CLASS_ASSIGNGENERATORTMPLATE

#include "AssignScheme.hpp"
#include "Assign.hpp"

template <class PgMODEL>
class AssignGeneratorTemplate : public PgMODEL, public AssignScheme
{
public:
  AssignGeneratorTemplate() = default;   // do nothing in template generator class
  ~AssignGeneratorTemplate() = default;

  void AssignRoutineInitialize   (Assign *);
  void AssignRoutineTerminate    (Assign *);

  void AssignRoutineHeader       (Assign *);
  void AssignParameters          (Assign *);
  void AssignVariableDefinitions (Assign *);

  void AssignGetGeometryData     (Assign *);
  void AssignStatement           (Assign *);

  void AssignReturnSequence      (Assign *);

  // Coroutines
  void AssignCoRoutineInitialize       (Assign *);
  void AssignCoRoutineReturnSequence   (Assign *);
  void AssignCoRoutineTerminate        (Assign *);

  // EwiseQuad subroutines
  void AssignParametersEwQuad              (Assign *);
  void AssignVariableDefinitionsEwQuad     (Assign *);
  void AssignInitializeEwQuad              (Assign *);
  void AssignLoopStartEwQuad               (Assign *);         // ewise quad
  void AssignAssignmentEwQuad              (Assign *);
  void AssignLoopEndEwQuad                 (Assign *);

  // EwiseQuad Coroutines
  void AssignCoRoutineHeaderEwQuad                 (Assign *);
  void AssignCoRoutineParametersEwQuad             (Assign *);
  void AssignCoRoutineVariableDefinitionsEwQuad    (Assign *);
  void AssignCoRoutineQuadratureSettingsEwQuad     (Assign *);
  void AssignCoRoutineStatementEwQuad              (Assign *);

  // Integral
  void AssignInitializeIntegral (Assign *);
  void AssignAssignmentIntegral (Assign *);
  void AssignLoopEndIntegral    (Assign *);

  // Integral Coroutines
  void AssignCoRoutineHeaderIntegral              (Assign *);
  void AssignCoRoutineVariableDefinitionsIntegral (Assign *);
  void AssignCoRoutineStatementIntegral           (Assign *);

private:
  int   assignNo   = 0;
  const char *routineName = nullptr;
  const char *sourceName  = nullptr;
};

/////////////////////////////////////////////

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignRoutineInitialize(Assign *asPtr)
{
  assignNo    = asPtr->GetAssignNo();
  routineName = this->GetAssignRoutineName(assignNo);
  sourceName  = this->GetSourceName(routineName);
  this->OpenSource(sourceName, LINKLEVEL_ASSIGN);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignRoutineTerminate(Assign * /*asPtr*/)
{
  this->CloseSource();
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignRoutineHeader(Assign *asPtr)
{
  this->DoAssignRoutineHeader(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignParameters(Assign *asPtr)
{
  this->DoAssignParameters(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignVariableDefinitions(Assign *asPtr)
{
  this->DoAssignVariableDefinitions(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignGetGeometryData(Assign *asPtr)
{
  this->DoAssignGetGeometryData(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignStatement(Assign *asPtr)
{
  this->DoAssignStatement(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignReturnSequence(Assign *asPtr)
{
  this->DoAssignReturnSequence(asPtr);
}

// Coroutines
template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignCoRoutineInitialize(Assign *asPtr)
{
  assignNo    = asPtr->GetAssignNo();
  routineName = this->GetAssignCoRoutineName(assignNo);
  sourceName  = this->GetSourceName(routineName);
  this->OpenSource(sourceName, LINKLEVEL_COASSIGN);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignCoRoutineReturnSequence(Assign *asPtr)
{
  this->DoAssignCoRoutineReturnSequence(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignCoRoutineTerminate(Assign * /*asPtr*/)
{
  this->CloseSource();
}

// EwiseQuad subroutines
template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignParametersEwQuad(Assign *asPtr)
{
  this->DoAssignParametersEwQuad(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignVariableDefinitionsEwQuad(Assign *asPtr)
{
  this->DoAssignVariableDefinitionsEwQuad(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignInitializeEwQuad(Assign *asPtr)
{
  this->DoAssignInitializeEwQuad(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignLoopStartEwQuad(Assign *asPtr)
{
  this->DoAssignLoopStartEwQuad(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignAssignmentEwQuad(Assign *asPtr)
{
  this->DoAssignAssignmentEwQuad(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignLoopEndEwQuad(Assign *asPtr)
{
  this->DoAssignLoopEndEwQuad(asPtr);
}

// EwiseQuad Coroutines
template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignCoRoutineHeaderEwQuad(Assign *asPtr)
{
  this->DoAssignCoRoutineHeaderEwQuad(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignCoRoutineParametersEwQuad(Assign *asPtr)
{
  this->DoAssignCoRoutineParametersEwQuad(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignCoRoutineVariableDefinitionsEwQuad(Assign *asPtr)
{
  this->DoAssignCoRoutineVariableDefinitionsEwQuad(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignCoRoutineQuadratureSettingsEwQuad(Assign *asPtr)
{
  this->DoAssignCoRoutineQuadratureSettingsEwQuad(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignCoRoutineStatementEwQuad(Assign *asPtr)
{
  this->DoAssignCoRoutineStatementEwQuad(asPtr);
}

// Integral routines
template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignInitializeIntegral(Assign *asPtr)
{
  this->DoAssignInitializeIntegral(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignAssignmentIntegral(Assign *asPtr)
{
  this->DoAssignAssignmentIntegral(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignLoopEndIntegral(Assign *asPtr)
{
  this->DoAssignLoopEndIntegral(asPtr);
}

// Integral coroutines
template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignCoRoutineHeaderIntegral(Assign *asPtr)
{
  this->DoAssignCoRoutineHeaderIntegral(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignCoRoutineVariableDefinitionsIntegral(Assign *asPtr)
{
  this->DoAssignCoRoutineVariableDefinitionsIntegral(asPtr);
}

template <class PgMODEL>
void AssignGeneratorTemplate<PgMODEL>::AssignCoRoutineStatementIntegral(Assign *asPtr)
{
  this->DoAssignCoRoutineStatementIntegral(asPtr);
}

#endif // FEM_CLASS_ASSIGNGENERATORTMPLATE
