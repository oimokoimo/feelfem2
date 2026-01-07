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
 */

char *GetElemRoutineName( int );
char *GetElemRoutineName( int solveNo, int elemNo ) 
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
