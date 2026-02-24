/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElemGeneratorTemplate.hpp
 *  Date     : 1999/12/09
 *  Modified : 1999/12/09
 *  Modified : 2001/01/31  ADD LINKLEVEL_ELEM
 *  Modified : 2001/11/29  ADD Vector Assemble version
 *
 *  Purpose  : Element assembly routine generator
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
 *
 */

#ifndef FEM_CLASS_ELEMGENERATOR
#define FEM_CLASS_ELEMGENERATOR

#include <iostream>   // for std::cout (constructor debug message)
#include "SolveElement.hpp"
#include "ElemScheme.hpp"
#include "ElemGeneratorVirtuals.hpp"

template <class MatMODEL>
class ElemGeneratorTemplate : public MatMODEL, public ElemScheme {
public:
  ElemGeneratorTemplate() { ; }
  ElemGeneratorTemplate(SolveElement *) {
    std::cout << "Do nothing ElemGeneratorTemplate constructor(SolveElement*)\n";
  }
  ~ElemGeneratorTemplate() { ; }

  void ElemRoutineInitialize  (Solve *,SolveElement *);
  void ElemRoutineTerminate   (void);

  void ElemRoutineHeader      (SolveElement *);
  void ElemParameters         (SolveElement *);
  void ElemVariableDefinitions(SolveElement *);
  void ElemInitializer        (SolveElement *);
  void ElemElementLoopStart   (SolveElement *,int);  // int is flag for own/ex
  void ElemCallEcalRoutine    (SolveElement *,int);
  void ElemAssembleMatrix     (SolveElement *,int);
  void ElemElementLoopEnd     (SolveElement *,int);
  void ElemReturnSequence     (SolveElement *);

  // for vector processing
  void ElemQuadratureLoopStart (SolveElement *,int);  // int is Quadrature No.
  void ElemQuadratureLoopEnd   (SolveElement *,int);
  void ElemQuadLoopPreparation (SolveElement *,int);
  void ElemQuadLoopMakeAllElement(SolveElement *,int);

private:
  int   solveNo;
  int   elemNo;
  char *routineName;
  char *sourceName;
};

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemRoutineInitialize(Solve *solvePtr,
                                                            SolveElement *solveElementPtr)
{
  solveNo     = solvePtr->GetSolveNo();
  elemNo      = solveElementPtr->GetElemNo();
  routineName = this->GetElemRoutineName(solveNo, elemNo);
  sourceName  = this->GetSourceName(routineName);
  this->OpenSource(sourceName, LINKLEVEL_ELEM);
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemRoutineTerminate(void)
{
  this->CloseSource();
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemRoutineHeader(SolveElement *solveElementPtr)
{
  this->DoElemRoutineHeaderMT(solveElementPtr);    // MT model
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemParameters(SolveElement *solveElementPtr)
{
  this->DoElemParameters(solveElementPtr);           // PM
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemVariableDefinitions(SolveElement *solveElementPtr)
{
  this->DoElemVariableDefinitionsPM(solveElementPtr);    // PM
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemInitializer(SolveElement *solveElementPtr)
{
  this->DoElemInitializer(solveElementPtr);       // PM  data ienp,iedp, call eset
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemElementLoopStart(SolveElement *solveElementPtr,
                                                           int flag)
{
  (void)solveElementPtr; // kept for interface compatibility; not used here
  this->DoElemElementLoopStart(flag);                // PM
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemQuadratureLoopStart(SolveElement *solveElementPtr,
                                                              int quadNo)
{
  this->DoElemQuadratureLoopStart(solveElementPtr, quadNo); // PM
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemQuadLoopPreparation(SolveElement *solveElementPtr,
                                                              int quadNo)
{
  this->DoElemQuadLoopPreparation(solveElementPtr, quadNo); // PM
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemQuadLoopMakeAllElement(SolveElement *solveElementPtr,
                                                                 int quadNo)
{
  this->DoElemQuadLoopMakeAllElement(solveElementPtr, quadNo); // PM
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemCallEcalRoutine(SolveElement *solveElementPtr,
                                                          int flag)
{
  this->DoElemCallEcalRoutine(solveElementPtr, flag);  // PM
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemAssembleMatrix(SolveElement *solveElementPtr,
                                                         int flag)
{
  (void)solveElementPtr; // kept for interface compatibility; not used here
  this->DoElemAssembleMatrix(flag);                   // MT
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemElementLoopEnd(SolveElement *solveElementPtr,
                                                         int flag)
{
  (void)solveElementPtr; // kept for interface compatibility; not used here
  this->DoElemElementLoopEnd(flag);                   // PM
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemQuadratureLoopEnd(SolveElement *solveElementPtr,
                                                            int flag)
{
  this->DoElemQuadratureLoopEnd(solveElementPtr, flag); // PM
  return;
}

template <class MatMODEL>
void ElemGeneratorTemplate<MatMODEL>::ElemReturnSequence(SolveElement *solveElementPtr)
{
  this->DoElemReturnSequence(solveElementPtr);                   // PM
  return;
}

#endif // FEM_CLASS_ELEMGENERATOR
