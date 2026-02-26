/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : NeumannGeneratorTemplate.hpp
 *  Date     : 2000/01/19
 *  Modified : 2001/01/31 (ADD LINKLEVEL_NCOND)
 *
 *  Purpose  : Generate Neumann routines
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

#ifndef FEM_CLASS_NEUMANNGENERATOR
#define FEM_CLASS_NEUMANNGENERATOR

#include "feeldef.hpp"
#include "NeumannScheme.hpp"

// forward declarations (reduce include coupling)
class Solve;
class Neumann;

template <class MatMODEL>
class NeumannGeneratorTemplate : public MatMODEL, public NeumannScheme {
public:
  NeumannGeneratorTemplate() = default;
  ~NeumannGeneratorTemplate() = default;

  void NeumannRoutineInitialize  (Solve *, Neumann *);
  void NeumannRoutineTerminate   ();

  void NeumannRoutineHeader      (Neumann *);
  void NeumannParameters         (Neumann *);
  void NeumannVariableDefinitions(Neumann *);
  void NeumannInitializer        (Neumann *);
  void NeumannBoundaryElementLoopStart(Neumann *);

  void NeumannApplyMatrix        (Neumann *);       // MT
  void NeumannBoundaryElementLoopEnd(Neumann *);

  void NeumannReturnSequence     (Neumann *);

private:
  int solveNo = 0;
  int ncondNo = 0;

  const char *routineName = nullptr;
  const char *sourceName  = nullptr;
};

//------------------------------------------------------------

template <class MatMODEL>
inline void NeumannGeneratorTemplate<MatMODEL>::NeumannRoutineInitialize(
    Solve *solvePtr, Neumann *nPtr)
{
  solveNo = solvePtr->GetSolveNo();
  ncondNo = nPtr->GetNcondNo();

  // NOTE: two-phase lookup: qualify through this->
  routineName = this->GetNeumannRoutineName(solveNo, ncondNo);
  sourceName  = this->GetSourceName(routineName);
  this->OpenSource(sourceName, LINKLEVEL_NCOND);
}

template <class MatMODEL>
inline void NeumannGeneratorTemplate<MatMODEL>::NeumannRoutineTerminate()
{
  this->CloseSource();
}

template <class MatMODEL>
inline void NeumannGeneratorTemplate<MatMODEL>::NeumannRoutineHeader(Neumann *nPtr)
{
  this->DoNeumannRoutineHeaderMT(nPtr);   // MT
  // this->DoNeumannArgumentSequenceMT(nPtr);  // MT (if used)
  // this->SourceStarters();                   // PM (if used)
}

template <class MatMODEL>
inline void NeumannGeneratorTemplate<MatMODEL>::NeumannParameters(Neumann *nPtr)
{
  this->DoNeumannParametersPM(nPtr);      // PM (NPG and NDF for P2 model)
}

template <class MatMODEL>
inline void NeumannGeneratorTemplate<MatMODEL>::NeumannVariableDefinitions(Neumann *nPtr)
{
  // this->writeMatrixDeclarations();          // MT dependent (if used)
  this->DoNeumannAutoVariableDefinitionsPM(nPtr);   // PM
}

template <class MatMODEL>
inline void NeumannGeneratorTemplate<MatMODEL>::NeumannInitializer(Neumann *nPtr)
{
  this->DoNeumannInitializerPM(nPtr);     // set quadrature, etc.
}

template <class MatMODEL>
inline void NeumannGeneratorTemplate<MatMODEL>::NeumannBoundaryElementLoopStart(Neumann *nPtr)
{
  this->DoNeumannBoundaryElementLoopStartPM(nPtr);
}

template <class MatMODEL>
inline void NeumannGeneratorTemplate<MatMODEL>::NeumannApplyMatrix(Neumann *nPtr)
{
  this->DoNeumannApplyMatrixMT(nPtr);
}

template <class MatMODEL>
inline void NeumannGeneratorTemplate<MatMODEL>::NeumannBoundaryElementLoopEnd(Neumann *nPtr)
{
  this->DoNeumannBoundaryElementLoopEndPM(nPtr);
}

template <class MatMODEL>
inline void NeumannGeneratorTemplate<MatMODEL>::NeumannReturnSequence(Neumann *nPtr)
{
  this->DoNeumannReturnSequencePM(nPtr);
}

#endif // FEM_CLASS_NEUMANNGENERATOR
