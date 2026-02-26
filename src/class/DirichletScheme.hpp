/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DirichletScheme.hpp
 *  Date     : 1999/12/22
 *  Modified : 1999/12/22
 *  
 *  Purpose  : Dirichlet Scheme 
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

#ifndef FEM_CLASS_DIRICHLETSCHEME
#define FEM_CLASS_DIRICHLETSCHEME

class Solve;

#include "Dirichlet.hpp"

class DirichletScheme {
public:
  DirichletScheme();
  ~DirichletScheme();


  // Mathematical algorithms
  void DirichletNormalLinear   (Solve *, Dirichlet *);
  void DirichletNormalNonlinear(Solve *, Dirichlet *);


  // Basic main procedures in FEM processing
  virtual void DirichletRoutineInitialize  (Solve *,Dirichlet *);
  virtual void DirichletRoutineTerminate   (void          );

  virtual void DirichletRoutineHeader      (Dirichlet *);
  virtual void DirichletParameters         (Dirichlet *);
  virtual void DirichletVariableDefinitions(Dirichlet *);
  virtual void DirichletInitializer        (Dirichlet *);
  virtual void DirichletLoopStart          (Dirichlet *);
  virtual void DirichletCalcBoundaryValue  (Dirichlet *);
  virtual void DirichletApplyMatrix        (Dirichlet *);
  virtual void DirichletLoopEnd            (Dirichlet *);
  virtual void DirichletReturnSequence     (Dirichlet *);


private:
  static int dirichletSchemes;

};

#endif
