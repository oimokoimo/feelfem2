/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_AMGCRS.cpp
 *  Date     : 2003/01/05 01:06
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
#include "SL_MT_ff90AMGCRS.hpp"

static int come_yet_AMGCRS = 0;


void SL_MT_ff90AMGCRS::SL_AMGCRS(int makeFlag)
{
  const char *sourceName;

  if(come_yet_AMGCRS == 1)  return;
  else                  come_yet_AMGCRS = 1;

  sourceName = GetSourceName("AMGCRS");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("module AMGCRS");
  com();
  com();
  writeSource("! AMG/CRS array for a single processor");
  com();
  writeSource("!  ================================");
  writeSource("! the difference from a general CRS");
  writeSource("!  ================================");
  writeSource("!  THE FIRST ENTRY IS DIAGONAL!!!!");
  writeSource("!  ================================");
  writeSource("!  ================================");
  com();
  writeSource("contains");
  com();
  com();
  writeSource("subroutine mkAMGCRSindex( neq,                          &");
  writeSource("                          ndfmax,ncon,                  &");
  writeSource("                          ipf,ipd,npmax,                &");
  writeSource("                          ielem,nelem,np,               &");
  writeSource("                          iptrcol,indrow,ncof           )");
  com();
  writeSource("! ---");
  writeSource("! construct AMG/CRS matrix index");
  com();
  com();
  com();
  writeSource("use numeric");
  writeSource("implicit none");
  com();
  writeSource("integer, intent(in)          :: neq            ! number of freedom");
  writeSource("integer, intent(in)          :: ndfmax         ! Maximum freedom in one element");
  writeSource("integer, intent(in)          :: ncon           ! Maximum relating freedom to");
  writeSource("                                               ! one node");
  com();
  writeSource("integer, intent(in)                    :: npmax");
  writeSource("integer, intent(in),dimension(npmax)   :: ipf,ipd");
  com();
  writeSource("integer, intent(in)                    :: nelem,np");
  writeSource("integer, dimension(:,:)                :: ielem");
  com();
  writeSource("integer, dimension(:),pointer          :: iptrcol,indrow   ! allocate here");
  writeSource("integer                                :: ncof,nhalo");
  com();
  writeSource("! auto variables");
  writeSource("integer                         :: i, j, k,l");
  writeSource("integer                         :: nj,nk");
  writeSource("integer                         :: iptr,nd   ! counter,and node number");
  writeSource("integer,dimension(:,:),pointer  :: ic        ! allocate(ncon,neq)");
  writeSource("                                             ! column index array(for indrow)");
  com();
  writeSource("integer,dimension(:),pointer    :: ip        ! allocate(neq)");
  writeSource("                                             ! row index array(for iptrcol)");
  writeSource("                                             ! it does not include the first");
  writeSource("                                             ! diagonal element, so it is not");
  writeSource("                                             ! the same of pmkCRSindex's ip");
  writeSource("                                             ! former ip(*)-1 = this ip(*)");
  com();
  writeSource("integer,dimension(ndfmax)       :: ipt       ! equation number list for one");
  writeSource("                                             ! element");
  com();
  writeSource("!======================================================================");
  writeSource("! allocate ip(neq),ic(ncon,neq)");
  com();
  writeSource("allocate( ip(neq) )");
  writeSource("allocate( ic(ncon,neq) )     ! Huge array");
  com();
  writeSource("do i=1,neq");
  writeSource(" ip(i)   = 1                 ! AMGCRS (first element is always diagonal)");
  writeSource(" ic(1,i) = i                 ! AMGCRS (diagonal is at first)");
  writeSource("end do");
  com();
  com();
  writeSource("! Construct ic array");
  com();
  writeSource("!-----------");
  writeSource("! My element");
  writeSource("!-----------");
  writeSource("do i=1,nelem");
  com();
  writeSource("!-------------------------------------------");
  writeSource("! step 1");
  writeSource("! make equation number list for i-th element");
  writeSource("!-------------------------------------------");
  writeSource("  iptr = 0");
  com();
  writeSource("  do j=1,np");
  writeSource("   nd = ielem(j,i)");
  writeSource("   do k=1,ipf(nd)");
  writeSource("      iptr = iptr + 1");
  writeSource("      ipt(iptr) = ipd(nd) + (k-1)        ! AMG/CRS equation number");
  writeSource("   end do");
  writeSource("  end do  ! do j=1,np");
  com();
  writeSource("! construct ic,ip");
  com();
  writeSource("  do j=1,iptr        !iptrhas the number of row candidates");
  writeSource("    nj = ipt(j)");
  com();
  writeSource("    do k=1,iptr        ! for all concerning columns");
  com();
  writeSource("      nk = ipt(k)      ! matrix cofficient is (nj,nk)");
  com();
  writeSource("      do l=1,ip(nj)");
  writeSource("        if(ic(l,nj) .eq. nk) goto 255");
  writeSource("      end do");
  com();
  writeSource("      ip(nj)        = ip(nj) + 1");
  writeSource("      ic(ip(nj),nj) = nk");
  com();
  writeSource("255   continue");
  com();
  writeSource("    end do  ! k=1,iptr      (column : all         )");
  writeSource("  end do    ! j=1,iptro   (row    : only my PE's)");
  com();
  writeSource("end do   ! do i=1,nelem    end of my element loop");
  com();
  writeSource("!--------------------------");
  writeSource("! Make indrow,iptrcol");
  writeSource("!--------------------------");
  writeSource("allocate( iptrcol(neq+1))");
  writeSource("iptrcol(1) = 1                     !");
  writeSource("ncof      = 0");
  com();
  writeSource("do i=1,neq");
  writeSource(" iptrcol(i+1) = iptrcol(i)+ip(i)");
  writeSource(" ncof         = ncof      +ip(i)");
  writeSource("end do");
  com();
  writeSource("allocate( indrow(ncof) )");
  writeSource("do i=1,neq");
  writeSource("  do j=1,ip(i)");
  writeSource("    indrow( iptrcol(i) + (j-1)) = ic(j,i)");
  writeSource("  end do");
  writeSource("end do");
  com();
  writeSource("deallocate(ip,ic)");
  com();
  writeSource("end subroutine mkAMGCRSindex");
  com();
  writeSource("end module AMGCRS");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
