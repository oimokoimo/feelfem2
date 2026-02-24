/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : aistpcp90_mainScheme.cpp
 *  Date     : 2002/06/28
 *  Modified : 2002/09/30
 *  
 *  Purpose  : Scheme part of main routine for aistpcp90 program model
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
 *  
 */

#include "PM_aistpcp90.hpp"
#include "Label.hpp"
#include "IfBlock.hpp"

#include "TermConvert.hpp"

// Main pointer is not used...
void PM_aistpcp90::DoMainScheme_solve(Main *mPtr, Solve *solvePtr)
{
  pushSource("call ");
  pushSource( GetSolveRoutineName( solvePtr->GetSolveNo() ));
  pushSource("(myrank,nprocs,iedom,                         &");
  flushSource();

  pushSource("            npmax,");
  pushCoordinateSource();
  pushSource(",firstEdatPtr,firstNsetPtr,solveLst &");
  flushSource();

  pushSource("           ");
  pushVariableListInMain( solvePtr->VariablePtrLst());
  pushSource(")");
  flushSource();

  return;
}

void PM_aistpcp90::DoMainScheme_label(Main *mPtr, Label *labelPtr)
{
  com();
  pushSource("! label ");
  pushSource(labelPtr->GetName());
  pushSource(":");
  flushSource();

  pushSource(" ");
  pushSourceInt(2000+labelPtr->GetLabelNo());
  pushSource("  continue");
  flushSource();

  com();

  return;
}

void PM_aistpcp90::DoMainScheme_if(Main *mPtr,IfBlock *ifblockPtr)
{
  TermConvert tc;
  listIterator <Variable *>itrV(ifblockPtr->GetVarPtrList());
  for(itrV.init(); !itrV; ++itrV){

    char bfrom[VARIABLE_TERMCONVERT_BUFSIZ];
    char bto  [VARIABLE_TERMCONVERT_BUFSIZ];

    switch(itrV()->GetType()) {
    case VAR_INT:
    case VAR_DOUBLE:
    case VAR_CONST:
      sprintf(bfrom,"%s%c",itrV()->GetName(),'\0');
      sprintf(bto  ,"sc_%s%c",itrV()->GetName(),'\0');      
      tc.storeConvertPair( bfrom, bto );
      break;

    case VAR_EWISE:
    case VAR_EWISE_A:
    case VAR_FEM:
    case VAR_VFEM:
    case VAR_MATERIAL:
      std::cerr << "Illegal var code\n";
      assert(1==0);

    default:
      std::cerr << "(default)Illegal var code\n";
      assert(1==0);
    }
  }
  
  string exprF90Str = tc.convertExpressionString(ifblockPtr->GetExprString());

  com();
  pushSource("if(");
  pushSource(exprF90Str);
  pushSource(") goto ");
  
  Label *labelPtr = ifblockPtr->GetLabelPtr();
  pushSourceInt(2000+labelPtr->GetLabelNo());
  flushSource();

  com();
}
