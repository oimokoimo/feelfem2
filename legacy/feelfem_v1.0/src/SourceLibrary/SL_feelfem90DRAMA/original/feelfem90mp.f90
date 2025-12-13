module feelfem90mp
!--------------------------------------------------------
! Message passing sub module for feelfem90
!
! subroutine ff90gathervbcast    ! for 1-dimensional array
! subroutine ff90gathervbcast2   ! for 2-dimensional array
!                                ! counts,displs are divided by np
!
!
!--------------------------------------------------------

contains
subroutine ff90allgather(myrank,nprocs,count,mybuf,buf   )
!
! allocate receive buffer and calls mpi_allgather
!
use abortmodule
implicit none
!
include 'mpif.h'
!
integer,intent(in)           :: myrank,nprocs
integer,intent(in)           :: count
integer,dimension(:)         :: mybuf
integer,dimension(:),pointer :: buf              ! allocate here

!auto variable
integer                      :: ierror



if(count .le. 0) then
  write(*,*) '[ff90allgather] count =',count
  call abortexit(myrank)
endif

allocate(buf(nprocs*count))
call MPI_ALLGATHER(mybuf,count,MPI_INTEGER,               &
                   buf  ,count,MPI_INTEGER,MPI_COMM_WORLD,ierror)

!
end subroutine ff90allgather

subroutine ff90gathervbcast(myrank,nprocs,mycount,mybuf, &
                            buf,counts,displs            )
use abortmodule
implicit none
!
include 'mpif.h'
!
integer,intent(in)           :: myrank,nprocs
integer,intent(in)           :: mycount
integer,dimension(:),pointer :: mybuf
integer,dimension(:),pointer :: buf              ! allocate here
integer,dimension(:),pointer :: counts           ! allocate here
integer,dimension(:),pointer :: displs           ! allocate here 

! auto variables

integer                      :: i                ! for loop counter
integer                      :: idisp,nwords     ! for counting
integer                      :: ierror


!------


if(mycount < 0) then
  write(*,*) '[ff90gathervbcast] myrank=',myrank,' mycount=',mycount
  call abortexit(myrank)
endif

!if(mycount == 0) then
!  allocate(sendbuffer(2))
!else
!  sendbuffer = mybuf
!endif 


allocate(counts(nprocs),displs(nprocs))

call MPI_GATHER(mycount,   1, MPI_INTEGER,         &
                counts ,   1, MPI_INTEGER, 0,      &
                              MPI_COMM_WORLD,ierror)
!----
! now only PE0 has counts(*) array
!----

if(myrank .eq. 0) then
  idisp = 0
  do i=1,nprocs
    displs(i) = idisp
    idisp = idisp + counts(i)
  end do
  nwords = idisp
endif

!---
! now only PE0 has displs(*) array
!---

! scatter buffer size nwords
call MPI_BCAST(nwords,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)

!allocate recieve buffer in each processor
allocate(buf(nwords))

