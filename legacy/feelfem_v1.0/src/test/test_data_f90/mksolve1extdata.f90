module mod_mksolve1extdata
contains

subroutine mksolve1extdata(myrank,nprocs,mypeid,              &
                    enptr,con,matno,nelem,             &
                    ipf,ipd,npmax,                     &
                    neq,                               &
                    isumup,                            &
                    nelem_ex,enptr_ex,con_ex,matno_ex, &
                    nouter,ndno,peno,ipf_ex,ipd_ex,    &
                    x,y,x_ex,y_ex,fem_v,fem_v_ex)
!------------------------------------------------------
! Problem dependent subroutine Make external data
!
! Following arrays are allocated in this subroutine
!
! isumup                   : sumup degree of freedom 
! enptr_ex,con_ex,matno_ex : external related element
! ndno,peno,ipf_ex,ipd_ex  : related outer node index
! external fem variables   : x_ex,y_ex, fem_ex,...etc.
!------------------------------------------------------
use numeric
use abortmodule
use feelfem90mp      ! message passing with memory allocation
use subSolveDrama
use preport90

implicit none

include 'mpif.h'

integer,intent(in)               :: myrank,nprocs,mypeid
integer,dimension(:,:)           :: enptr,con
integer,dimension(:)             :: matno
integer,intent(in)               :: nelem,npmax
integer,dimension(:)             :: ipf,ipd
integer,intent(in)               :: neq
integer,dimension(:),pointer     :: isumup   ! allocate here

integer                          :: nelem_ex
integer,dimension(:,:),pointer   :: enptr_ex,con_ex
integer,dimension(:),pointer     :: matno_ex
integer                          :: nouter
integer,dimension(:),pointer     :: ndno,peno,ipf_ex,ipd_ex

real(kind=REAL8),dimension(:),pointer :: x,y
real(kind=REAL8),dimension(:),pointer :: x_ex,y_ex
real(kind=REAL8),dimension(:),pointer :: fem_v
real(kind=REAL8),dimension(:),pointer :: fem_v_ex

! auto variables
!--------------------------------------------
! Auto variables
!--------------------------------------------
integer                          :: i,j,k
integer                          :: l,lptr
integer                          :: iptr,ipos,ipos_from,ipos_to
integer                          :: ierror

! used in mksendlst
integer, dimension(:),pointer    :: nflag,eflag
integer                          :: ne2send,nconsiz,nn2send

integer, parameter               :: n_of_ctrl = 4
integer, dimension(n_of_ctrl)    :: ctrl_send
integer, dimension(:)  ,pointer  :: ctrl_all

integer                          :: nsend_enptr !  0 or ne2send+1
integer, dimension(:,:),pointer  :: enptr_send,con_send
integer, dimension(:,:),pointer  :: enptr_all,con_all
integer, dimension(:)  ,pointer  :: enptr_counts,enptr_displs
integer, dimension(:)  ,pointer  :: con_counts,  con_displs

integer, dimension(:)  ,pointer  :: matno_send
integer, dimension(:)  ,pointer  :: matno_all,matno_counts, &
                                    matno_displs

integer, dimension(:)  ,pointer  :: nd_counts,nd_displs
integer                          :: nd_allcounts
 
integer, dimension(:)  ,pointer  :: nodeno_send,nodeno_all
integer, dimension(:)  ,pointer  :: peno_all
integer, dimension(:)  ,pointer  :: ipf_send,ipd_send
integer, dimension(:)  ,pointer  :: ipf_all,ipd_all

integer                      :: nconsiz_ex    ! temporary use
integer                      :: procbuf(nprocs)
integer                      :: nelem_tmp
integer                      :: enptr_base,con_base,matno_base

real(kind=REAL8),dimension(:),pointer  :: x_send,y_send
real(kind=REAL8),dimension(:),pointer  :: x_all,y_all
real(kind=REAL8),dimension(:),pointer  :: fem_v_send
real(kind=REAL8),dimension(:),pointer  :: fem_v_all
!--------------------------------------------------
! first, allocate isumup(nprocs+1)
!--------------------------------------------------
allocate(isumup(nprocs+1))

!--------------------------------------------------
! Make message passing list
! This routine is a problem independent routine
!--------------------------------------------------
allocate(nflag(npmax),eflag(nelem))

call mksendlst(myrank,nprocs,mypeid,enptr,con,nelem,npmax,  &
               eflag,nflag,ne2send,nconsiz,nn2send          )

