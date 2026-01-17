/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : cg_functions.hpp
 *  Date     : 2001/07/11
 *  Modified : 2002/04/16 (BCN)
 *  
 *  Purpose  :
 *  
 */

class Solve;
class Assign;

// solve series
void cg_NormalLinearProblem( Solve *);
void cg_NormalNonlinearProblem( Solve *);

// assignment series
void cg_AssignmentFEM1( Assign *);   // category 1 : Node FEM variable
void cg_AssignmentFEM2( Assign *);   // category 2 : Helmite FEM variable 
void cg_AssignmentFEM3( Assign *);   // category 3 : Vector FEM variable

void cg_AssignmentEWISE1( Assign *); // category 1 : with interpolation
void cg_AssignmentEWISE2( Assign *); // category 2 : quadrature point
void cg_AssignmentEWISE3( Assign *); // category 3 : material ewise

void cg_AssignmentScalar( Assign *); // scalar variable assignment
