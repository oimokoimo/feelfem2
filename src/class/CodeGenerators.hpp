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
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  cg_ functions act as code-generation dispatchers.
 *  Actual code emission is implemented in backend-specific DoXXXX methods.
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
