/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : NeumannScheme.hpp
 *  Date     : 2000/01/18
 *  Modified : 2000/01/18
 *  
 *  Purpose  :
 *  
 */
#ifndef FEM_CLASS_NEUMANNSCHEME
#define FEM_CLASS_NEUMANNSCHEME

#include "Neumann.hpp"
class Solve;

class NeumannScheme {
public:
  NeumannScheme();
  ~NeumannScheme();

  // Mathematical algorithms
  void NeumannNormalLinear (Solve *,Neumann *);

  // Basic main procedures in FEM processing

  virtual void NeumannRoutineInitialize  (Solve *,Neumann *);
  virtual void NeumannRoutineTerminate   (void          );

  virtual void NeumannRoutineHeader      (Neumann *);
  virtual void NeumannParameters         (Neumann *);
  virtual void NeumannVariableDefinitions(Neumann *);
  virtual void NeumannInitializer        (Neumann *);
  virtual void NeumannBoundaryElementLoopStart(Neumann *);

  virtual void NeumannApplyMatrix        (Neumann *);        //MT

  virtual void NeumannBoundaryElementLoopEnd(Neumann *);
  virtual void NeumannReturnSequence     (Neumann *);


private:
  static int neumannSchemes;
};

#endif