! scatter counts/displs array
call MPI_BCAST(counts,nprocs,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(displs,nprocs,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)

! gather and scatter data

call MPI_GATHERV(mybuf,mycount,MPI_INTEGER,buf,counts,displs, &
                               MPI_INTEGER,  0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(buf,nwords,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)


!if(mycount == 0) then 
! deallocate(sendbuffer)
!endif 

end subroutine ff90gathervbcast


subroutine ff90gathervbcast2(myrank,nprocs,np,n,mybuf, &
                             buf,counts,displs            )
!
!  counts,displs are divided by np for 2-dimensional array
!
!
!
use abortmodule
implicit none
!
include 'mpif.h'
!
integer,intent(in)              :: myrank,nprocs
integer,intent(in)              :: np,n
integer,dimension(:,:) ,pointer :: mybuf
integer,dimension(:,:) ,pointer :: buf              ! allocate here

integer,dimension(:)   ,pointer :: counts           ! allocate here
integer,dimension(:)   ,pointer :: displs           ! allocate here 

! auto variables

integer                      :: i                ! for loop counter
integer                      :: idisp,nwords     ! for counting
integer                      :: ntimes
integer                      :: mycount
integer                      :: ierror

!integer,dimension(:,:) ,pointer :: sendbuffer       ! for PGI 
!integer,dimension(2,1)          :: tempbuffer

!------

mycount = np * n

if(mycount < 0) then
  write(*,*) '[ff90gathervbcast2] myrank=',myrank,' np=',np,' n=',n
  call abortexit(myrank)
endif

!if(mycount == 0) then
!  sendbuffer = mybuf
!else
!  allocate(sendbuffer(2,1))
!endif 


allocate(counts(nprocs),displs(nprocs))

call MPI_GATHER(mycount,   1, MPI_INTEGER,         &
                counts ,   1, MPI_INTEGER, 0,      &
                              MPI_COMM_WORLD,ierror)
!----
! now only PE0 has counts(*) array
!----

if(myrank .eq. 0) then
  idisp = 0
  do i=1,nprocs
    displs(i) = idisp
    idisp = idisp + counts(i)
  end do
  nwords = idisp
endif

!---
! now only PE0 has displs(*) array
!---

! scatter buffer size nwords
call MPI_BCAST(nwords,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)

!allocate recieve buffer in each processor
ntimes = nwords / np

if(ntimes * np  .ne. nwords) then
 write(*,*) 'calculation of ntimes illegal'
 call abortexit(myrank)
endif
 
allocate(buf(np,ntimes))


! scatter counts/displs array
call MPI_BCAST(counts,nprocs,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(displs,nprocs,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)

! gather and scatter data
call MPI_GATHERV(mybuf,mycount,MPI_INTEGER,buf,counts,displs, &
                               MPI_INTEGER,  0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(buf,nwords,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)

! Adjust for counts/displs for 2-dimensional array
do i=1,nprocs
 counts(i)=counts(i)/np
 displs(i)=displs(i)/np
end do


end subroutine ff90gathervbcast2


subroutine ff90gathervdbl(myrank,nprocs,npmax,ddat,dgatherbuf,npmax_g)
!--------------------------------------------------------------
! gatherv for double precision version
!
! dgatherbuf is allocated here, and must be free after use
!--------------------------------------------------------------
  use numeric

  implicit none

  include 'mpif.h'

  integer                               :: myrank,nprocs
  integer                               :: npmax
  real(kind=REAL8),dimension(:),pointer :: ddat
  
  real(kind=REAL8),dimension(:),pointer :: dgatherbuf  !allocate here

  integer                               :: npmax_g     ! all nodes

! auto variables
  integer                               :: i
  integer,dimension(:),pointer          :: counts,displs  ! allocate&deallocate
  integer                               :: ierr
  
!--------------------------------------
  npmax_g = 0

  if(myrank .eq. 0) then
     allocate(counts(nprocs))
     allocate(displs(nprocs))
  end if
  
  call MPI_GATHER(npmax , 1,MPI_INTEGER,                       &
                  counts, 1,MPI_INTEGER, 0, MPI_COMM_WORLD,ierr )
  
  if(myrank .eq. 0) then

     ! calculate npmax_g
     do i=1,nprocs
        npmax_g = npmax_g + counts(i)
     end do

     ! make displs array
     displs(1) = 0
     do i=2,nprocs
        displs(i) = displs(i-1)+counts(i-1)
     end do

     allocate(dgatherbuf(npmax_g))

  end if

  call MPI_GATHERV(ddat,npmax,MPI_DOUBLE_PRECISION,                &
                   dgatherbuf,counts,displs,MPI_DOUBLE_PRECISION,  &
                   0,MPI_COMM_WORLD,ierr                           )
  !

  deallocate(counts,displs)

  return
end subroutine ff90gathervdbl

end module feelfem90mp