if(myrank .eq. 0) call preport('MODULE: mksendlst')

!------------------------------------------------------
! ! old:solve1mksdbuf
!------------------------------------------------------
ctrl_send(1) = ne2send
ctrl_send(2) = nconsiz
ctrl_send(3) = nn2send
ctrl_send(4) = neq

! Element information to send
if(ne2send == 0) then

  nsend_enptr = 0
!  nullify(enptr_send,matno_send,con_send)
  allocate(enptr_send(2,1),con_send(2,1),matno_send(2))

else

  nsend_enptr = ne2send+1
  allocate(enptr_send(2,nsend_enptr),con_send(2,nconsiz))
  allocate(matno_send(ne2send))

  iptr = 0
  ipos = 1

  do i=1,nelem
    if(eflag(i) == Oui) then
      iptr = iptr + 1
      enptr_send(1,iptr) = ipos
      enptr_send(2,iptr) = enptr(2,i)
      matno_send(  iptr) = matno(i)

      ipos_from = enptr(1,i  )
      ipos_to   = enptr(1,i+1)-1

      do j=ipos_from,ipos_to
        con_send(1,ipos) = con(1,j)
        con_send(2,ipos) = con(2,j)
        ipos             = ipos+1
      end do
    endif
  end do

  enptr_send(1,iptr+1) = ipos
  enptr_send(2,iptr+1) = EndOfEnptr

  if(iptr+1 .ne. nsend_enptr) then
    write(*,*) 'iptr+1 .ne. nsend_enptr  myrank=',myrank
    write(*,*) 'myrank=',myrank,'  ne2send,iptr=',ne2send,iptr
    call abortexit(myrank)
  endif

endif 

!----------------------------
! node information to send
!----------------------------
iptr = 0
if(nn2send .le. 0) then
  write(*,*) 'nn2send =0 ERROR'
  write(*,*) 'myrank=',myrank,'  nn2send=',nn2send
  call abortexit(myrank)
endif

allocate(nodeno_send(nn2send))
allocate(ipf_send   (nn2send))
allocate(ipd_send   (nn2send))

allocate(x_send     (nn2send))
allocate(y_send     (nn2send))
allocate(fem_v_send(nn2send))

do i=1,npmax
  if(nflag(i) .eq. Oui) then
    iptr = iptr + 1
    nodeno_send(iptr) = i
    ipf_send   (iptr) = ipf(i)
    ipd_send   (iptr) = ipd(i)
    x_send     (iptr) = x(i)
    y_send     (iptr) = y(i)
    fem_v_send(iptr) = fem_v(i)
  endif
end do

if(iptr .ne. nn2send) then
  write(*,*) '[mksolve1exdata]myrank=',myrank,' nn2send != iptr '
  call abortexit(myrank)
endif

!-----------------------------------------------
! share
!-----------------------------------------------
! ctrl
call ff90allgather(myrank,nprocs,n_of_ctrl,ctrl_send,ctrl_all)

! enptr
call ff90gathervbcast2(myrank,nprocs,2,nsend_enptr,enptr_send, &
                       enptr_all,enptr_counts,enptr_displs   )

! con
call ff90gathervbcast2(myrank,nprocs,2,nconsiz,con_send,     &
                       con_all,con_counts,con_displs         )
! matro
call ff90gathervbcast (myrank,nprocs,ne2send,matno_send,     &
                       matno_all,matno_counts,matno_displs   )

!----------------------------------------------------------------
! nodeno (nd_counts,nd_displs allocate here)
!----------------------------------------------------------------
call ff90gathervbcast (myrank,nprocs,nn2send,nodeno_send,    &
                       nodeno_all,nd_counts,nd_displs        )
nd_allcounts = 0
do i=1,nprocs
  nd_allcounts = nd_allcounts + nd_counts(i)
end do

! make peno_all from nd_counts(i)
allocate(peno_all(nd_allcounts))
iptr = 0
do i=1,nprocs
  do j=1,nd_counts(i)
   iptr=iptr+1
   peno_all(iptr) = i-1      ! RANK NO starts 0
  end do
end do

! ipf
allocate(ipf_all(nd_allcounts))
call MPI_ALLGATHERV(ipf_send,nn2send,            MPI_INTEGER, &
                    ipf_all ,nd_counts,nd_displs,MPI_INTEGER, &
                    MPI_COMM_WORLD,ierror                       )

