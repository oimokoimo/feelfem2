/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DirichletGeneratorTemplate.hpp
 *  Date     : 1999/12/21
 *  Modified : 2001/01/31 (ADD LINKLEVEL_DCOND)
 *
 *  Purpose  : Dirichlet Condition program generator template
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

#ifndef FEM_CLASS_DIRICHLETGENERATOR
#define FEM_CLASS_DIRICHLETGENERATOR

#include "feeldef.hpp"
#include "DirichletScheme.hpp"

// forward declarations to reduce header coupling
class Solve;
class Dirichlet;

template <class MatMODEL>
class DirichletGeneratorTemplate : public MatMODEL, public DirichletScheme {
public:
  DirichletGeneratorTemplate() = default;
  ~DirichletGeneratorTemplate() = default;

  void DirichletRoutineInitialize  (Solve *, Dirichlet *);
  void DirichletRoutineTerminate   ();

  void DirichletRoutineHeader      (Dirichlet *);
  void DirichletParameters         (Dirichlet *);
  void DirichletVariableDefinitions(Dirichlet *);
  void DirichletInitializer        (Dirichlet *);
  void DirichletLoopStart          (Dirichlet *);
  void DirichletCalcBoundaryValue  (Dirichlet *);
  void DirichletApplyMatrix        (Dirichlet *);
  void DirichletLoopEnd            (Dirichlet *);
  void DirichletReturnSequence     (Dirichlet *);

private:
  int solveNo  = 0;
  int dcondNo  = 0;

  const char *routineName = nullptr;
  const char *sourceName  = nullptr;
};

//------------------------------------------------------------

template <class MatMODEL>
inline void DirichletGeneratorTemplate<MatMODEL>::DirichletRoutineInitialize(
    Solve *solvePtr, Dirichlet *dPtr)
{
  solveNo = solvePtr->GetSolveNo();
  dcondNo = dPtr->GetDcondNo();

  // NOTE: two-phase lookup: qualify through this->
  routineName = this->GetDirichletRoutineName(solveNo, dcondNo);
  sourceName  = this->GetSourceName(routineName);
  this->OpenSource(sourceName, LINKLEVEL_DCOND);
}

template <class MatMODEL>
inline void DirichletGeneratorTemplate<MatMODEL>::DirichletRoutineTerminate()
{
  this->CloseSource();
}

template <class MatMODEL>
inline void DirichletGeneratorTemplate<MatMODEL>::DirichletRoutineHeader(Dirichlet *dPtr)
{
  // MT side
  this->DoDirichletRoutineHeaderMT(dPtr);

  // PM side (if needed)
  // this->SourceStarters();
}

template <class MatMODEL>
inline void DirichletGeneratorTemplate<MatMODEL>::DirichletVariableDefinitions(Dirichlet *dPtr)
{
  // PM side
  this->doDirichletAutoVariableDefinitionsPM(dPtr);
  // MT side
  this->doDirichletAutoVariableDefinitionsMT(dPtr);
}

template <class MatMODEL>
inline void DirichletGeneratorTemplate<MatMODEL>::DirichletParameters(Dirichlet * /*dPtr*/)
{
  // do nothing now...
}

template <class MatMODEL>
inline void DirichletGeneratorTemplate<MatMODEL>::DirichletInitializer(Dirichlet *dPtr)
{
  this->DoDirichletInitializer(dPtr);  // PM dependent
}

template <class MatMODEL>
inline void DirichletGeneratorTemplate<MatMODEL>::DirichletLoopStart(Dirichlet *dPtr)
{
  this->DoDirichletLoopStart(dPtr);
}

template <class MatMODEL>
inline void DirichletGeneratorTemplate<MatMODEL>::DirichletCalcBoundaryValue(Dirichlet *dPtr)
{
  this->DoDirichletCalcBoundaryValue(dPtr);
}

template <class MatMODEL>
inline void DirichletGeneratorTemplate<MatMODEL>::DirichletApplyMatrix(Dirichlet *dPtr)
{
  this->DoDirichletApplyMatrixMT(dPtr);
}

template <class MatMODEL>
inline void DirichletGeneratorTemplate<MatMODEL>::DirichletLoopEnd(Dirichlet *dPtr)
{
  this->DoDirichletLoopEnd(dPtr);
}

template <class MatMODEL>
inline void DirichletGeneratorTemplate<MatMODEL>::DirichletReturnSequence(Dirichlet *dPtr)
{
  this->DoDirichletReturnSequencePM(dPtr);
}

#endif // FEM_CLASS_DIRICHLETGENERATOR
