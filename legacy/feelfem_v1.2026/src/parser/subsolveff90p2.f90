module subsolveff90p2

contains

subroutine makeipfp2(nenfre,maxElementFreedom,neg, &
                     ielem,nelem,np,npmax,ipf      )
!--------------
! construct ipf
!--------------
use numeric

implicit none

integer                                  :: maxElementFreedom,neg
integer                                  :: nelem,np,npmax

integer,dimension(maxElementFreedom,neg) :: nenfre
integer,dimension(:,:),pointer           :: ielem
integer,dimension(npmax)                 :: ipf          ! initialized here

! auto variables
integer                                  :: i,j

!------------------------------------------------------
do i=1,npmax
  ipf(i) = 0
end do

do i=1,nelem

 do j=1,np

   ipf(ielem(j,i)) = nenfre(j,0001)   ! P2 restriction

  end do

end do

end subroutine makeipfp2

subroutine makeipdp2(ipf,ipd,npmax,neq)
use abortmodule
implicit none

integer                    :: npmax
integer                    :: neq
integer ,dimension(npmax)  :: ipf,ipd

! auto variables

integer                    :: i
integer                    :: istart
integer                    :: nowfree

!-----------------------------------------------------

! initialization
neq = 0
do i=1,npmax
   ipd(i) = 0
end do


! find first freedom

istart = 0
do i=1,npmax
  if(ipf(i) .ne. 0) then
    istart = i
    exit
  endif
end do

! cannot find the first degree of freedom
if(istart .eq. 0) then
  call abortexit('Cannot find first degree of freedom')
endif


! construct IPD array

nowfree     = ipf(istart)
ipd(istart) = 1

do i=istart+1,npmax
  if(ipf(i) .ne. 0) then
    ipd(i) = nowfree + 1
    nowfree = nowfree + ipf(i)
  endif
end do

neq = nowfree

end subroutine makeipdp2

subroutine nc_connectp2(npmax,ielem,nelem,np, &
                        ncmax                 )
use numeric

implicit none

integer,intent(in)               :: npmax,nelem,np
integer,dimension(:,:),pointer   :: ielem
integer,intent(out)              :: ncmax

! auto variables

integer                          :: i,j
integer,dimension(:),pointer     :: nc

!----------------
! nc preparation
!----------------
allocate(nc(npmax))
do i=1,npmax
 nc(i) = 0
end do

!--------------------------
! count element connections
!--------------------------
do i=1,nelem
  do j=1,np
  nc(ielem(j,i)) = nc(ielem(j,i)) + 1
  end do
end do

!--------------------------
! calculate ncmax
!--------------------------
ncmax = nc(1)
do i=2,npmax
  if(ncmax < nc(i) ) ncmax = nc(i)
end do

deallocate(nc)

end subroutine nc_connectp2

end module subsolveff90p2