! ipd
allocate(ipd_all(nd_allcounts))
call MPI_ALLGATHERV(ipd_send,nn2send,            MPI_INTEGER, &
                    ipd_all ,nd_counts,nd_displs,MPI_INTEGER, &
                    MPI_COMM_WORLD,ierror                       )

! x
allocate(x_all(nd_allcounts))
call MPI_ALLGATHERV(x_send,nn2send,MPI_DOUBLE_PRECISION,&
      x_all ,nd_counts,nd_displs,  MPI_DOUBLE_PRECISION,&
                                   MPI_COMM_WORLD,ierror)

! y
allocate(y_all(nd_allcounts))
call MPI_ALLGATHERV(y_send,nn2send,MPI_DOUBLE_PRECISION,&
      y_all ,nd_counts,nd_displs,  MPI_DOUBLE_PRECISION,&
                                   MPI_COMM_WORLD,ierror)

! fem_v
allocate(fem_v_all(nd_allcounts))
call MPI_ALLGATHERV(fem_v_send,nn2send,           MPI_DOUBLE_PRECISION,&
                    fem_v_all,nd_counts,nd_displs,MPI_DOUBLE_PRECISION,&
                    MPI_COMM_WORLD,ierror     )

!------------------------------------------------------
! sumupdegree
!------------------------------------------------------
isumup(1) = 0
do i=1,nprocs
  isumup(i+1)=isumup(i)+ctrl_all((i-1)*n_of_ctrl + 4)
end do

!------------------------------------------------------
! makeielemex
!------------------------------------------------------

! count nelem_ex
nelem_ex   = 0
nconsiz_ex = 0

do 1 i=1,nprocs
  procbuf(i) = 0
  if(mypeid+1 .ne. i) then
   nelem_tmp=ctrl_all( (i-1)*n_of_ctrl + 1)  ! ne2send of PE(i-1)
   if(nelem_tmp .gt. 0) then

    enptr_base = enptr_displs(i)
    con_base   = con_displs(i)

    do 2 j=1,nelem_tmp
     ipos_from = enptr_all(1,enptr_base+j  )
     ipos_to   = enptr_all(1,enptr_base+j+1) - 1

     do 3 k=ipos_from,ipos_to
       if( con_all(2,con_base+k) .eq. mypeid) then
         procbuf(i) = procbuf(i)+1
         nconsiz_ex = nconsiz_ex + (ipos_to-ipos_from+1)
         goto 2
       endif
3    continue
2   continue

   end if ! of nelem_tmp .gt. 0
  end if ! of mypeid+1  .ne. i

  nelem_ex = nelem_ex + procbuf(i)

1 continue

! make enptr_ex,con_ex,matno_ex, 

if(nelem_ex .eq. 0) then

  iptr = 0
!  nullify(enptr_ex,con_ex,matno_ex)  ! PGI/ABI
  allocate(enptr_ex(2,1),con_ex(2,1),matno_ex(2))  

else
  allocate(enptr_ex(2,nelem_ex+1),con_ex(2,nconsiz_ex))
  allocate(matno_ex(nelem_ex))
  enptr_ex(1,1) = 1

  iptr = 0
  do i=1,nprocs

   if(procbuf(i) .ne. 0 .and. mypeid+1 .ne. i) then
    nelem_tmp = ctrl_all((i-1)*n_of_ctrl+1) ! ne2send of PE(i-1)
    enptr_base = enptr_displs(i)
    con_base   = con_displs(i)
    matno_base = matno_displs(i)

    do 11 j=1,nelem_tmp
     ipos_from = enptr_all(1,enptr_base+j  )
     ipos_to   = enptr_all(1,enptr_base+j+1) -1

     do k=ipos_from,ipos_to
      if(con_all(2,con_base+k) .eq. mypeid) then
       iptr = iptr + 1
       enptr_ex(2,iptr  )=enptr_all(2,enptr_base+j)
       enptr_ex(1,iptr+1)=enptr_ex(1,iptr)+(ipos_to-ipos_from+1)
       matno_ex(iptr    ) = matno_all(matno_base+j)

       do l=ipos_from,ipos_to
        lptr = l-ipos_from       ! lptr = 0,1,2,3,....
        con_ex(1,enptr_ex(1,iptr)+lptr)=con_all(1,con_base+l)
        con_ex(2,enptr_ex(1,iptr)+lptr)=con_all(2,con_base+l)
       end do

       goto 11
       end if

      end do        ! do k=ipos_from,ipos_to

