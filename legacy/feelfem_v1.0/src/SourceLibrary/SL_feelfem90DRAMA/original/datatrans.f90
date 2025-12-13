module datatrans


contains

subroutine initbcast(myrank,nprocs,                                     &
                     ndim,npmax,npmax_g,nelem_g,nedat,nnset,nnum,nip,   &
                     mode_ex,mode_output,nvars_fem,nvars_ewise,         &
                     x,y,                                               &
                     firstEdatPtr,firstNsetPtr,ipData,                  &
                     metis                                               ) 
use numeric
use femDataType

implicit none

include 'mpif.h'

! feel_dat fundamental parameters
integer                        :: myrank,nprocs


integer(kind=INT4 )            :: ndim             ! space dimension
integer(kind=INT4 )            :: npmax            ! nodes(global/local)
integer(kind=INT4 )            :: npmax_g
integer(kind=INT4 )            :: nelem_g          ! number of region element
integer(kind=INT4 )            :: nedat
integer(kind=INT4 )            :: nnset
integer(kind=INT4 )            :: nnum
integer(kind=INT4 )            :: nip

integer(kind=INT4 )            :: mode_ex
integer(kind=INT4 )            :: mode_output
integer(kind=INT4 )            :: nvars_fem,nvars_ewise

real   (kind=REAL8),dimension(:),pointer :: x,y

type(edatList),pointer         :: firstEdatPtr
type(nsetList),pointer         :: firstNsetPtr
type(ipdat),   pointer         :: ipData

integer,dimension(:),pointer   :: metis
!-----------------------
! Auto variable
!-----------------------
integer                        :: i
integer                        :: ierror

! ------------
! EDAT/NSET/IP
! ------------
integer                        :: no
integer                        :: np

! ----
! EDAT
! ----
type(edat), pointer            :: edatData
type(edatList),pointer         :: currentEdatPtr,edatPtr

integer(kind=INT4 )            :: netype
integer,dimension(:,:),pointer :: ielem             ! for reading
integer,dimension(:)  ,pointer :: matno             ! for reading

integer                        :: nelem

! ----
! NSET
! ----
type(nset), pointer            :: nsetData
type(nsetList),pointer         :: currentNsetPtr,nsetPtr

integer,dimension(:,:),pointer :: inset
integer                        :: nodes


! ----
! IP
! ----
integer,dimension(:),pointer   :: ipno                        



!-----------------------
! Message passing
!-----------------------
call MPI_BCAST(ndim   ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(npmax  ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(nelem_g,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(nedat  ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(nnset  ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(nnum   ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(nip    ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(mode_ex,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(mode_output,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(nvars_fem,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(nvars_ewise,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)

! parallel
npmax_g = npmax

! NODE
if(myrank .ne. 0) then
  allocate(x(npmax),y(npmax))
endif
call MPI_BCAST(x   ,npmax,MPI_DOUBLE_PRECISION,0,MPI_COMM_WORLD,ierror)
call MPI_BCAST(y   ,npmax,MPI_DOUBLE_PRECISION,0,MPI_COMM_WORLD,ierror)

! EDAT

do i=1,nedat
 if(myrank .eq. 0) then
   if(i .eq. 1) then
    edatPtr => firstEdatPtr
   else
    edatPtr => edatPtr%next
   endif

   edatData =>edatPtr%edatData

   no     = edatData%no
   nelem  = edatData%nelem
   np     = edatData%np
   netype = edatData%netype
 endif

 call MPI_BCAST(no    ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
 call MPI_BCAST(nelem ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
 call MPI_BCAST(np    ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
 call MPI_BCAST(netype,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)

 if(myrank .eq. 0) then

   ielem => edatData%ielem
   matno => edatData%matno

 else

   allocate(edatData,edatPtr,ielem(np,nelem),matno(nelem))

   edatData%ielem => ielem
   edatData%matno => matno
   edatData%no    =  no
   edatData%np    =  np
   edatData%nelem =  nelem
   edatData%netype=  netype

   edatPtr%no       =  no
   edatPtr%edatData => edatData 
   nullify(edatPtr%next)

   if(i .eq. 1) then
    firstEdatPtr=>edatPtr
    currentEdatPtr=>edatPtr
   else
    currentEdatPtr%next =>edatPtr
    currentEdatPtr      =>edatPtr
   endif
 endif

 call MPI_BCAST(ielem,np*nelem,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
 call MPI_BCAST(matno,   nelem,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
 end do


! NSET

do i=1,nnset
 if(myrank .eq. 0) then
  if(i .eq. 1) then
    nsetPtr => firstNsetPtr
  else
    nsetPtr => nsetPtr%next
  endif

  nsetData => nsetPtr%nsetData

  no   = nsetData%no
  np   = nsetData%np
  nodes= nsetData%nodes
 endif

 call MPI_BCAST(no    ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
 call MPI_BCAST(np    ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
 call MPI_BCAST(nodes ,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)

 if(myrank .eq. 0 ) then

  inset => nsetData%inset

 else

  allocate(nsetData,nsetPtr,inset(np,nodes))
  nsetData%inset => inset
  nsetData%no    =  no
  nsetData%np    =  np
  nsetData%nodes =  nodes

  nsetPtr%no     =  no
  nsetPtr%nsetData => nsetData
  nullify(nsetPtr%next)

  if(i .eq. 1) then
   firstNsetPtr =>nsetPtr
   currentNsetPtr=>nsetPtr
  else
   currentNsetPtr%next =>nsetPtr
   currentNsetPtr      =>nsetPtr
  endif
 endif
 
 call MPI_BCAST(inset ,np*nodes,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)

 end do

! IP
 if(nip .ne. 0) then
  if(myrank .eq. 0) then
    ipno => ipData%ipno
  else
    allocate(ipData,ipno(nip))
    ipData%ipno  => ipno
    ipData%nodes =  nip
  endif
  call MPI_BCAST(ipno,nip,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)
 endif

! Metis
 if(myrank .ne. 0) then
   allocate(metis(nelem_g))
 endif
 call MPI_BCAST(metis,nelem_g,MPI_INTEGER,0,MPI_COMM_WORLD,ierror)


end subroutine initbcast

end module datatrans
