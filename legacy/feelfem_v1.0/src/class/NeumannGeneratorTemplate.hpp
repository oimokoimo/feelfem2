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
 */

#ifndef FEM_CLASS_NEUMANNGENERATOR
#define FEM_CLASS_NEUMANNGENERATOR

#include "feeldef.hpp"
#include "NeumannScheme.hpp"

template <class MatMODEL> class NeumannGeneratorTemplate 
  : public MatMODEL, public NeumannScheme {

public:
  NeumannGeneratorTemplate() { return; }
  ~NeumannGeneratorTemplate(){ return; }
  
  void NeumannRoutineInitialize  (Solve *,Neumann *);
  void NeumannRoutineTerminate   (void          );

  void NeumannRoutineHeader      (Neumann *);
  void NeumannParameters         (Neumann *);
  void NeumannVariableDefinitions(Neumann *);
  void NeumannInitializer        (Neumann *);
  void NeumannBoundaryElementLoopStart(Neumann *);

  void NeumannApplyMatrix        (Neumann *);       //MT

  void NeumannBoundaryElementLoopEnd(Neumann *);

  void NeumannReturnSequence     (Neumann *);

private:
  int solveNo;
  int ncondNo;
  char *routineName;
  char *sourceName;

};


template <class MatMODEL> void NeumannGeneratorTemplate <MatMODEL>::
NeumannRoutineInitialize  (Solve *solvePtr,Neumann *nPtr)
{
  solveNo = solvePtr->GetSolveNo();
  ncondNo = nPtr->GetNcondNo();
  routineName = GetNeumannRoutineName(solveNo,ncondNo);
  sourceName  = GetSourceName(routineName);
  OpenSource(sourceName,LINKLEVEL_NCOND);

  return;
}

template <class MatMODEL> void NeumannGeneratorTemplate <MatMODEL>::
NeumannRoutineTerminate   (void          )
{
  CloseSource();
  return;
}


template <class MatMODEL> void NeumannGeneratorTemplate <MatMODEL>::
NeumannRoutineHeader   (Neumann *nPtr)
{
  DoNeumannRoutineHeaderMT(nPtr);     // MT 
  //  DoNeumannArgumentSequenceMT(nPtr);  // MT
  //  SourceStarters();                   // PM 
  return;
}

template <class MatMODEL> void NeumannGeneratorTemplate <MatMODEL>::
NeumannParameters         (Neumann *nPtr)
{
  DoNeumannParametersPM(nPtr);   // PM (NPG and NDF for P2 model)
  return;
}

template <class MatMODEL> void NeumannGeneratorTemplate <MatMODEL>::
NeumannVariableDefinitions(Neumann *nPtr)
{
  //  writeMatrixDeclarations();            //This is dependent MT 
  DoNeumannAutoVariableDefinitionsPM(nPtr); //PM
  return;
}


template <class MatMODEL> void NeumannGeneratorTemplate <MatMODEL>::
NeumannInitializer        (Neumann *nPtr)
{
  DoNeumannInitializerPM(nPtr);  // set quadrature, etc.
  return;
}

template <class MatMODEL> void NeumannGeneratorTemplate <MatMODEL>::
NeumannBoundaryElementLoopStart (Neumann *nPtr)
{
  DoNeumannBoundaryElementLoopStartPM( nPtr );
}

template <class MatMODEL> void NeumannGeneratorTemplate <MatMODEL>::
NeumannApplyMatrix        (Neumann *nPtr)
{
  DoNeumannApplyMatrixMT(nPtr);
  return;
}

template <class MatMODEL> void NeumannGeneratorTemplate <MatMODEL>::
NeumannBoundaryElementLoopEnd(Neumann *nPtr)
{
  DoNeumannBoundaryElementLoopEndPM(nPtr);
  return;
}

template <class MatMODEL> void NeumannGeneratorTemplate <MatMODEL>::
NeumannReturnSequence     (Neumann *nPtr)
{
  DoNeumannReturnSequencePM(nPtr);
  return;
}

#endif
