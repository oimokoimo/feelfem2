module PAMGCRS

contains

subroutine pmkAMGCRShalo(nouter,ndno,peno,ipf_ex,ipd_ex,ipd_halo,sort) 
integer,intent(in)          :: nouter
integer,dimension(nouter)   :: ndno,peno,ipf_ex,ipd_ex
integer,dimension(:),pointer:: ipd_halo,sort

! auto variables
integer                     :: i,j

integer                     :: ip,jp

integer                     :: ipt

!-----------------
!make sort array 

allocate(sort(nouter))
do i=1,nouter
 sort(i) = i
end do

do i=1,nouter-1
 
 ip = sort(i)
 do j=i+1,nouter
  jp = sort(j)

  if(peno(jp) < peno(ip) .or. (peno(jp) == peno(ip) .and. ndno(jp) < ndno(ip)) ) then
    sort(i) = jp
    sort(j) = ip
    ip = jp
  end if
 end do
end do

!---
allocate(ipd_halo(nouter))
ipt = 1
do i=1,nouter
  ipd_halo(sort(i)) = ipt
  ipt = ipt + ipf_ex(sort(i))
end do

!--
!do i=1,nouter
!write(*,*) 'i=',i,'  pe,nd=',peno(sort(i)),ndno(sort(i))
!end do

!do i=1,nouter
!write(*,*) 'i=',i,' pe,nd,ipd_halo=',peno(i),ndno(i),ipd_halo(i)
!end do
  
  
end subroutine pmkAMGCRShalo

subroutine pmkAMGCRSupdate(myrank,nprocs,mypeid,           &
                           neq,nhalo,isumup,               &
                           ndno,peno,nouter,               &
                           ipf_ex,ipd_ex,ipd_halo,sort_ex, &
                           iptrcol,indrow,ncof,            &
                           penv,pupdate,glinfo             )

use mod_amg_update
use mod_amg_penv

implicit none

integer                      :: myrank,nprocs,mypeid
integer                      :: neq,nhalo
integer,dimension(:)         :: isumup
integer                      :: nouter
integer,dimension(nouter)    :: ndno,peno,ipf_ex,ipd_ex,ipd_halo
integer,dimension(:),pointer :: sort_ex
integer,dimension(:)         :: iptrcol,indrow
integer                      :: ncof

type (amg_penv),       pointer :: penv
type (amg_update_info),pointer :: pupdate
type (amg_global_info),pointer :: glinfo   

! auto variables
integer                        :: i,j,k 
integer                        :: ipt
integer,dimension(nhalo)       :: ienum,iproc   ! for pinput2amg routine

integer                        :: nnuglobal
integer                        :: myi
integer,dimension(:),pointer   :: partition

!----------------------------------------------------------
k = 0
do i=1,nouter
 ipt = sort_ex(i)
 do j=1,ipf_ex(ipt)
  k=k+1
  iproc(k) = peno(ipt) + 1
  ienum(k) = isumup(peno(ipt)+1)+ipd_ex(ipt)+(j-1)
 end do
end do

nnuglobal = isumup(nprocs+1)


allocate(partition(nnuglobal))
do i=1,nprocs
do j=isumup(i)+1,isumup(i+1)
 partition(j) = i-1
end do
end do

myi = myrank + 1

call amg_pinput2amg(penv,pupdate,glinfo, &
                    myi,nprocs,MPI_COMM_WORLD,neq,nhalo, &
                    ienum,iproc,                              &
                    iptrcol,indrow,ncof,partition,nnuglobal   )

deallocate( partition )
deallocate( sort_ex   )

end subroutine pmkAMGCRSupdate


subroutine pmkAMGCRSindex(mypeid,nprocs,                &
                          neq,isumup,                   &
                          ndfmax,ncon,                  &
                          ipf,ipd,npmax,                &
                          ndno,peno,nouter,             & 
                          ipf_ex,ipd_ex,ipd_halo,       &
                          enptr   ,con   ,nelem   ,     &
                          enptr_ex,con_ex,nelem_ex,     &
                          iptrcol,indrow,ncof,nhalo     )
                           
! ---
! construct AMG/CRS matrix index
! 
!
!

use numeric
use subSolveDrama
implicit none
                          
integer, intent(in)          :: mypeid,nprocs
integer, intent(in)          :: neq            ! number of freedom of my PE
integer, dimension(nprocs)   :: isumup

integer, intent(in)          :: ndfmax         ! Maximum freedom in one element
integer, intent(in)          :: ncon           ! Maximum relating freedom to 
                                               ! one node  

integer, intent(in)                    :: npmax   
integer, intent(in),dimension(npmax)   :: ipf,ipd
integer, intent(in)                    :: nouter
integer, dimension(nouter)             :: ndno,peno,ipf_ex,ipd_ex
integer, dimension(nouter)             :: ipd_halo

