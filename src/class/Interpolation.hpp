/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Interpolation.hpp
 *  Date     : 2002/03/03
 *  Modified : 
 *  
 *  Purpose  :
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

#ifndef FEM_CLASS_INTERPOLATION
#define FEM_CLASS_INTERPOLATION

#include "Node.hpp"
#include "string.hpp"

class ostream;

class Interpolation {

public:
  Interpolation();
  ~Interpolation();

  void SetType(int); // INTERP_TYPE_NODAL,
                     // INTERP_TYPE_DX
                     // INTERP_TYPE_DY
                     // INTERP_TYPE_DZ
                     // INTERP_TYPE_DN
                     // INTERP_TYPE_DTX  ...
  int  GetType(void) {
    return (type); 
  }

  void SetExprStr(const  char *);
  void SetNodePtr( Node *);
  void SetBoundaryNodePtr( Node *);

  Node *GetNodePtr(void);        
  Node *GetBoundaryNodePtr(void);  // for boundary
  
  string &GetExprString() { return exprStr; }

  // following function checks type and Node *
  friend int operator < (const Interpolation &left,const Interpolation &right);
  friend int operator ==(const Interpolation &left,const Interpolation &right);


  // generate boundary element for neumann type conditions
  // return null if corresponding interpolation has no relationship in
  // boundary reference face
  Interpolation *GetBoundaryInterp_tri(void);   
  Interpolation *GetBoundaryInterp_rect(void);
  Interpolation *GetBoundaryInterp_tetra(void);
  Interpolation *GetBoundaryInterp_cube(void);

  void print(std::ostream &ost);

private:
  int   type;        // INTERP_TYPE_NODAL,
                     // INTERP_TYPE_DX
                     // INTERP_TYPE_DY
                     // INTERP_TYPE_DZ
                     // INTERP_TYPE_DN
                     // INTERP_TYPE_DTX  ...
  Node   *nodePtr;
  Node   *boundaryNodePtr;
  string  exprStr;

};


#endif

