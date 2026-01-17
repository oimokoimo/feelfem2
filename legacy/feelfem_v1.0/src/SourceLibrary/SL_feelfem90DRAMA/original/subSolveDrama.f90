module subSolveDrama
!---------------------------------------------------------
! Problem independent subsidiary routines for solve routine
!
! feelfemf90/drama model  
! 
! subroutine makeipfdrama : Make freedom array for each node 
! subroutine makeipddrama : (Independent of DRAMA)
! subroutine mksendlst    :
! subroutine pnc_connect90: Calculate maximul number of connecting nodes
!
! function   ndsearch_ex  : outer node search :(if not found, abort)
! function   ndsearch_ex2 : return NodeError(-1) if not found 
! function   dramafemval  : search and return fem_ex value
!---------------------------------------------------------
contains

subroutine makeipfdrama(mypeid,nenfre,maxElementFreedom,neg, &
                        enptr,con,nelem,npmax,ipf)
!---------------
! calculate ipf(*) array with drama double index enptr/con and nenfre
!---------------
use abortmodule
use numeric
implicit none
integer                                  :: mypeid
integer                                  :: maxElementFreedom,neg 
integer                                  :: nelem,npmax
 
integer,dimension(maxElementFreedom,neg) :: nenfre
integer,dimension(2,nelem)               :: enptr
integer                                  :: con(2,*)
integer,dimension(npmax)                 :: ipf

! auto variables

integer                    :: i,j
integer                    :: ipos_from,ipos_to
integer                    :: elementType
integer                    :: iptr

!-------------------------------------------------------------

!  initialize ipf = number of freedom at each node

do i=1,npmax
  ipf(i) = 0
end do

!

do i=1,nelem
   ipos_from = enptr(1,i)
   ipos_to   = enptr(1,i+1)-1

   elementType = enptr(2,i)

   if(elementType .EQ. Nur_One_Etype) then
     do j=ipos_from,ipos_to
       iptr = j - ipos_from + 1
       if(con(2,j) .eq. mypeid) then
         ipf(con(1,j)) = nenfre(iptr,0001)   ! 0001 means nur one etype
       endif
     end do
   else

     write(*,*) 'elementType =',elementType,' i=',i
     write(*,*) 'Not allowed element type in enptr(2,*) feel_dat limitation '
     call abortexit(mypeid) 
   endif
end do

end subroutine makeipfdrama

subroutine makeipddrama(ipf,ipd,npmax,neq)
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
  write(*,*) 'Cannot find first degree of freedom'
  call abortexit(-999)
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

end subroutine makeipddrama

subroutine mksendlst(myrank,nprocs,mypeid,   &
                     enptr,con,nelem,npmax,  &
                     eflag,nflag,            &
                     ne2send,nconsiz,nn2send )

use numeric
use feelfem90mp
implicit none
!
integer,intent(in)        :: myrank,nprocs,mypeid
integer,intent(in)        :: enptr(2,*),con(2,*)
integer,intent(in)        :: nelem,npmax
integer,dimension(nelem)  :: eflag
integer,dimension(npmax)  :: nflag
integer                   :: ne2send,nconsiz,nn2send

! auto variables

integer                          :: i,j
integer                          :: iptr
integer                          :: ipos_from,ipos_to         
integer                          :: nodeofother       ! n of others' nodes

integer,dimension(:,:),pointer   :: reqcon            ! request con array 
integer,dimension(:,:),pointer   :: allreqcon         ! exchange con array
integer,dimension(:)  ,pointer   :: counts,displs     ! for gathervbcast

!--------------------------------------------
!initialization


ne2send  = 0
nconsiz  = 0
nn2send  = 0

do i=1,nelem
 eflag(i) = Non 
end do

do i=1,npmax
 nflag(i) = Non 
end do

!------------------------------------------------------------------
! step 1-1
! Count the other PE's node in my elements
! In current implementation, duplication of sending nodes occures
! In addition, construct eflag(*) array
!------------------------------------------------------------------
nodeofother = 0
do i=1,nelem
  ipos_from = enptr(1,i  )
  ipos_to   = enptr(1,i+1)-1

  do j=ipos_from,ipos_to
    if(con(2,j) .ne. mypeid) then     ! double count occures 
      nodeofother = nodeofother + 1
      eflag(i) = Oui
    endif
  end do
end do

if(nodeofother .eq. 0) then
!!!! nullify(reqcon)                       ! 

   allocate(reqcon(2,1))                 ! for PGI fortran
else
  allocate(reqcon(2,nodeofother))
  iptr = 0
  do i=1,nelem
    ipos_from = enptr(1,i  )
    ipos_to   = enptr(1,i+1)-1

    do j=ipos_from,ipos_to
      if(con(2,j) .ne. mypeid) then
        iptr = iptr + 1
        reqcon(1,iptr) = con(1,j)
        reqcon(2,iptr) = con(2,j)
      endif
    end do
  end do
endif

!-------------------------
! step 1-2 
! gather/scatter
!-------------------------


call ff90gathervbcast2(myrank,nprocs,2,nodeofother,reqcon,  &
                              allreqcon,counts,displs        )
!-------------------------
! step 1-3
! make nflag list
!-------------------------
do i=1,nprocs
  do j=1,counts(i)
    iptr = j+ displs(i)
    if(mypeid .eq. allreqcon(2,iptr) ) then
      nflag(allreqcon(1,iptr)) = Oui
    endif
  end do
