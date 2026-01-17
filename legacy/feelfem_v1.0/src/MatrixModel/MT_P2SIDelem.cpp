/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2SIDelem.cpp
 *  Date     : 2000/11/23
 *  Modified : 2000/11/23
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : Element assembly routine for model P2/SID
 *  
 */
#include "MT_P2SID.hpp"


void MT_P2SID::DoElemRoutineHeaderMT(SolveElement *sePtr)
{
  doElemArgumentSequenceMT(sePtr);
  doElemStarters();                // just call SourceStarters();

  doElemDeclareArgumentVariablesPM( sePtr );
  doElemVariableDefinitionsMT();                //

}

void MT_P2SID::doElemArgumentSequenceMT(SolveElement *sePtr)
{
  pushSource("      subroutine ");
  pushElemRoutineName(sePtr->GetSolveNo(),sePtr->GetElemNo());
  pushSource("(x,y,ielem,matno,nelem,np,");
  flushSource();

  pushSource("     $ ");
  pushMatrixArgumentsCalled();
  pushSource(",IPD");
  flushSource();
  
  pushSource("     $     ");
  orderedPtrList   <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }
  pushSource(")");
  flushSource();

  return;
}

void MT_P2SID::DoElemAssembleMatrix(int flag)
{

  writeSource("      do 300 j=1,NDF");
  writeSource("        jp   = ikp(j)");
  writeSource("        do 400 k=1,NDF");
  writeSource("          kp=ikp(k)");
  writeSource("          do 500 L=1,mj");
  writeSource("            if(ja(jp,L) .EQ. kp) goto 505");
  writeSource(" 500      continue");
  writeSource("*--- err         ");
  writeSource("          write(*,*) 'cannot find'    ");
  writeSource("          stop 'elem'");
  writeSource("*--- err");
  writeSource(" 505      continue         ");
  writeSource("          a(jp,L) = a(jp,L)+ea(j,k)");
  writeSource(" 400    continue");
  writeSource(" 300  continue    ");
  comment();

  writeSource("      do 600 j=1,NDF");
  writeSource("        b(ikp(j))=b(ikp(j))+eb(j)");
  writeSource(" 600  continue");
  comment();

  return;
}