11  continue   ! do j=1,nelem_tmp

  end if   ! if(procbuf(i) .ne. 0 .and. mypeid+1 .ne. i)
  end do   ! do i=1,nprocs

end if  ! if(nelem_ex .eq. 0) then ..... 

!-------------- end of making enptr_ex,con_ex,matno_ex

!-----------------------------
! mkexnode
!-----------------------------

! count nouter with DUPLICATION

nouter = 0

do i=1,nelem              ! search other PE's node in my elements
 ipos_from = enptr(1,i  )
 ipos_to   = enptr(1,i+1)-1
 do j=ipos_from,ipos_to
  if(con(2,j) .ne. mypeid) nouter = nouter + 1
 end do
end do

do i=1,nelem_ex                ! search other N in other E
 ipos_from = enptr_ex(1,i  )
 ipos_to   = enptr_ex(1,i+1)-1
 do j=ipos_from,ipos_to
   if(con_ex(2,j) .ne. mypeid) nouter = nouter + 1
 end do
end do

! allocate  ndno,peno, and x,y, fem variables(PROBLEM DEPENDENT)
if(nouter .eq. 0) then

  nullify(ndno,peno,ipf_ex,ipd_ex)
  nullify(x_ex,y_ex)
  nullify(fem_v_ex)

else

  allocate(ndno(nouter),peno(nouter))
!
! fix duplication
!
  iptr = 0

  do i=1,nelem          ! make outer node list with my elements
   ipos_from = enptr(1,i  )
   ipos_to   = enptr(1,i+1)-1
   do 21 j=ipos_from,ipos_to
    if(con(2,j) .ne. mypeid) then
      do k=1,iptr
       if(ndno(k)==con(1,j) .and. peno(k)== con(2,j)) goto 21
      end do
      iptr = iptr + 1
      ndno(iptr) = con(1,j)
      peno(iptr) = con(2,j)
    end if
21 continue 
  end do

  do i=1,nelem_ex                  ! make outer node list
   ipos_from = enptr_ex(1,i  )
   ipos_to   = enptr_ex(1,i+1)-1
   do 22 j=ipos_from,ipos_to
    if(con_ex(2,j) .ne. mypeid) then
     do k=1,iptr
      if(ndno(k)==con_ex(1,j) .and. peno(k)==con_ex(2,j)) goto 22
     end do
     iptr = iptr + 1
     ndno(iptr) = con_ex(1,j)
     peno(iptr) = con_ex(2,j)
    end if  
22 continue
  end do

! reallocation peno/ndno
  allocate( ipf_ex(iptr), ipd_ex(iptr))
  do i=1,iptr
    ipf_ex(i) = ndno(i)
    ipd_ex(i) = peno(i)
  end do

!-------------
! real nouter 
!-------------
  nouter = iptr

  deallocate( ndno,peno )
  allocate  ( ndno(nouter),peno(nouter))

  do i=1,nouter
    ndno(i)=ipf_ex(i)
    peno(i)=ipd_ex(i)
  end do
  deallocate( ipf_ex,ipd_ex )

! make ipf_ex,ipd_ex, and external fem variables

  allocate(ipf_ex(nouter),ipd_ex(nouter))    ! ipf, ipd
  allocate(x_ex(nouter),y_ex(nouter))        ! coordinates
  allocate(fem_v_ex(nouter))

  do 31 i=1,nouter
    do j=1,nd_allcounts
      if(ndno(i)==nodeno_all(j) .and. peno(i)==peno_all(j)) then
        ipf_ex(i)    = ipf_all(j)
        ipd_ex(i)    = ipd_all(j)
        x_ex(i)      = x_all(j)
        y_ex(i)      = y_all(j)
        fem_v_ex(i) = fem_v_all(j)
        goto 31
      endif
    end do
    write(*,*) 'ERROR: Not found outer node'
    write(*,*) 'pe,no=',peno(i),ndno(i),' i=',i
    call abortexit(myrank)
31 continue

endif              !if(nouter.eq.0)

!----------------------------------
! Deallocation
!---------------------------------
deallocate(nflag,eflag)
if(associated(enptr_send)) then
  deallocate(enptr_send,con_send,matno_send)
endif
deallocate(nodeno_send)
deallocate(ipf_send,ipd_send)
deallocate(x_send,y_send)
deallocate(x_all ,y_all )
deallocate(peno_all,ipf_all,ipd_all)
deallocate(fem_v_send,fem_v_all)

end subroutine mksolve1extdata
end module mod_mksolve1extdata
