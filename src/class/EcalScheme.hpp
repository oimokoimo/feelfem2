/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : 
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

#ifndef FEM_ECALSCHEME_CLASS
#define FEM_ECALSCHEME_CLASS

#include "feeldef.hpp"
#include "SolveElement.hpp"

class Solve;

class EcalScheme {

public:
  EcalScheme();
  ~EcalScheme();

  // Scheme Libraries  (These are NOT VIRTUAL functions)
  void NormalElementStiffness(Solve *,SolveElement *);   


  // Basic main procedures in FEM procedures
  virtual void EcalRoutineInitialize  (Solve *,SolveElement *);
  virtual void EcalRoutineTerminate   (SolveElement *);

  virtual void EcalRoutineHeader      (SolveElement *);
  virtual void EcalParameters         (SolveElement *);
  virtual void EcalVariableDefinitions(SolveElement *);
  virtual void EcalInitializer        (SolveElement *);


  virtual void EcalElementMatInitialize(SolveElement *);

  // start loop
  virtual void EcalQuadLoopStart     (int, SolveElement *);
  virtual void EcalCalcJacobian      (int, SolveElement *);
  virtual void EcalSetValAtGaussP    (int, SolveElement *);
  virtual void EcalCalcElementMatRHS (int, SolveElement *);
  virtual void EcalQuadLoopEnd       (int, SolveElement *);

  virtual void EcalReturnSequence     (SolveElement *);


private:
  static int ecalSchemes;

};

#endif
