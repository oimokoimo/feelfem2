/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_mat_skyline.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_MT_ff90SKYLINE.hpp"

static int come_yet_mat_skyline = 0;


void SL_MT_ff90SKYLINE::SL_mat_skyline(int makeFlag)
{
  char *sourceName;

  if(come_yet_mat_skyline == 1)  return;
  else                  come_yet_mat_skyline = 1;

  sourceName = GetSourceName("mat_skyline");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("module mod_mat_skyline");
  writeSource("contains");
  writeSource("subroutine cal_ht_a(ielem,neelem,nenode,KHa,npmax)");
  writeSource("!---");
  com();
  com();
  com();
  writeSource("!----");
  writeSource("implicit none");
  com();
  writeSource("integer,dimension(:,:),pointer    :: ielem");
  writeSource("integer,intent(in)                :: neelem,nenode");
  writeSource("integer,dimension(:),pointer      :: KHa");
  writeSource("integer,intent(in)                :: npmax");
  com();
  writeSource("! auto variables");
  writeSource("integer                           :: i,j,ip_min");
  writeSource("!----");
  writeSource("do  i=1,npmax");
  writeSource("   KHa(i) = npmax + 1");
  writeSource("end do");
  writeSource("!----");
  writeSource("do i=1,neelem");
  writeSource("   ip_min = ielem(1,i)");
  com();
  writeSource("! calc smallest node number at each element");
  writeSource("   do j=2,nenode");
  writeSource("      if(ip_min > ielem(j,i)) ip_min = ielem(j,i)");
  writeSource("   end do");
  com();
  writeSource("   do j=1,nenode");
  writeSource("      if(KHa(ielem(j,i)) > ip_min) KHa(ielem(j,i)) = ip_min");
  writeSource("   end do");
  com();
  writeSource("end do");
  com();
  writeSource("return");
  writeSource("end subroutine cal_ht_a");
  com();
  writeSource("subroutine cal_ht(KHa,KH,IPF,IPD,npmax,neq)");
  writeSource("!-----");
  com();
  writeSource("!-----");
  writeSource("integer,dimension(:),pointer  :: KHa,KH,IPF,IPD");
  writeSource("integer,intent(in)            :: npmax,neq");
  com();
  writeSource("! auto");
  writeSource("integer                       :: i");
  writeSource("integer                       :: min_np,ip_base");
  com();
  writeSource("! ----");
  writeSource("do i=1,npmax");
  writeSource("   if(IPF(i) .ne.  0) then");
  com();
  writeSource("!  min_np is smallest connecting equation No. for node No. i");
  com();
  writeSource("      min_np  = IPD( KHa(i) )");
  writeSource("      ip_base = IPD( i )");
  com();
  writeSource("      do j=1,IPF(i)");
  writeSource("         KH( ip_base + j - 1) = min_np");
  writeSource("      end do");
  writeSource("   end if");
  writeSource("end do");
  com();
  com();
  writeSource("do  i=1,neq");
  writeSource("   KH(i) = i - KH(i)");
  writeSource("end do");
  writeSource("return");
  writeSource("end subroutine cal_ht");
  com();
  writeSource("subroutine make_KLD(KH,KLD,neq,ncof)");
  writeSource("! make skyline information array KLD");
  com();
  writeSource("integer,dimension(:),pointer    :: KH,KLD");
  writeSource("integer,intent(in)              :: neq");
  writeSource("integer                         :: ncof");
  com();
  writeSource("! auto variables");
  writeSource("integer                         :: i");
  com();
  writeSource("!----------------------------------------");
  writeSource("KLD(1) = 1");
  writeSource("KLD(2) = 1");
  com();
  writeSource("do i = 3,neq+1");
  writeSource("   KLD(i) = KLD(i-1) + KH(i-1)");
  writeSource("end do");
  com();
  com();
  writeSource("ncof = KLD(neq + 1) - 1");
  com();
  writeSource("return");
  writeSource("end subroutine make_KLD");
  com();
  writeSource("end module mod_mat_skyline");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
