module MUMPSCA

!
! MUMPS Centraized assemble
!

contains


subroutine mkMUMPSCAindex( neq,                   &
                           ndfmax,ncon,           &
                           ipf,ipd,npmax,         &
                           ielem,nelem,np,        &
                           mumps_par,             &
                           iptrcol               )
                           
! ---
! construct MUMPS Centralized assembled matrix
! 
!
!
use numeric
implicit none

include 'dmumps_struc.h'
                          
integer, intent(in)                    :: neq     ! number of freedom
integer, intent(in)                    :: ndfmax  ! Maximum freedom per element
integer, intent(in)                    :: ncon    ! Maximum relating freedom 
                                                  ! to one node  

integer, intent(in)                    :: npmax   
integer, intent(in),dimension(npmax)   :: ipf,ipd

integer, intent(in)                    :: nelem,np
integer, dimension(:,:)                :: ielem

type (DMUMPS_STRUC)                    :: mumps_par

! auto variables
integer, dimension(:),pointer          :: iptrcol,indrow   ! (AMGCRS)
integer                                :: ncof


integer                         :: i, j, k,l
integer                         :: nj,nk
integer                         :: iptr,nd   ! counter,and node number
integer,dimension(:,:),pointer  :: ic        ! allocate(ncon,neq)
                                             ! column index array(for indrow)

integer,dimension(:),pointer    :: ip        ! allocate(neq)
                                             ! row index array(for iptrcol)
                                             ! it does not include the first
                                             ! diagonal element, so it is not
                                             ! the same of pmkCRSindex's ip
                                             ! former ip(*)-1 = this ip(*)

integer,dimension(ndfmax)       :: ipt       ! equation number list for one 
                                             ! element

!======================================================================
! allocate ip(neq),ic(ncon,neq)
!
allocate( ip(neq) )
allocate( ic(ncon,neq) )     ! Huge array

do i=1,neq 
 ip(i)   = 1                 ! AMGCRS (first element is always diagonal)
 ic(1,i) = i                 ! AMGCRS (diagonal is at first)
end do


! Construct ic array

!-----------
! My element
!-----------
do i=1,nelem

!-------------------------------------------
! step 1
! make equation number list for i-th element
!-------------------------------------------
  iptr = 0

  do j=1,np
   nd = ielem(j,i)
   do k=1,ipf(nd)
      iptr = iptr + 1
      ipt(iptr) = ipd(nd) + (k-1)        ! AMG/CRS equation number
   end do
  end do  ! do j=1,np

! construct ic,ip

  do j=1,iptr        !iptrhas the number of row candidates
    nj = ipt(j)

    do k=1,iptr        ! for all concerning columns

      nk = ipt(k)      ! matrix cofficient is (nj,nk)

      do l=1,ip(nj)
        if(ic(l,nj) .eq. nk) goto 255
      end do
      
      ip(nj)        = ip(nj) + 1
      ic(ip(nj),nj) = nk  

255   continue

    end do  ! k=1,iptr      (column : all         )
  end do    ! j=1,iptro   (row    : only my PE's)

end do   ! do i=1,nelem    end of my element loop

!--------------------------
! Make indrow,iptrcol
!--------------------------
allocate( iptrcol(neq+1))
iptrcol(1) = 1                     ! 
ncof      = 0

do i=1,neq
 iptrcol(i+1) = iptrcol(i)+ip(i)
 ncof         = ncof      +ip(i)
end do

allocate( indrow(ncof) )
do i=1,neq
  do j=1,ip(i)
    indrow( iptrcol(i) + (j-1)) = ic(j,i)
  end do
end do

deallocate(ip,ic)

!-----------------------------
! Make MUMPS data structure (Currently, AMGCRS policy, appliced, first is diag)
!-----------------------------

mumps_par%N   = neq
mumps_par%NZ  = ncof
allocate( mumps_par%IRN(ncof))
allocate( mumps_par%JCN(ncof))

do i=1,neq
   do j=iptrcol(i),iptrcol(i+1)-1
      mumps_par%IRN(j) = i             ! row number
      mumps_par%JCN(j) = indrow(j)     ! column number
   end do
end do

deallocate(indrow)

end subroutine mkMUMPSCAindex

end module MUMPSCA
