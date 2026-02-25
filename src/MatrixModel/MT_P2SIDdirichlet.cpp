/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2SIDdirichlet.cpp
 *  Date     : 2000/01/12
 *  Modified : 2000/01/12
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : FEEL P2 program model/CRS storage dirichlet condition
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

#include "MT_P2SID.hpp"
#include "Dirichlet.hpp"

void MT_P2SID::DoDirichletRoutineHeaderMT(Dirichlet *dPtr)
{
  DoDirichletArgumentSequence( dPtr );
  SourceStarters();

  //  fortImplicit();    // f77 version in SourceStarters();
  com();

  DoDirichletArgumentVariableDefinitionsPM(dPtr);
  com();
  writeMatrixDeclarations();
  com();

  return;
}

void MT_P2SID::DoDirichletArgumentSequence(Dirichlet *dPtr)
{
  pushSource("      subroutine ");
  pushDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo());
  pushSource("(x,y,");             // dependent on class
  flushSource();

  pushSource("     $ ");
  pushMatrixArgumentsCalled();
  pushSource(",IPD,inset,nd");         // only here is dependent on class
  flushSource();

  pushSource("     $ ");
  orderedPtrList   <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr; ++itr ){
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }
  pushSource(")");
  flushSource();

  return;
}

void MT_P2SID::doDirichletAutoVariableDefinitionsMT(Dirichlet *dPtr)
{
  // matrix related auto variables
  
  // do nothing because of fortran 77

  return;
}

void MT_P2SID::DoDirichletApplyMatrixMT(Dirichlet *dPtr)
{
  comment();
  writeSource("      do 100 i=1,nd");
  com();
  writeSource("       ip  = inset(1,i)");
  writeSource("       ieq = IPD(ip)+inset(2,i)");

  pushSource( "       u   = ");
  pushSource( dPtr->testGetTestExpression() );
  flushSource();
  com();
  
  writeSource("***********");
  writeSource("* row ieq *");
  writeSource("***********");
  writeSource("       do 110 j=1,mj");
  writeSource("        jeq = ja(ieq,j)");
  writeSource("        if(jeq .eq. ieq) then");
  writeSource("         a(ieq,j) = 1.0d0");
  writeSource("        else");
  writeSource("         a(ieq,j) = 0.0d0");
  writeSource("        endif");
  writeSource(" 110   continue");
  writeSource("       b(ieq) = u");

  writeSource("**************");
  writeSource("* column ieq *");
  writeSource("**************");
  writeSource("       do 120 j=1,mj");
  writeSource("        jeq = ja(ieq,j)");
  writeSource("        if(ieq .eq. jeq) goto 120");
  writeSource("        if(  0 .eq. jeq) goto 120");
  
  writeSource("* --------");
  writeSource("* row jeq ");
  writeSource("* --------");
  writeSource("        do 130 k=1,mj");
  writeSource("         if(ieq .eq. ja(jeq,k)) goto 140");
  writeSource(" 130    continue");
  writeSource("* err");
  writeSource("        stop 'cannot find (jeq,ieq)'");
  writeSource("* err");
  writeSource(" 140    continue");
  writeSource("        b(jeq)  =b(jeq)-a(jeq,k)*u");
  writeSource("        a(jeq,k) =0.0d0");
  writeSource("*");
  writeSource(" 120   continue");    
  writeSource("*");

  writeSource(" 100  continue");
  comment();

  return;
}
