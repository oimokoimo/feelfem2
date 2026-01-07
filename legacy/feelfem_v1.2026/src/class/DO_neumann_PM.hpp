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
