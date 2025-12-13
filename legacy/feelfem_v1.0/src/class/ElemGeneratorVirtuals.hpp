/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElemGeneratorVirtuals.hpp
 *  Date     : 2001/11/29
 *  Modified : 
 *  
 *  Purpose  : DoElem virtual definitons
 *  
 */

#ifndef FEM_CLASS_ELEMGENERATORVIRTUALS
#define FEM_CLASS_ELEMGENERATORVIRTUALS

class SolveElement;

class ElemGeneratorVirtuals {

public:

  ElemGeneratorVirtuals() {; }
  ~ElemGeneratorVirtuals() {; }

  //  virtual void  DoElemStarters();


  //  virtual void  DoElemDeclareArgumentVariablesPM(SolveElement *sePtr); 
  virtual void  DoElemParameters(SolveElement *sePtr);
  virtual void  DoElemVariableDefinitionsPM(SolveElement *sePtr);
  virtual void  DoElemInitializer(SolveElement *sePtr);
  virtual void  DoElemElementLoopStart(int n);
  virtual void  DoElemCallEcalRoutine(SolveElement *sePtr,int n);
  virtual void  DoElemElementLoopEnd(int n);
  virtual void  DoElemReturnSequence(SolveElement *sePtr);

  // for vector processing  ElemNormalVectorAssembly() etc.
  virtual void  DoElemQuadratureLoopStart(SolveElement *sePtr, int no);
  virtual void  DoElemQuadratureLoopEnd(SolveElement *sePtr, int no);
  virtual void  DoElemQuadLoopPreparation(SolveElement *,int no);
  virtual void  DoElemQuadLoopMakeAllElement(SolveElement *,int no);

private:
};

#endif
