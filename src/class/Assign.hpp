/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Assign.hpp
 *  Date     : 1999/11/17
 *  Modified : 1999/11/17
 *  
 *  Purpose  : Assignment class
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

#ifndef FEM_ASSIGN_CLASS
#define FEM_ASSIGN_CLASS

#include "Variable.hpp"
#include "orderedPtrList.hpp"

class ostream;

class SNassignment;
class GeomObj;
class EwiseQuadEcalInfo;
class ElementNodePattern;
class Quadrature;

class Assign {
public:
  Assign();
  ~Assign();

  void AddLeftVarPtr( Variable * );
  void SetGeometryType(int n) { geometryType = n; return; }
  void SetLeftVarAssignType(int n) { leftVarAssignType = n; }

  int GetAssignNo(void) { return assignNo; }

  // geometry
  int GetGeometryType(void) { return geometryType; }

  void SetNumberOfPlaces( int n) { numberOfPlaces = n; return;}
  int  GetNumberOfPlaces(void) { return numberOfPlaces; }
  void AddGeomObjPtr(GeomObj *);
  list <GeomObj *>&GetGeomObjPtrList(void) {
    return(geomObjPtrLst);
  }

  // variable to be assigned and right hand side expression
  int GetLeftVarAssignType(void) { return leftVarAssignType; }
  string &GetExprString() { return expr; }
  string &GetOriginalExprString() { return originalExpr; }

  void SetExpression(const char *e) {   // In EwiseQuad assignment
    expr = e; 
    return;
  }
  void SetOriginalExpression(const char *e) {
    originalExpr = e;
    return;
  }

  void UseX() { useX = 1; }
  void UseY() { useY = 1; }
  void UseZ() { useZ = 1; }

  void UseNX() { useNX = 1; }
  void UseNY() { useNY = 1; }
  void UseNZ() { useNZ = 1; }

  void UseDiff1st() { useDiff1st = 1; }
  void UseDiff2nd() { useDiff2nd = 1; }

  int IsUseX() { return useX; }
  int IsUseY() { return useY; }
  int IsUseZ() { return useZ; }

  int IsUseXVal() { return useXval; }
  int IsUseYVal() { return useYval; }
  int IsUseZVal() { return useZval; }

  int IsUseNX() { return useNX; }
  int IsUseNY() { return useNY; }
  int IsUseNZ() { return useNZ; }

  int IsUseDifferential1st() { return useDiff1st; }
  int IsUseDifferential2nd() { return useDiff2nd; }

  orderedPtrList <Variable *> &GetVarPtrList(void) {
    return varPtrLst;
  }
  Variable *GetLeftVarPtr(void) { return leftVarPtr; }


  // Ewise Quad  Quadrature pointer
  // and also for Integral
  void SetQuadraturePtr(Quadrature *);
  Quadrature *GetQuadraturePtr(void);

  // Ewise quadrature point assignment
  void EwiseQuadDiscretize(void);   //  in Assign directory
  EwiseQuadEcalInfo *GetEwQEcalInfoPtr(void) {
    return(ewqEcalInfoPtr);
  }

  Element *GetParametricElementPtr(void) {
    return(parametricElemPtr);
  }
  ElementNodePattern *GetElementNodePatternPtr(void)
  {
    return enpPtr;
  }

  int  GetNodesEwiseQuad(void); // = ElementNodePattern->GetNodes();

  int  GetNodesForParametric(void);    // used from ProgramModel class
  int *GetNodeInfoParametric(void);    //
  int  GetNodesForVariable(Variable *);
  int *GetNodeInfoVariable(Variable *);
  int  GetNodesForElement (Element  *);
  int *GetNodeInfoElement (Element  *);
				 
  int  HasCoroutine(void);
  void UseCoroutine(void);

  void AddUsedUserFuncSymbol( string &);
  list <string> &GetUsedUserFuncStrList(void) {
    return userFuncStrLst;
  }

  friend SNassignment;

  void print(ostream &);

private:

  // EwiseQuad (called from EwiseQuadDiscretize() )
  void EwiseQuadIG_TermConvert();     
  void EwiseQuadIG_ElementNodePattern();

  static int totalAssigns; // counter of assignment statements
  int assignNo;            // used as let subroutine name

  Variable *leftVarPtr;
  int leftVarAssignType;   // AS_VAR_TYPE ...

  int geometryType;        // ASSIGN_TYPE_NORMAL  (no information is needed.)
                           // ASSIGN_TYPE_ELEM    (element information needed)
                           // ASSIGN_TYPE_NSET    (node set information needed)
                           // ASSIGN_TYPE_NODE    (one node number is needed)
  int numberOfPlaces;
  list <GeomObj *>geomObjPtrLst;

  // right hand side information
  int useX,useXval;    // useX is used for argument making,
  int useY,useYval;    // while useXval means used in assignement formula,
  int useZ,useZval;    // used in EwiseQuad assignment

  int useNX;
  int useNY;
  int useNZ;

  int useDiff1st;
  int useDiff2nd;       // future....

  int coroutineFlag;    // coroutine 

  string expr;               // first set at SNassign_InfoGenerete, but
                             // EwiseQuad reuse this area (2002/09/30 detected)
  string originalExpr;

  // for code generation
  orderedPtrList <Variable *>varPtrLst;

  // for EwiseQuad
  Element            *parametricElemPtr;   // parametric transformation
  EwiseQuadEcalInfo  *ewqEcalInfoPtr;
  ElementNodePattern *enpPtr;

  Quadrature         *ewqQuadPtr;

  int           userFuncs;
  list <string> userFuncStrLst;

  //functional flags
  int           regionalIntegralFlag;
  int           boundaryIntegralFlag;

};

#endif
