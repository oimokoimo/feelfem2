module mod_mat_skyline
contains
subroutine cal_ht_a(ielem,neelem,nenode,KHa,npmax)
!---
!
!
!
!----
implicit none

integer,dimension(:,:),pointer    :: ielem
integer,intent(in)                :: neelem,nenode
integer,dimension(:),pointer      :: KHa
integer,intent(in)                :: npmax

! auto variables
integer                           :: i,j,ip_min
!----
do  i=1,npmax
   KHa(i) = npmax + 1
end do
!----
do i=1,neelem
   ip_min = ielem(1,i)

! calc smallest node number at each element
   do j=2,nenode
      if(ip_min > ielem(j,i)) ip_min = ielem(j,i)
   end do
!
   do j=1,nenode
      if(KHa(ielem(j,i)) > ip_min) KHa(ielem(j,i)) = ip_min
   end do
         
end do

return
end subroutine cal_ht_a

subroutine cal_ht(KHa,KH,IPF,IPD,npmax,neq)
!-----
!
!-----
integer,dimension(:),pointer  :: KHa,KH,IPF,IPD
integer,intent(in)            :: npmax,neq

! auto
integer                       :: i
integer                       :: min_np,ip_base

! ----
do i=1,npmax
   if(IPF(i) .ne.  0) then

!  min_np is smallest connecting equation No. for node No. i

      min_np  = IPD( KHa(i) )
      ip_base = IPD( i )
!
      do j=1,IPF(i)
         KH( ip_base + j - 1) = min_np 
      end do
   end if
end do

!
do  i=1,neq
   KH(i) = i - KH(i)
end do
return
end subroutine cal_ht

subroutine make_KLD(KH,KLD,neq,ncof)
! make skyline information array KLD

integer,dimension(:),pointer    :: KH,KLD
integer,intent(in)              :: neq
integer                         :: ncof

! auto variables
integer                         :: i

!----------------------------------------
KLD(1) = 1
KLD(2) = 1
!
do i = 3,neq+1
   KLD(i) = KLD(i-1) + KH(i-1)
end do

!
ncof = KLD(neq + 1) - 1

return
end subroutine make_KLD

end module mod_mat_skyline