integer, intent(in)                    :: nelem
integer, dimension(:,:)                :: enptr,con
integer, intent(in)                    :: nelem_ex
integer, dimension(:,:)                :: enptr_ex,con_ex

integer, dimension(:),pointer          :: iptrcol,indrow   ! allocate here
integer                                :: ncof,nhalo


! auto variables
integer                         :: i, j, k,l
integer                         ::   nj,nk
integer                         :: ipos_from,ipos_to
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
integer,dimension(ndfmax)       :: ipno      ! local equation number list
                                             ! only for local rows 

integer                         :: iptr      ! pointer
integer                         :: iptr_ipno ! pointer

integer                         :: nd,pe     ! node number / pe number

integer                         :: exno      ! external list number

!======================================================================
! allocate ip(neq),ic(ncon,neq)
!
allocate( ip(neq) )
allocate( ic(ncon,neq) )     ! Huge array

do i=1,neq 
 ip(i)   = 1                 ! AMGCRS (first element is always diagonal)
 ic(1,i) = i                 ! AMGCRS (local column number for local equations)
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
  iptr      = 0
  iptr_ipno = 0
  ipos_from = enptr(1,i  )
  ipos_to   = enptr(1,i+1)-1
 
  do j=ipos_from,ipos_to
   nd = con(1,j)
   pe = con(2,j)

   if(pe .eq. mypeid) then

     do k=1,ipf(nd)
      iptr = iptr + 1
      ipt(iptr) = ipd(nd) + (k-1)        ! AMG/CRS is LOCAL NUMBER

      iptr_ipno       = iptr_ipno + 1
      ipno(iptr_ipno) = ipd(nd) + (k-1)  ! Row number list(local number)
                                         ! both for AMGCRS and AchimCRS

     end do

   else

     exno = ndsearch_ex(nd,pe,ndno,peno,nouter)
     do k=1,ipf_ex(exno)
       iptr = iptr + 1
       ipt(iptr) = neq+ipd_halo(exno)+(k-1)    ! AMG/CRS halo no global 
     end do 

   endif   ! if(pe .eq. mypeid)

  end do  ! do j=ipos_from,ipos_to

! construct ic,ip

  do j=1,iptr_ipno     !iptr_ipno has the number of rows for my PE
    nj = ipno(j)

    do k=1,iptr        ! for all concerning columns

      nk = ipt(k)      ! matrix cofficient is (nj,nk)

      do l=1,ip(nj)
        if(ic(l,nj) .eq. nk) goto 255
      end do
      
      ip(nj)        = ip(nj) + 1
      ic(ip(nj),nj) = nk  

255   continue

    end do  ! k=1,iptr      (column : all         )
  end do    ! j=1,iptr_no   (row    : only my PE's)

end do   ! do i=1,nelem    end of my element loop


!----------------
! Other's element
!----------------
do i=1,nelem_ex

!-------------------------------------------
! step 1
! make equation number list for i-th element
!-------------------------------------------
  iptr      = 0
  iptr_ipno = 0
  ipos_from = enptr_ex(1,i  )
  ipos_to   = enptr_ex(1,i+1)-1
 
  do j=ipos_from,ipos_to
   nd = con_ex(1,j)
   pe = con_ex(2,j)

   if(pe .eq. mypeid) then

     do k=1,ipf(nd)
      iptr = iptr + 1
      ipt(iptr) = ipd(nd) + (k-1)    ! AMG/CRS is LOCAL NUMBER

      iptr_ipno       = iptr_ipno + 1
      ipno(iptr_ipno) = ipd(nd) + (k-1)  ! Row number list(local number)
                                         ! both for AMGCRS and AchimCRS

     end do

   else

     exno = ndsearch_ex(nd,pe,ndno,peno,nouter)
     do k=1,ipf_ex(exno)
       iptr      = iptr + 1
       ipt(iptr) = neq + (ipd_halo(exno)+(k-1))  ! AMG/CRS halo no.
     end do 

   endif   ! if(pe .eq. mypeid)

  end do  ! do j=ipos_from,ipos_to

! construct ic,ip

  do j=1,iptr_ipno     !iptr_ipno has the number of rows for my PE
    nj = ipno(j)

    do k=1,iptr        ! for all concerning columns

      nk = ipt(k)      ! matrix cofficient is (nj,nk)

      do l=1,ip(nj)
        if(ic(l,nj) .eq. nk) goto 355
      end do
      
      ip(nj)        = ip(nj) + 1
      ic(ip(nj),nj) = nk  

355   continue

    end do  ! k=1,iptr      (column : all         )
  end do    ! j=1,iptr_no   (row    : only my PE's)

end do   ! do i=1,nelem_ex   end of my element loop


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

!------------------
! nhalo calculation
!------------------
nhalo = 0
do i=1,nouter
  nhalo = nhalo + ipf_ex(i)
end do

end subroutine pmkAMGCRSindex

end module PAMGCRS
