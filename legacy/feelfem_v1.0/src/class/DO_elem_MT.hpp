/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_elem_MT.hpp
 *  Date     : 2003/01/10
 *  Modified : 
 *  
 *  Purpose  : Matrix class related element
 *  
 */


void DoElemRoutineHeaderMT(SolveElement *);
void DoElemAssembleMatrix(int);

void doElemArgumentSequenceMT(SolveElement *);  // subsidary of routineHeader
void doElemVariableDefinitionsMT();
