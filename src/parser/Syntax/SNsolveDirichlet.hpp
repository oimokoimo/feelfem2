/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveDirichlet.hpp
 *  Date     : 2001/07/24
 *  Modified : 
 *  
 *  Purpose  : Solve Dirichlet condition
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

#ifndef FEM_SYNTAX_SOLVEDIRICHLET
#define FEM_SYNTAX_SOLVEDIRICHLET

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "../../class/Expression.hpp"

class Dirichlet;

class SNsolveDirichlet : public SNunit {
public:

  // with default quadrature method
  SNsolveDirichlet( const char *name, Expression *ePtr, SNunit *sPtr)
    : SNunit("solveDirichlet",SN_SOLVEDIRICHLET) {

    varName      = name;
    dExprPtr     = ePtr;
    dBoundaryLst = (SNidentifierlist *)sPtr;

    dirichletPtr = 0;

    return;
  }

  void print(std::ostream &ost) {

    ost << "Dirichlet ";
    ost << varName << " = ";
    dExprPtr->print(ost);
    ost << " on ";
    dBoundaryLst->print(ost);
    ost << std::endl;

    return;
  }

  // CHECK
  int VariableDefinedCheck_Dirichlet( list <string> &);
  int GeometryCheck();

  // InfoGenerate
  Variable *GetDirichletVariablePtr(void);
  void AddVariablePtr_Dirichlet(Dirichlet *);
  void SetDataExprStr(Dirichlet *);
  void SetDataSimpleExprStr(Dirichlet *);
  int  GeometryCreate();

private:
  string             varName;
  Expression        *dExprPtr;
  SNidentifierlist  *dBoundaryLst;

  Dirichlet         *dirichletPtr;

};

#endif
