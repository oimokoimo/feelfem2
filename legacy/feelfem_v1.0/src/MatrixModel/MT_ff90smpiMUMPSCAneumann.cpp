/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90smpiMUMPSCAneumann.cpp
 *  Date     : 2003/01/01  (Copied from MT_ff90AMGCRS)
 *  Modified : 2003/01/04
 *  
 *  Purpose  : feelfem90smpi program model/MUMPS CA storage neumann condition
 *            (originally derived from PAMG data model)
 *  
 */

#include "MT_ff90smpiMUMPSCA.hpp"
#include "Neumann.hpp"

void MT_ff90smpiMUMPSCA::DoNeumannRoutineHeaderMT(Neumann *nPtr)
{
  DoNeumannArgumentSequenceMT( nPtr );
  SourceStarters();

  F90useNeumannPM();

  fortImplicit();
  com();

  DoNeumannArgumentVariableDefinitionsPM(nPtr);
  com();

  doNeumannVariableDefinitionsMT();
  com();
  
  return;
}


void MT_ff90smpiMUMPSCA::DoNeumannArgumentSequenceMT(Neumann *nPtr)
{
  pushSource("module mod_");
  pushNeumannRoutineName(nPtr->GetSolveNo(),nPtr->GetNcondNo());
  flushSource();
  
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushNeumannRoutineName(nPtr->GetSolveNo(),nPtr->GetNcondNo());
  pushSource("(   nbedatno,firstEdatPtr, &");
  flushSource();

  pushSource("   npmax,");
  pushCoordinateSource();
  pushSource(",ipf,ipd &");
  flushSource();
  
  pushSource("   ");

  /* Additional variables */
  orderedPtrList <Variable *>varPtrLst = nPtr->GetVariablePtrLst();
  //  listIterator <Variable *>itr(varPtrLst);

  /* Domain variables */
  pushVariableListInCalled( varPtrLst );

  pushSource(",");
  pushMatrixArgumentsCalled();
  pushSource(")");

  flushSource();

  return;
}

void MT_ff90smpiMUMPSCA::DoNeumannApplyMatrixMT(Neumann *nPtr)
{

  /* Prepare ikp (Prepared in PM dependent section)*/
  writeSource("  do j=1,NDF");

  writeSource("    nd     = bielem(ienp(j),i)");
  writeSource("    ikp(j) = ipd(nd)+iedp(j)");
  writeSource("  end do");
  com();

  if(nPtr->GetMatNonZero() != 0) {
    writeSource("!-----------------");
    writeSource("! Loop for ba(*,*)");
    writeSource("!-----------------");
    writeSource("  do j=1,NDF");

    writeSource("   ip   = ikp(j)");
    writeSource("   iptf = iptrcol(ip)");
    writeSource("   iptt = iptrcol(ip+1)-1");
    com();

    writeSource("   do k=1,NDF");
    writeSource("     jp = ikp(k)");
    com();

    writeSource("     do L=iptf,iptt");
    writeSource("       if(mumps_par%JCN(L) .EQ. jp) goto 608");
    writeSource("     end do                               ! do L=iptf,iptt");
    com();

    writeSource("!--- err");
    writeSource("        write(*,*) '???(ncond 607)',ip,jp");
    writeSource("        call abortexit('ncond error')");
    writeSource("!--- err");
    com();

    writeSource(" 608 continue");
    writeSource("     mumps_par%A(L)=mumps_par%A(L)+ba(j,k)");
    com();

    writeSource("   end do                                 ! do k=1,NDF"); 
    writeSource("  end do                                  ! do j=1,NDF");
  }
  com();
  
  writeSource("  do j=1,NDF");
  writeSource("    mumps_par%RHS(ikp(j))=mumps_par%RHS(ikp(j))+bb(j)");
  writeSource("  end do");
  comment();

  return;
}

// neumann routine matrix dependent parts
void MT_ff90smpiMUMPSCA::doNeumannVariableDefinitionsMT(void)
{
  writeMatrixDeclarations();
  writeInteger4sc("iptf,iptt");
  return;
}
