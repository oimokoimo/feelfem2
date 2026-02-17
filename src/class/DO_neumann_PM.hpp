/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_neumann.hpp
 *  Date     : 2001/11/29
 *  Modified : 
 *  
 *  Purpose  : DoNeumann family
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

void DoNeumannArgumentVariableDefinitionsPM(Neumann *);
void DoNeumannAutoVariableDefinitionsPM(Neumann *);
void DoNeumannReturnSequencePM(Neumann *);
void DoNeumannParametersPM(Neumann *);
void DoNeumannInitializerPM(Neumann *);
void DoNeumannBoundaryElementLoopStartPM(Neumann *);
void DoNeumannBoundaryElementLoopEndPM(Neumann *);

void doNeumannEsetCalcInterpolationSub( Neumann *, Element *, int);
void doNeumannEcalSetValAtGaussP( Neumann *);
void pushNeumannEcalCoordSub(Neumann *, const char *);

void pushNeumannCoordDiff(Neumann *,const char *dx,const char *dr);


void doIthNeumannCallInSolvePM(Solve *,int);  // separete PM part from MT
void doIthNeumannCallInSolvePM2(Solve *,int);  // separete PM part from MT
