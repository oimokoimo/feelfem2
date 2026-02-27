/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_sol.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
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
#include "SL_LIB_feelP2Skyline.hpp"

static int come_yet_sol = 0;


void SL_LIB_feelP2Skyline::SL_sol(int makeFlag)
{
  const char *sourceName;

  if(come_yet_sol == 1)  return;
  else                  come_yet_sol = 1;

  sourceName = GetSourceName("sol");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      SUBROUTINE SOL(VKGS,VKGD,VKGI,VFG,KLD,NEQ,MP,IFAC,ISOL,NSYM,ENERG)");
  writeSource("     $");
  writeSource("C***********************************************************");
  writeSource("C     SUBROUTINE SOL(VKGS,VKGD,VKGI,VFG,KLD,NEQ,MP,IFAC,ISOL,NSYM,ENERG)");
  com();
  writeSource("C                                               sol.f");
  com();
  writeSource("C     input      VKGS,VKGD,VKGI");
  writeSource("C                VFG");
  writeSource("C                KLD");
  writeSource("C                NEQ");
  writeSource("C                MP");
  writeSource("C                IFAC");
  writeSource("C                ISOL");
  writeSource("C                NSYM");
  writeSource("C     output     VKGS,VKGI,VKGD");
  writeSource("C                VFG");
  writeSource("C                ENERG");
  com();
  com();
  com();
  com();
  writeSource("C************************************************************");
  writeSource("      IMPLICIT REAL*8(A-H,O-Z)");
  writeSource("      DIMENSION VKGS(1),VKGD(1),VKGI(1),VFG(1),KLD(1)");
  writeSource("      DATA ZERO/0.0D0/");
  com();
  writeSource("      IK = 1");
  writeSource("      IF( VKGD(1).NE.ZERO ) GOTO 10");
  writeSource("      WRITE( MP,2000 ) IK");
  writeSource("      STOP");
  writeSource(" 10   ENERG = ZERO");
  com();
  writeSource("C---");
  com();
  writeSource("      JHK = 1");
  writeSource("      DO 100 IK = 2, NEQ");
  com();
  writeSource("         JHK1 = KLD( IK + 1 )");
  com();
  writeSource("         LHK = JHK1 - JHK");
  writeSource("         LHK1 = LHK - 1");
  com();
  writeSource("         IMIN  = IK - LHK1");
  writeSource("         IMIN1 = IMIN - 1");
  com();
  writeSource("         IMAX = IK - 1");
  com();
  writeSource("         IF( LHK1.LT.0 ) GOTO 100");
  writeSource("         IF( IFAC.NE.1 ) GOTO 90");
  writeSource("         IF( NSYM.EQ.1 ) VKGI( JHK ) = VKGI( JHK ) / VKGD( IMIN1 )");
  writeSource("         IF( LHK1.EQ.0 ) GOTO 40");
  com();
  com();
  writeSource("         JCK = JHK + 1");
  writeSource("         JHJ = KLD( IMIN )");
  com();
  writeSource("         DO 30 IJ = IMIN,IMAX");
  writeSource("            JHJ1 = KLD( IJ + 1 )");
  com();
  writeSource("            IC = MIN0( JCK - JHK , JHJ1 - JHJ )");
  com();
  writeSource("            IF( ( IC.LE.0 ).AND.( NSYM.EQ.0 ) ) GOTO 20");
  writeSource("            C1 = ZERO");
  writeSource("            IF( IC.LE.0 ) GOTO 17");
  writeSource("            J1 = JHJ1 - IC");
  writeSource("            J2 = JCK - IC");
  writeSource("            IF( NSYM.EQ.1 ) GOTO 15");
  writeSource("            VKGS(JCK)=VKGS(JCK)-SCAL(VKGS(J1),VKGS(J2),IC)");
  writeSource("            GOTO 20");
  writeSource(" 15         VKGS(JCK)=VKGS(JCK)-SCAL(VKGI(J1),VKGS(J2),IC)");
  writeSource("            C1 = SCAL( VKGS( J1 ), VKGI( J2 ), IC )");
  writeSource(" 17         VKGI( JCK ) = (VKGI(JCK)-C1) / VKGD( IJ )");
  writeSource(" 20         JCK = JCK + 1");
  writeSource(" 30      JHJ = JHJ1");
  com();
  com();
  writeSource(" 40      JCK = JHK");
  writeSource("         CDIAG = ZERO");
  writeSource("         DO 70 IJ = IMIN1,IMAX");
  writeSource("            C1 = VKGS( JCK )");
  writeSource("            IF( NSYM.EQ.1 ) GOTO 50");
  writeSource("            C2 = C1 / VKGD( IJ )");
  writeSource("            VKGS( JCK ) = C2");
  writeSource("            GOTO 60");
  com();
  writeSource(" 50         C2 = VKGI( JCK )");
  writeSource(" 60         CDIAG = CDIAG + C1 * C2");
  writeSource(" 70      JCK = JCK + 1");
  writeSource("         VKGD( IK ) = VKGD( IK ) - CDIAG");
  writeSource("         IF( VKGD( IK ) ) 90,80,90");
  com();
  writeSource(" 80      WRITE( MP,2000 ) IK");
  writeSource(" 2000    FORMAT(' *** ERROR,ZERO PIVOT EQUATION ',I5 )");
  writeSource("         STOP");
  com();
  com();
  writeSource(" 90      IF( ISOL.NE.1 ) GOTO 100");
  writeSource("         IF( NSYM.NE.1 ) VFG( IK ) = VFG( IK ) - SCAL( VKGS( JHK ),");
  writeSource("     $                                  VFG( IMIN1 ) , LHK )");
  writeSource("         IF( NSYM.EQ.1 ) VFG( IK ) = VFG( IK ) - SCAL( VKGI( JHK ),");
  writeSource("     $                                  VFG( IMIN1 ),LHK )");
  com();
  writeSource(" 100  JHK = JHK1");
  com();
  writeSource("      IF( ISOL.NE.1 ) RETURN");
  com();
  writeSource("      IF( NSYM.EQ.1 ) GOTO 120");
  writeSource("      DO 110 IK = 1,NEQ");
  writeSource("         C1 = VKGD( IK )");
  writeSource("         C2 = VFG( IK ) / C1");
  writeSource("         VFG( IK ) = C2");
  writeSource("         ENERG = ENERG + C1 * C2 * C2");
  writeSource(" 110  CONTINUE");
  com();
  com();
  writeSource(" 120  IK = NEQ + 1");
  writeSource("      JHK1 = KLD( IK )");
  com();
  writeSource(" 130  IK = IK - 1");
  writeSource("      IF( NSYM.EQ.1 ) VFG( IK ) = VFG( IK ) / VKGD( IK )");
  writeSource("      IF( IK.EQ.1 ) RETURN");
  writeSource("      C1 = VFG( IK )");
  writeSource("      JHK = KLD( IK )");
  writeSource("      JBK = JHK1 - 1");
  writeSource("      IF( JHK.GT.JBK ) GOTO 150");
  writeSource("      IJ = IK - JBK + JHK - 1");
  writeSource("      DO 140 JCK = JHK,JBK");
  writeSource("         VFG( IJ ) = VFG( IJ ) - VKGS( JCK ) * C1");
  writeSource(" 140     IJ = IJ + 1");
  com();
  writeSource(" 150  JHK1 = JHK");
  writeSource("      GOTO 130");
  com();
  writeSource("      END");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
