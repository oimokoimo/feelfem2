/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : IntegrandSet.hpp
 *  Date     : 2002/02/08
 *  Modified : 
 *  
 *  Purpose  : Integrand set class
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

#ifndef FEM_CLASS_WEAKFORMULATION
#define FEM_CLASS_WEAKFORMULATION

#include <iostream>

#include "list.hpp"
#include "string.hpp"

class Quadrature;
class Variable  ;

class TermConvert;

class IntegrandSet {

public:
  IntegrandSet();
  ~IntegrandSet();

  void SetEquations( int n );
  void SetQuadraturePtr( Quadrature *);
  void SetIntegrandStr( string &);

  void SetUseX(void);   // called from Expression_WEAK.cpp
  void SetUseY(void);
  void SetUseZ(void);

  int  GetUseX(void);
  int  GetUseY(void);
  int  GetUseZ(void);
              
  Quadrature *GetQuadraturePtr(void);

  void AddVariablePtr( Variable *);  // with uniq functionality

  void print(std::ostream &ost);

  friend class GalerkinMethod;        // GalerkinMethod::Make_ElementInfo
  friend class BoundaryGalerkinMethod;

  //  list <Variable *>&GetVarPtrLst(void) {
  //    return (varPtrLst);
  //  }

protected:
  int equations;
  Quadrature *quadPtr;

  list <string> integrandLst;

  list <Variable *>varPtrLst;
  list <string    >functionNameLst;
  int   useX;
  int   useY;
  int   useZ;

};


class BoundaryIntegrandSet : public IntegrandSet 
{
public:
  
  BoundaryIntegrandSet();
  ~BoundaryIntegrandSet();
  
  void SetUseNX(void);   // called from Expression_WEAK.cpp
  void SetUseNY(void);
  void SetUseNZ(void);

  int  GetUseNX(void);
  int  GetUseNY(void);
  int  GetUseNZ(void);

  BoundaryIntegrandSet *GetNewByTC(TermConvert &);

private:
  int useNX;
  int useNY;
  int useNZ;

};

#endif
