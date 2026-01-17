/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2CRSdirichlet.cpp
 *  Date     : 2000/01/12
 *  Modified : 2000/01/12
 *  Modified : 2002/02/02 orderedPtrList
 *  
 *  Purpose  : FEEL P2 program model/CRS storage dirichlet condition
 *  
 */

#include "MT_P2CRS.hpp"
#include "Dirichlet.hpp"

void MT_P2CRS::DoDirichletRoutineHeaderMT(Dirichlet *dPtr)
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

void MT_P2CRS::DoDirichletArgumentSequence(Dirichlet *dPtr)
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

  orderedPtrList  <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
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

void MT_P2CRS::doDirichletAutoVariableDefinitionsMT(Dirichlet *dPtr)
{
  // matrix related auto variables
  
  // do nothing for fortran 77

  return;
}

void MT_P2CRS::DoDirichletApplyMatrixMT(Dirichlet *dPtr)
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
  writeSource("       iptf = iptrcol(ieq)");
  writeSource("       iptt = iptrcol(ieq+1)-1");
  writeSource("       do 110 j=iptf,iptt");
  writeSource("        jeq = indrow(j)");
  writeSource("        if(jeq .eq. ieq) then");
  writeSource("         valmat(j) = 1.0d0");
  writeSource("        else");
  writeSource("         valmat(j) = 0.0d0");
  writeSource("        endif");
  writeSource(" 110   continue");
  writeSource("       vfg(ieq) = u");

  writeSource("**************");
  writeSource("* column ieq *");
  writeSource("**************");
  writeSource("       do 120 j=iptf,iptt");
  writeSource("        jeq = indrow(j)");
  writeSource("        if(ieq .eq. jeq) goto 120");
  
  writeSource("* --------");
  writeSource("* row jeq ");
  writeSource("* --------");
  writeSource("        iptf2 = iptrcol(jeq)    ");
  writeSource("        iptt2 = iptrcol(jeq+1)-1");
  writeSource("        do 130 k=iptf2,iptt2");
  writeSource("         if(ieq .eq. indrow(k)) goto 140");
  writeSource(" 130    continue");
  writeSource("* err");
  writeSource("        stop 'cannot find (jeq,ieq)'");
  writeSource("* err");
  writeSource(" 140    continue");
  writeSource("        vfg(jeq)  =vfg(jeq)-valmat(k)*u");
  writeSource("        valmat(k) =0.0d0");
  writeSource("*");
  writeSource(" 120   continue");    
  writeSource("*");

  writeSource(" 100  continue");
  comment();

  return;
}


