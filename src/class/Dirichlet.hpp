/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Dirichlet.hpp
 *  Date     : 1999/11/24
 *  Modified : 1999/11/30
 *  
 *  Purpose  : Dirichlet Condition class
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

#ifndef FEM_CLASS_DIRICHLET
#define FEM_CLASS_DIRICHLET

#include "string.hpp"
#include "orderedPtrList.hpp"
#include "Variable.hpp"

class Expression;
class DirichletGeom;

class Dirichlet {
public:
  Dirichlet();
  ~Dirichlet();

  void operator= (const Dirichlet &);

  void AddDirichletGeomPtr(DirichletGeom *);
  int  GetNumberOfDirichletGeoms(void);
  DirichletGeom *GetIthDirichletGeomPtr(int);

  int  GetSolveNo(void) {return solveNo;}
  int  GetDcondNo(void) { return dcondNo; }
  int  GetNsetno(void);

  void SetNsetno( int );
  void SetSolveNo( int );
  void SetDcondNo( int );
  void SetDirichletVarPtr( Variable * );

  Variable   *GetDcondVariablePtr(void) { return dirichletVarPtr; }

  void SetDataExprStr( char *);
  void SetDataSimpleExprStr( char *);
  const char *GetExprStr() { return dDataExpr; }
  const char *GetSimpleExprStr() { return dDataSimpleExpr; } // for Gid.cnd

  int  GetFirstDirichletGeomNo_DOTMP(void);
    

  // set series 
  void testSetNsetno( int );
  void testSetSolveNo(int no) {solveNo = no; return; }
  void testSetDcondNo( int no) { dcondNo = no; return;}

  void  testSetTestExpression ( const char * );
  const char *testGetTestExpression ( void   );
  
  orderedPtrList <Variable *> &GetVariablePtrLst(void) {
    return(varPtrLst);
  }

  void AddVariablePtr (Variable *);
  
private:
  Variable       *dirichletVarPtr;
  orderedPtrList <Variable *> varPtrLst;

  string      dDataExpr;
  string      dDataSimpleExpr;
  string      testExpression;
  
  list <DirichletGeom *>dirichletGeomPtrLst;
  int         dGeoms ;
  
  int         solveNo;
  int         dcondNo;
  int         nsetno;              // node set number for this dirichlet data

};

#endif
