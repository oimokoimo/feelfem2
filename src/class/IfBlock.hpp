/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : IfBlock.hpp
 *  Date     : 2002/07/18
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

#ifndef FEM_CLASS_IFBLOCK
#define FEM_CLASS_IFBLOCK

#include "feeldef.hpp"

#include "Variable.hpp"
#include "orderedPtrList.hpp"
#include "Expression.hpp"

class SNif;
class Label;

class IfBlock {
public:
  IfBlock(const char *);
  ~IfBlock();

  friend class SNif;

  const char *GetExprString() {
    return( (const char *)expr);
  }

  Label *GetLabelPtr(void);

  orderedPtrList <Variable *>&GetVarPtrList() {
    return( varPtrLst );
  }

private:
  
  orderedPtrList <Variable *> varPtrLst;
  string gotoLabel;
  string expr;

};
  
#endif
