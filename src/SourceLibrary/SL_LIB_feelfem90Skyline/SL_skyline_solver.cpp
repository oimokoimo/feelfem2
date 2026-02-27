/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_skyline_solver.cpp
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
#include "SL_LIB_feelfem90Skyline.hpp"

static int come_yet_skyline_solver = 0;


void SL_LIB_feelfem90Skyline::SL_skyline_solver(int makeFlag)
{
  const char *sourceName;

  if(come_yet_skyline_solver == 1)  return;
  else                  come_yet_skyline_solver = 1;

  sourceName = GetSourceName("skyline_solver");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("module mod_skyline_solver");
  writeSource("contains");
  writeSource("  subroutine skyline_sol(vkgs,vkgd,vkgi,vfg,kld,neq,mp,ifac,isol,nsym,energ)");
  com();
  writeSource("    implicit none");
  com();
  writeSource("    double precision,dimension(:),pointer   :: vkgs,vkgd,vkgi");
  writeSource("    double precision,dimension(:),pointer   :: vfg");
  writeSource("    integer         ,dimension(:),pointer   :: kld");
  writeSource("    integer         ,intent(in)             :: neq,mp,ifac,isol,nsym");
  writeSource("    double precision                        :: energ");
  com();
  writeSource("    double precision                        :: scal");
  com();
  writeSource("    ! auto variables");
  writeSource("    integer                                 :: i,j");
  writeSource("    integer                                 :: ic");
  writeSource("    integer                                 :: j1,j2");
  writeSource("    integer                                 :: imin,imin1");
  writeSource("    integer                                 :: imax");
  writeSource("    integer                                 :: ik  ,ij");
  writeSource("    integer                                 :: jhk ,jhj ,lhk");
  writeSource("    integer                                 :: jhk1,jhj1,lhk1");
  writeSource("    integer                                 :: jbk ,jck");
  writeSource("    double precision                        :: cdiag,c1,c2");
  writeSource("    double precision                        :: zero");
  com();
  writeSource("    data   zero/0.0d0/");
  writeSource("    !------------------------------------------------------------");
  com();
  writeSource("    ik = 1");
  com();
  writeSource("    IF( VKGD(1).NE.ZERO ) GOTO 10");
  writeSource("    WRITE(*,2000 ) IK");
  writeSource("    STOP");
  com();
  writeSource("10  ENERG = ZERO");
  writeSource("    !");
  writeSource("    !");
  writeSource("    JHK = 1");
  writeSource("    DO 101 IK = 2, NEQ");
  com();
  writeSource("       JHK1 = KLD( IK + 1 )");
  com();
  writeSource("       LHK = JHK1 - JHK");
  writeSource("       LHK1 = LHK - 1");
  writeSource("       !");
  writeSource("       IMIN  = IK - LHK1");
  writeSource("       IMIN1 = IMIN - 1");
  writeSource("       !");
  writeSource("       IMAX = IK - 1");
  com();
  writeSource("       IF( LHK1.LT.0 ) GOTO 100");
  writeSource("       IF( IFAC.NE.1 ) GOTO 90");
  writeSource("       IF( NSYM.EQ.1 ) VKGI( JHK ) = VKGI( JHK ) / VKGD( IMIN1 )");
  writeSource("       IF( LHK1.EQ.0 ) GOTO 40");
  writeSource("       !");
  writeSource("       !");
  writeSource("       JCK = JHK + 1");
  writeSource("       JHJ = KLD( IMIN )");
  writeSource("       !");
  writeSource("       DO  IJ = IMIN,IMAX         ! do 30");
  writeSource("          JHJ1 = KLD( IJ + 1 )");
  com();
  writeSource("          IC = MIN0( JCK - JHK , JHJ1 - JHJ )");
  com();
  writeSource("          IF( ( IC.LE.0 ).AND.( NSYM.EQ.0 ) ) GOTO 20");
  writeSource("          C1 = ZERO");
  writeSource("          IF( IC.LE.0 ) GOTO 17");
  writeSource("          J1 = JHJ1 - IC");
  writeSource("          J2 = JCK - IC");
  writeSource("          IF( NSYM.EQ.1 ) GOTO 15");
  writeSource("          VKGS(JCK)=VKGS(JCK)-SCAL(VKGS(J1),VKGS(J2),IC)");
  writeSource("          GOTO 20");
  writeSource("15        VKGS(JCK)=VKGS(JCK)-SCAL(VKGI(J1),VKGS(J2),IC)");
  writeSource("          C1 = SCAL( VKGS( J1 ), VKGI( J2 ), IC )");
  writeSource("17        VKGI( JCK ) = (VKGI(JCK)-C1) / VKGD( IJ )");
  writeSource("20        JCK = JCK + 1");
  writeSource("          JHJ = JHJ1");
  writeSource("       end DO                 ! 30");
  writeSource("       !");
  writeSource("       !");
  writeSource("40     JCK = JHK");
  writeSource("       CDIAG = ZERO");
  writeSource("       DO  IJ = IMIN1,IMAX    ! 70");
  writeSource("          C1 = VKGS( JCK )");
  writeSource("          IF( NSYM.EQ.1 ) GOTO 50");
  writeSource("          C2 = C1 / VKGD( IJ )");
  writeSource("          VKGS( JCK ) = C2");
  writeSource("          GOTO 60");
  writeSource("          !");
  writeSource("50        C2 = VKGI( JCK )");
  writeSource("60        CDIAG = CDIAG + C1 * C2");
  writeSource("          JCK = JCK + 1");
  writeSource("       end do                                    ! 70");
  writeSource("       VKGD( IK ) = VKGD( IK ) - CDIAG");
  writeSource("       IF( VKGD( IK ) ) 90,80,90");
  writeSource("       !");
  writeSource("80     WRITE( *,2000 ) IK");
  writeSource("2000   FORMAT(' *** ERROR,ZERO PIVOT EQUATION ',I5 )");
  writeSource("       STOP");
  writeSource("       !");
  writeSource("       !");
  writeSource("90     IF( ISOL.NE.1 ) GOTO 100");
  writeSource("       IF( NSYM.NE.1 ) VFG( IK ) = VFG( IK ) - SCAL( VKGS( JHK ), &");
  writeSource("                                          VFG( IMIN1 ) , LHK )");
  com();
  writeSource("       IF( NSYM.EQ.1 ) VFG( IK ) = VFG( IK ) - SCAL( VKGI( JHK ), &");
  writeSource("                                          VFG( IMIN1 ),LHK )");
  writeSource("       !");
  writeSource("100    JHK = JHK1");
  writeSource("101 end do               ! 101( former 100)");
  writeSource("       !");
  writeSource("    IF( ISOL.NE.1 ) RETURN");
  writeSource("    !");
  writeSource("    IF( NSYM.EQ.1 ) GOTO 120");
  writeSource("    DO 110 IK = 1,NEQ");
  writeSource("       C1 = VKGD( IK )");
  writeSource("       C2 = VFG( IK ) / C1");
  writeSource("       VFG( IK ) = C2");
  writeSource("       ENERG = ENERG + C1 * C2 * C2");
  writeSource("110 end do");
  writeSource("       !");
  writeSource("       !");
  writeSource("120 IK = NEQ + 1");
  writeSource("    JHK1 = KLD( IK )");
  writeSource("       !");
  writeSource("130 IK = IK - 1");
  writeSource("    IF( NSYM.EQ.1 ) VFG( IK ) = VFG( IK ) / VKGD( IK )");
  writeSource("    IF( IK.EQ.1 ) RETURN");
  writeSource("    C1 = VFG( IK )");
  writeSource("    JHK = KLD( IK )");
  writeSource("    JBK = JHK1 - 1");
  writeSource("    IF( JHK.GT.JBK ) GOTO 150");
  writeSource("    IJ = IK - JBK + JHK - 1");
  writeSource("    DO JCK = JHK,JBK");
  writeSource("       VFG( IJ ) = VFG( IJ ) - VKGS( JCK ) * C1");
  writeSource("       IJ = IJ + 1");
  writeSource("    end do");
  writeSource("    !");
  writeSource("150 JHK1 = JHK");
  writeSource("    GOTO 130");
  writeSource("    !");
  writeSource("  end subroutine skyline_sol");
  writeSource("end module mod_skyline_solver");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
