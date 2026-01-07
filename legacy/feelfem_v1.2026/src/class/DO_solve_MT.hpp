/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_solve_MT.hpp
 *  Date     : 2003/01/10
 *  Modified : 
 *  
 *  Purpose  : Matrix class related solve
 *  
 */

void DoSolveVariableDefinitionsMT();  // MT dependent variables
void DoSolveInitializerMT(Solve *);
void DoSolveMatrixAllocate(Solve *); // Current P2 no dependency on solve class
void DoSolveCallAssembleRoutine    ( Solve *);
