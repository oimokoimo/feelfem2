/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EcalGeneratorTemplate.hpp
 *  Date     : 2002/02/19
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

#ifndef FEM_CLASS_ECALGENERATOR
#define FEM_CLASS_ECALGENERATOR

#include "SolveElement.hpp"
#include "DiscretizedComponent.hpp"

#include "EcalScheme.hpp"
#include "EcalInfo.hpp"

// forward declarations
class Solve;

template <class ProgMODEL>
class EcalGeneratorTemplate : public ProgMODEL, public EcalScheme {
public:
  EcalGeneratorTemplate() = default;
  ~EcalGeneratorTemplate() = default;

  // EcalScheme overrides
  void EcalRoutineInitialize  (Solve *, SolveElement *) override;
  void EcalRoutineTerminate   (SolveElement *) override;

  void EcalRoutineHeader      (SolveElement *) override;
  void EcalParameters         (SolveElement *) override;
  void EcalVariableDefinitions(SolveElement *) override;
  void EcalInitializer        (SolveElement *) override;

  void EcalElementMatInitialize(SolveElement *) override;

  // start loop
  void EcalQuadLoopStart     (int, SolveElement *) override;
  void EcalCalcJacobian      (int, SolveElement *) override;
  void EcalSetValAtGaussP    (int, SolveElement *) override;
  void EcalCalcElementMatRHS (int, SolveElement *) override;
  void EcalQuadLoopEnd       (int, SolveElement *) override;

  void EcalReturnSequence     (SolveElement *) override;

private:
  int         solveNo   = 0;
  int         ecalNo    = 0;
  const char *routineName = nullptr;
  const char *sourceName  = nullptr;

  EcalInfo   *ecalInfoPtr  = nullptr; // 既存設計を尊重（所有権は別途）
};

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalRoutineInitialize(
    Solve *solvePtr, SolveElement *solveElementPtr)
{
  solveNo = solvePtr->GetSolveNo();
  ecalNo  = solveElementPtr->GetElemNo();  // elem = ecal

  routineName = this->GetEcalRoutineName(solveNo, ecalNo);
  sourceName  = this->GetSourceName(routineName);
  this->OpenSource(sourceName, LINKLEVEL_ECAL);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalRoutineTerminate(SolveElement *sePtr)
{
  this->CloseSource();

  // generate eset routine
  this->GenerateCoSolveEcalRoutines(sePtr);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalRoutineHeader(SolveElement *solveElementPtr)
{
  this->DoEcalRoutineHeader(solveElementPtr);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalParameters(SolveElement *solveElementPtr)
{
  this->DoEcalParameters(solveElementPtr);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalVariableDefinitions(
    SolveElement *solveElementPtr)
{
  this->DoEcalVariableDefinitions(solveElementPtr);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalInitializer(SolveElement *)
{
  // 元コード通り：今は何もしない
  // this->DoEcalInitializer(solveElementPtr);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalElementMatInitialize(SolveElement *sePtr)
{
  this->DoEcalElementMatInitialize(sePtr);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalQuadLoopStart(int quadNo, SolveElement *sePtr)
{
  this->DoEcalQuadLoopStart(quadNo, sePtr);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalCalcJacobian(int quadNo, SolveElement *sePtr)
{
  this->DoEcalCalcJacobian(quadNo, sePtr);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalSetValAtGaussP(int quadNo, SolveElement *sePtr)
{
  this->DoEcalSetValAtGaussP(quadNo, sePtr);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalCalcElementMatRHS(
    int quadNo, SolveElement *sePtr)
{
  this->DoEcalCalcElementMatRHS(quadNo, sePtr);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalQuadLoopEnd(int quadNo, SolveElement *sePtr)
{
  this->DoEcalQuadLoopEnd(quadNo, sePtr);
}

template <class ProgMODEL>
inline void EcalGeneratorTemplate<ProgMODEL>::EcalReturnSequence(SolveElement *sePtr)
{
  this->DoEcalReturnSequence(sePtr);
}

#endif // FEM_CLASS_ECALGENERATOR
