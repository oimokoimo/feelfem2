/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElemScheme.hpp
 *  Date     : 1999/12/10 (Bonus!)
 *  Modified : 1999/12/10 
 *  
 *  Purpose  : Abstract numerical scheme definition class for elem
 *  
 *  
 *  
 */
#ifndef FEM_ELEMSCHEME_CLASS
#define FEM_ELEMSCHEME_CLASS

#include "feeldef.hpp"
#include "SolveElement.hpp"
#include "Solve.hpp"


class ElemScheme {

public:
  ElemScheme();
  ~ElemScheme();

  // Scheme Libraries  (These are NOT VIRTUAL functions)
  void NormalAssembly          (Solve *,SolveElement *);   
  void DistributedAssembly     (Solve *,SolveElement *);   
  void NormalVectorAssembly    (Solve *,SolveElement *);

  // Basic main procedures in FEM procedures
  virtual void ElemRoutineInitialize  (Solve *,SolveElement *);
  virtual void ElemRoutineTerminate   (void          );

  virtual void ElemRoutineHeader      (SolveElement *);
  virtual void ElemParameters         (SolveElement *);
  virtual void ElemVariableDefinitions(SolveElement *);
  virtual void ElemInitializer        (SolveElement *);

  virtual void ElemElementLoopStart   (SolveElement *,int);
  virtual void ElemCallEcalRoutine    (SolveElement *,int);
  virtual void ElemAssembleMatrix     (SolveElement *,int);
  virtual void ElemElementLoopEnd     (SolveElement *,int);

  virtual void ElemReturnSequence     (SolveElement *);


  // for ElemNormalVectorAssembly();
  virtual void ElemQuadratureLoopStart(SolveElement *,int quadNo);  
  virtual void ElemQuadratureLoopEnd  (SolveElement *,int quadNo);
  virtual void ElemQuadLoopPreparation(SolveElement *,int quadNo);
  virtual void ElemQuadLoopMakeAllElement(SolveElement *,int quadNo);


private:
  static int elemSchemes;

};

#endif
