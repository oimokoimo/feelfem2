/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_neumann_MT.hpp
 *  Date     : 2002/04/11
 *  Modified : 
 *  
 *  Purpose  : Matrix related Neumann generator
 *  
 */

void DoNeumannRoutineHeaderMT(Neumann *);
void DoNeumannArgumentSequenceMT(Neumann *);
void DoNeumannApplyMatrixMT(Neumann *);
  
void doNeumannVariableDefinitionsMT(void);
