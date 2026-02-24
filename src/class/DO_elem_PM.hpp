/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_elem_PM.hpp
 *  Date     : 2001/11/29
 *  Modified : 
 *  
 *  Purpose  : DoElem routine definitons
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

const char *GetElemRoutineName( int );
const char *GetElemRoutineName( int solveNo, int elemNo ) 
{return(GetElemRoutineName(solveNo)); }   //P2 limit

void  doElemStarters();
void  doElemDeclareArgumentVariablesPM(SolveElement *); // from RoutineHeader
void  DoElemParameters(SolveElement *);
void  DoElemVariableDefinitionsPM(SolveElement *);
void  DoElemInitializer(SolveElement *);
void  DoElemElementLoopStart(int);
void  DoElemCallEcalRoutine(SolveElement *,int);
void  DoElemElementLoopEnd(int);
void  DoElemReturnSequence(SolveElement *);