end do
  

!-------------------------
! step 1-4
! deallocation
!-------------------------
deallocate(allreqcon,counts,displs)
if(associated(reqcon)) deallocate(reqcon)


!---------------
! step 2-1 count send buffer information for element
!---------------
do i=1,nelem
  if(eflag(i) .eq. Oui) then
    ipos_from = enptr(1,i  )
    ipos_to   = enptr(1,i+1)-1
    ne2send = ne2send +  1
    nconsiz = nconsiz + (ipos_to-ipos_from+1) 
  endif
end do


!---------------
! step 2-2 count send buffer information for node 
!---------------
do i=1,nelem
  if(eflag(i) .eq. Oui) then
    ipos_from = enptr(1,i  )
    ipos_to   = enptr(1,i+1)-1
    do j=ipos_from,ipos_to
      if(con(2,j) .eq. mypeid) then
        nflag(con(1,j)) = Oui
      endif
    end do
  endif
end do

!---------------
! step 2-3 count total nodes to send 
!---------------
do i=1,npmax
  nn2send = nn2send + nflag(i)
end do

999 continue
end subroutine mksendlst

subroutine pnc_connect90(mypeid,npmax,enptr   ,con   ,nelem   , &
                                      enptr_ex,con_ex,nelem_ex, &
                                      ncmax                     )
!
implicit none
integer,intent(in)              :: mypeid,npmax
integer,intent(in)              :: nelem,nelem_ex 
integer,dimension(2,nelem+1)    :: enptr
integer                         :: con(2,*)
integer,dimension(2,nelem_ex+1) :: enptr_ex
integer                         :: con_ex(2,*)
integer,intent(out)             :: ncmax

! auto variables
integer                         :: i,j
integer                         :: ipos_from,ipos_to
integer,dimension(:),pointer    :: nc
!====================================================
! nc preparation

!write(*,*) '******************'
!write(*,*) '**now do nothing**'
!write(*,*) '******************'

allocate(nc(npmax))
do i=1,npmax
nc(i)=0
end do


!---------------------------------------------------
! Count the connecting elements 
! Part 1: my PE's element
!---------------------------------------------------
do i=1,nelem
 ipos_from = enptr(1,i  )
 ipos_to   = enptr(1,i+1)-1
 do j=ipos_from,ipos_to
   if(con(2,j) .eq. mypeid) then
     nc(con(1,j)) = nc(con(1,j)) + 1
   endif
 end do
end do

!---------------------------------------------------
! Count the connecting elements 
! Part 2: other PEs' element
!---------------------------------------------------
do i=1,nelem_ex
 ipos_from = enptr_ex(1,i  )
 ipos_to   = enptr_ex(1,i+1)-1
 do j=ipos_from,ipos_to
   if(con_ex(2,j) .eq. mypeid) then
     nc(con_ex(1,j)) = nc(con_ex(1,j)) + 1
   endif
 end do
end do

!---------------------
! calculate ncmax
!---------------------
ncmax=nc(1)
do i=2,npmax
 if(ncmax .lt. nc(i)) ncmax = nc(i)
end do

! deallocation of array nc

deallocate(nc)

999 continue
end subroutine pnc_connect90


integer function ndsearch_ex(nd,pe,ndno,peno,nouter)
! search outer node number 
use abortmodule
implicit none
integer,intent(in)         :: nd,pe     ! questioned node number and PE number
integer,dimension(nouter)  :: ndno,peno ! node/pe number list
integer,intent(in)         :: nouter    ! number of external nodex

!auto varaible
integer                    :: i

!================================================
do i=1,nouter
  if(nd .eq. ndno(i) .AND. pe .eq. peno(i)) then
    ndsearch_ex = i
    return
  endif
end do

write(*,*) '[ndsearch_ex] Cannot find PE ',pe,' node ',nd
call abortexit(-999)

end function ndsearch_ex

integer function ndsearch_ex2(nd,pe,ndno,peno,nouter)
! search outer node number 
use numeric
implicit none
integer,intent(in)         :: nd,pe     ! questioned node number and PE number
integer,dimension(nouter)  :: ndno,peno ! node/pe number list
integer,intent(in)         :: nouter    ! number of external nodex

!auto varaible
integer                    :: i

!================================================
do i=1,nouter
  if(nd .eq. ndno(i) .AND. pe .eq. peno(i)) then
    ndsearch_ex2 = i
    return
  endif
end do

ndsearch_ex2 = NodeError
return

end function ndsearch_ex2


real*8 function dramafemval(mypeid, ind,ipe,val,npmax, &
                            valex,ndno,peno,nouter)
!------------------------------------------------------------
!    Get fem value by nd/pe double index pair
!
!    val(npmax)
!    valex(nouter),ndno(nouter),peno(nouter)
!------------------------------------------------------------
      integer*4 mypeid
      integer*4 ind,ipe
      real   *8 val(*)
      integer*4 npmax
      real   *8 valex(*)
      integer*4 ndno(*),peno(*)
      integer*4 nouter
!------------------------------------------------------
      if(mypeid .eq. ipe) then
         dramafemval = val(ind)
      else
!
         nd = ndsearch_ex(ind,ipe,ndno,peno,nouter)
         dramafemval = valex(nd)
      endif
!
      return
end function dramafemval      
end module subSolveDrama 
