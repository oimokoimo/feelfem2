/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PM_ecal.hpp
 *  Date     : 2003/02/13
 *  Modified : 
 *  
 *  Purpose  : ecal related common routines for ProgramModel
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

  char *GetEcalRoutineName( int solveNo, int elemNo );
  void pushEcalRoutineName( SolveElement *);
  void EcalArgumentVariableDeclarationLst(SolveElement *,
					  orderedPtrList<Variable *>&);

  void EcalElementMatRHSVariableDeclaration(int solveNo,int elemNo);
  void EcalElementMatRHSCommon(int solveNo, int elemNo );  // NDF is assumed

  void EcalQuadArgumentVariableDeclaration(SolveElement *,
					   DiscretizedComponent *,
					   int solveNo,int elemNo, int quadNo);
  void EcalQuadCommon(SolveElement *,
		      DiscretizedComponent *dcPtr,
		      int solveNo,int elemNo,int quadNo);

  void DoEcalRoutineHeader( SolveElement *);
  void doEcalArgumentSequence(SolveElement *);
  void doEcalDeclareArgumentVariables( SolveElement *);
  void pushEcalJacobiSub(int quadNo,int freedom,int *ndPattern,
			 const char *,const char *,const char *);
  void pushEcalCoordSub(int quadNo,Element *,SolveElement *,const char *coord);
  void pushEcalDiffSub_1st(int quadNo,Element *ePtr,int dim,int no,int diff);

  //  void doEcalVariableDefinition(SolveElement *);

  void DoEcalParameters(SolveElement *);
  void DoEcalVariableDefinitions(SolveElement *);

  void DoEcalElementMatInitialize(SolveElement *);

  void DoEcalQuadLoopStart(int quadNo, SolveElement *);
  void DoEcalCalcJacobian(int quadNo, SolveElement *);
  void DoEcalSetValAtGaussP(int quadNo, SolveElement *);
  void DoEcalCalcElementMatRHS(int quadNo, SolveElement *);

  void DoEcalQuadLoopEnd(int quadNo, SolveElement *);

  void DoEcalReturnSequence(SolveElement *);
