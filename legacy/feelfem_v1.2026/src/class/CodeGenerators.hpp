/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : CodeGenerators.hpp
 *  Date     : 2002/02/06
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

// for solve block
class Solve;

void cg_NormalNonlinearProblem(Solve *);
void cg_NormalLinearProblem(Solve *);

// for assign block
class Assign;

void cg_AssignmentScalar( Assign *);
void cg_AssignmentEwiseQuad( Assign *);
void cg_AssignmentIntegral(Assign *);
// void cg_AssignmentBIntegral(Assign *);

// for output block
class Output;

void cg_Output(Output *);
