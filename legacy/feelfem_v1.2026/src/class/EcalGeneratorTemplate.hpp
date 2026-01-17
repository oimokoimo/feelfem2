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
 */

#ifndef FEM_CLASS_ECALGENERATOR
#define FEM_CLASS_ECALGENERATOR

#include "SolveElement.hpp"
#include "DiscretizedComponent.hpp"

#include "EcalScheme.hpp"
#include "EcalInfo.hpp"

template <class ProgMODEL> class EcalGeneratorTemplate
  : public ProgMODEL, public EcalScheme {
public:
  EcalGeneratorTemplate()  {;}
  ~EcalGeneratorTemplate() {;}

  void EcalRoutineInitialize  (Solve *,SolveElement *);
  void EcalRoutineTerminate   (SolveElement *);

  void EcalRoutineHeader      (SolveElement *);
  void EcalParameters         (SolveElement *);
  void EcalVariableDefinitions(SolveElement *);
  void EcalInitializer        (SolveElement *);

  void EcalElementMatInitialize(SolveElement *);

  // start loop
  void EcalQuadLoopStart     (int, SolveElement *);
  void EcalCalcJacobian      (int, SolveElement *);
  void EcalSetValAtGaussP    (int, SolveElement *);
  void EcalCalcElementMatRHS (int, SolveElement *);
  void EcalQuadLoopEnd       (int, SolveElement *);

  void EcalReturnSequence     (SolveElement *);

private:
  int   solveNo;
  int   ecalNo;
  char *routineName;
  char *sourceName;

  EcalInfo *ecalInfoPtr;
};

template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalRoutineInitialize (Solve *solvePtr,SolveElement *solveElementPtr)
{
  solveNo     = solvePtr->GetSolveNo();
  ecalNo      = solveElementPtr->GetElemNo();        // elem = ecal
  routineName = GetEcalRoutineName(solveNo,ecalNo);
  sourceName  = GetSourceName(routineName);
  OpenSource(sourceName,LINKLEVEL_ECAL);

  return;
}

template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalRoutineTerminate (SolveElement *sePtr)
{
  CloseSource();

  // generate eset routine
  GenerateCoSolveEcalRoutines( sePtr );
  return;
}


template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalRoutineHeader (SolveElement *solveElementPtr)
{
  DoEcalRoutineHeader(solveElementPtr);  
  return;
}


template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalParameters (SolveElement *solveElementPtr)
{
  DoEcalParameters(solveElementPtr);         
  return;
}

template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalVariableDefinitions (SolveElement *solveElementPtr)
{
  DoEcalVariableDefinitions(solveElementPtr); 
  return;
}

template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalInitializer (SolveElement *solveElementPtr)
{
  //  DoEcalInitializer(solveElementPtr);       //PM  data ienp,iedp, call eset
  return;
}

template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalElementMatInitialize(SolveElement *sePtr)
{
  DoEcalElementMatInitialize(sePtr);    
  return;
}

template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalQuadLoopStart     (int quadNo, SolveElement *sePtr)
{
  DoEcalQuadLoopStart(quadNo,sePtr);
  return;
}

template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalCalcJacobian      (int quadNo, SolveElement *sePtr)
{
  DoEcalCalcJacobian(quadNo,sePtr);
  return;
}

template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalSetValAtGaussP    (int quadNo, SolveElement *sePtr)
{
  DoEcalSetValAtGaussP(quadNo,sePtr);
  return;
}

template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalCalcElementMatRHS (int quadNo, SolveElement *sePtr)
{
  DoEcalCalcElementMatRHS( quadNo, sePtr );
  return;
}

template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalQuadLoopEnd       (int quadNo, SolveElement *sePtr)
{
  DoEcalQuadLoopEnd(quadNo,sePtr);
  return;
}

template <class ProgMODEL> void EcalGeneratorTemplate<ProgMODEL>::
EcalReturnSequence     (SolveElement *sePtr)
{
  DoEcalReturnSequence(sePtr);
  return;
}

#endif
