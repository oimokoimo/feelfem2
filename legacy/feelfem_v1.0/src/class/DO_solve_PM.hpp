/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_solve.inc
 *  Date     : 2001/11/29
 *  Modified : 
 *  
 *  Purpose  : Do solve routine definitions
 *  
 */

void  DoSolveStarters();                // copyright,date,implicit real*8
void  DoSolveParametersPM(Solve *);     // parameters (depend, and independs)
void  DoSolveVariableDefinitionsPM(Solve *);  // matrix independent parts

void  DoSolveInitialDefPM(Solve *);   // data statements, etc.
void  DoSolveInitializerPM(Solve *);  // problem dependent const variable, etc.
void  DoSolveDegreeOfFreedom(Solve *);    // calculate the degree of freedom
void  DoSolveAssemblyPreparation(Solve *);  // message exchange for fem vars
void  DoSolveBoundaryDataPreparation(Solve *);  //preparation for boundary data
void  DoSolveReturnSequence(Solve *);

void DoSolveReport( int , const char *);

void doSolveFreeMemoryPM(Solve *);
