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
 */

#ifndef FEM_CLASS_DIRICHLETGENERATOR
#define FEM_CLASS_DIRICHLETGENERATOR

#include "feeldef.hpp"
#include "DirichletScheme.hpp"

template <class MatMODEL> class DirichletGeneratorTemplate 
  : public MatMODEL, public DirichletScheme {
public:
  DirichletGeneratorTemplate() { return; }
  ~DirichletGeneratorTemplate(){ return; }
  
  void DirichletRoutineInitialize  (Solve *,Dirichlet *);
  void DirichletRoutineTerminate   (void               );

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
  int solveNo;
  int dcondNo;
  char *routineName;
  char *sourceName;

};


template <class MatMODEL> void DirichletGeneratorTemplate <MatMODEL>::
DirichletRoutineInitialize  (Solve *solvePtr,Dirichlet *dPtr)
{
  solveNo = solvePtr->GetSolveNo();
  dcondNo = dPtr->GetDcondNo();
  routineName = GetDirichletRoutineName(solveNo,dcondNo);
  sourceName  = GetSourceName(routineName);
  OpenSource(sourceName,LINKLEVEL_DCOND);

  return;
}

template <class MatMODEL> void DirichletGeneratorTemplate <MatMODEL>::
DirichletRoutineTerminate   (void)
{
  CloseSource();
  return;
}


template <class MatMODEL> void DirichletGeneratorTemplate <MatMODEL>::
DirichletRoutineHeader   (Dirichlet *dPtr)
{
  DoDirichletRoutineHeaderMT(dPtr);      // MT
  //  SourceStarters();                  // PM 
  return;
}



template <class MatMODEL> void DirichletGeneratorTemplate <MatMODEL>::
DirichletVariableDefinitions(Dirichlet *dPtr)
{
  doDirichletAutoVariableDefinitionsPM(dPtr); //PM
  doDirichletAutoVariableDefinitionsMT(dPtr); //MT
  return;
}


template <class MatMODEL> void DirichletGeneratorTemplate <MatMODEL>::
DirichletParameters         (Dirichlet *dPtr)
{
  // do nothing now...
  return;
}



template <class MatMODEL> void DirichletGeneratorTemplate <MatMODEL>::
DirichletInitializer        (Dirichlet *dPtr)
{
  DoDirichletInitializer(dPtr);     // PM dependent
  return;
}


template <class MatMODEL> void DirichletGeneratorTemplate <MatMODEL>::
DirichletLoopStart        (Dirichlet *dPtr)
{
  DoDirichletLoopStart( dPtr );
  return;
}

template <class MatMODEL> void DirichletGeneratorTemplate <MatMODEL>::
DirichletCalcBoundaryValue        (Dirichlet *dPtr)
{
  DoDirichletCalcBoundaryValue( dPtr );
  return;
}

template <class MatMODEL> void DirichletGeneratorTemplate <MatMODEL>::
DirichletApplyMatrix        (Dirichlet *dPtr)
{
  DoDirichletApplyMatrixMT(dPtr);
  return;
}

template <class MatMODEL> void DirichletGeneratorTemplate <MatMODEL>::
DirichletLoopEnd        (Dirichlet *dPtr)
{
  DoDirichletLoopEnd( dPtr );
  return;
}

template <class MatMODEL> void DirichletGeneratorTemplate <MatMODEL>::
DirichletReturnSequence     (Dirichlet *dPtr)
{
  DoDirichletReturnSequencePM( dPtr );
  return;
}

#endif



