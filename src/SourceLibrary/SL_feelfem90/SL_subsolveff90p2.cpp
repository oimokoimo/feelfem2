/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_subsolveff90p2.cpp
 *  Date     : 2002/09/12 17:25
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
#include "SL_feelfem90.hpp"

static int come_yet_subsolveff90p2 = 0;


void SL_feelfem90::SL_subsolveff90p2(int makeFlag)
{
  const char *sourceName;

  if(come_yet_subsolveff90p2 == 1)  return;
  else                  come_yet_subsolveff90p2 = 1;

  sourceName = GetSourceName("subsolveff90p2");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("module subsolveff90p2");
  com();
  writeSource("contains");
  com();
  writeSource("subroutine makeipfp2(nenfre,maxElementFreedom,neg, &");
  writeSource("                     ielem,nelem,np,npmax,ipf      )");
  writeSource("!--------------");
  writeSource("! construct ipf");
  writeSource("!--------------");
  writeSource("use numeric");
  com();
  writeSource("implicit none");
  com();
  writeSource("integer                                  :: maxElementFreedom,neg");
  writeSource("integer                                  :: nelem,np,npmax");
  com();
  writeSource("integer,dimension(maxElementFreedom,neg) :: nenfre");
  writeSource("integer,dimension(:,:),pointer           :: ielem");
  writeSource("integer,dimension(npmax)                 :: ipf          ! initialized here");
  com();
  writeSource("! auto variables");
  writeSource("integer                                  :: i,j");
  com();
  writeSource("!------------------------------------------------------");
  writeSource("do i=1,npmax");
  writeSource("  ipf(i) = 0");
  writeSource("end do");
  com();
  writeSource("do i=1,nelem");
  com();
  writeSource(" do j=1,np");
  com();
  writeSource("   ipf(ielem(j,i)) = nenfre(j,0001)   ! P2 restriction");
  com();
  writeSource("  end do");
  com();
  writeSource("end do");
  com();
  writeSource("end subroutine makeipfp2");
  com();
  writeSource("subroutine makeipdp2(ipf,ipd,npmax,neq)");
  writeSource("use abortmodule");
  writeSource("implicit none");
  com();
  writeSource("integer                    :: npmax");
  writeSource("integer                    :: neq");
  writeSource("integer ,dimension(npmax)  :: ipf,ipd");
  com();
  writeSource("! auto variables");
  com();
  writeSource("integer                    :: i");
  writeSource("integer                    :: istart");
  writeSource("integer                    :: nowfree");
  com();
  writeSource("!-----------------------------------------------------");
  com();
  writeSource("! initialization");
  writeSource("neq = 0");
  writeSource("do i=1,npmax");
  writeSource("   ipd(i) = 0");
  writeSource("end do");
  com();
  com();
  writeSource("! find first freedom");
  com();
  writeSource("istart = 0");
  writeSource("do i=1,npmax");
  writeSource("  if(ipf(i) .ne. 0) then");
  writeSource("    istart = i");
  writeSource("    exit");
  writeSource("  endif");
  writeSource("end do");
  com();
  writeSource("! cannot find the first degree of freedom");
  writeSource("if(istart .eq. 0) then");
  writeSource("  call abortexit('Cannot find first degree of freedom')");
  writeSource("endif");
  com();
  com();
  writeSource("! construct IPD array");
  com();
  writeSource("nowfree     = ipf(istart)");
  writeSource("ipd(istart) = 1");
  com();
  writeSource("do i=istart+1,npmax");
  writeSource("  if(ipf(i) .ne. 0) then");
  writeSource("    ipd(i) = nowfree + 1");
  writeSource("    nowfree = nowfree + ipf(i)");
  writeSource("  endif");
  writeSource("end do");
  com();
  writeSource("neq = nowfree");
  com();
  writeSource("end subroutine makeipdp2");
  com();
  writeSource("subroutine nc_connectp2(npmax,ielem,nelem,np, &");
  writeSource("                        ncmax                 )");
  writeSource("use numeric");
  com();
  writeSource("implicit none");
  com();
  writeSource("integer,intent(in)               :: npmax,nelem,np");
  writeSource("integer,dimension(:,:),pointer   :: ielem");
  writeSource("integer,intent(out)              :: ncmax");
  com();
  writeSource("! auto variables");
  com();
  writeSource("integer                          :: i,j");
  writeSource("integer,dimension(:),pointer     :: nc");
  com();
  writeSource("!----------------");
  writeSource("! nc preparation");
  writeSource("!----------------");
  writeSource("allocate(nc(npmax))");
  writeSource("do i=1,npmax");
  writeSource(" nc(i) = 0");
  writeSource("end do");
  com();
  writeSource("!--------------------------");
  writeSource("! count element connections");
  writeSource("!--------------------------");
  writeSource("do i=1,nelem");
  writeSource("  do j=1,np");
  writeSource("  nc(ielem(j,i)) = nc(ielem(j,i)) + 1");
  writeSource("  end do");
  writeSource("end do");
  com();
  writeSource("!--------------------------");
  writeSource("! calculate ncmax");
  writeSource("!--------------------------");
  writeSource("ncmax = nc(1)");
  writeSource("do i=2,npmax");
  writeSource("  if(ncmax < nc(i) ) ncmax = nc(i)");
  writeSource("end do");
  com();
  writeSource("deallocate(nc)");
  com();
  writeSource("end subroutine nc_connectp2");
  com();
  writeSource("end module subsolveff90p2");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
