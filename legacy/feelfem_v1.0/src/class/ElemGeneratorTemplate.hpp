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
 */

#ifndef FEM_CLASS_ELEMGENERATOR
#define FEM_CLASS_ELEMGENERATOR

#include "SolveElement.hpp"
#include "ElemScheme.hpp"
#include "ElemGeneratorVirtuals.hpp"

template <class MatMODEL> class ElemGeneratorTemplate
  : public MatMODEL, public ElemScheme {
public:
  ElemGeneratorTemplate()  {;}
  ElemGeneratorTemplate(SolveElement *) { 
    cout << "Do nothing ElemGeneratorTemplate constructor(SolveElement*)\n";
  }
  ~ElemGeneratorTemplate() {;}

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

  void ElemQuadratureLoopStart(SolveElement *,int);  // int is Quadrature No.
  void ElemQuadratureLoopEnd  (SolveElement *,int);  
  void ElemQuadLoopPreparation(SolveElement *,int);
  void ElemQuadLoopMakeAllElement(SolveElement *,int);
  

private:
  int   solveNo;
  int   elemNo;
  char *routineName;
  char *sourceName;
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemRoutineInitialize (Solve *solvePtr,SolveElement *solveElementPtr)
{
  solveNo     = solvePtr->GetSolveNo();
  elemNo      = solveElementPtr->GetElemNo();
  routineName = GetElemRoutineName(solveNo,elemNo);
  sourceName  = GetSourceName(routineName);
  OpenSource(sourceName,LINKLEVEL_ELEM);
  
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemRoutineTerminate (void)
{
  CloseSource();
  return;
}


template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemRoutineHeader (SolveElement *solveElementPtr)
{
  DoElemRoutineHeaderMT(solveElementPtr);    // MT model
  return;
}


template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemParameters (SolveElement *solveElementPtr)
{
  DoElemParameters(solveElementPtr);           //PM
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemVariableDefinitions (SolveElement *solveElementPtr)
{
  DoElemVariableDefinitionsPM(solveElementPtr);    //PM
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemInitializer (SolveElement *solveElementPtr)
{
  DoElemInitializer(solveElementPtr);       //PM  data ienp,iedp, call eset
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemElementLoopStart (SolveElement *solveElementPtr, int flag)
{
  DoElemElementLoopStart(flag);                // PM
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemQuadratureLoopStart(SolveElement *solveElementPtr, int quadNo)
{
  DoElemQuadratureLoopStart(solveElementPtr,quadNo);                // PM
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemQuadLoopPreparation(SolveElement *solveElementPtr,int quadNo)
{
  DoElemQuadLoopPreparation(solveElementPtr,quadNo);                // PM
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemQuadLoopMakeAllElement(SolveElement *solveElementPtr,int quadNo)
{
  DoElemQuadLoopMakeAllElement(solveElementPtr,quadNo);                // PM
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemCallEcalRoutine (SolveElement *solveElementPtr, int flag)
{
  DoElemCallEcalRoutine (solveElementPtr,flag);  //PM
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemAssembleMatrix (SolveElement *solveElementPtr,int flag)
{
  DoElemAssembleMatrix(flag);                   //MT
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemElementLoopEnd (SolveElement *solveElementPtr,int flag)
{
  DoElemElementLoopEnd(flag);                   //PM
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemQuadratureLoopEnd (SolveElement *solveElementPtr,int flag)
{
  DoElemQuadratureLoopEnd(solveElementPtr, flag);                //PM
  return;
}

template <class MatMODEL> void ElemGeneratorTemplate<MatMODEL>::
ElemReturnSequence (SolveElement *solveElementPtr)
{
  DoElemReturnSequence(solveElementPtr);                   //PM
  return;
}

#endif










