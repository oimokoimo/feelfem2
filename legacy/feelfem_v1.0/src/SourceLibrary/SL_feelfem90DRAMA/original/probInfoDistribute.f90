module mod_probInfoDistribute
!
! two distribute subroutines
!
! matInitDistribute      material and initial value distribute
! probInfoDistribute     mesh data information and solve information distribute
!
!
contains

subroutine matInitDistribute(myrank,nprocs,numData,matData)
!--------------------------------------------------
! Distribute meshDat and solveLst information
! 
! Date        : 2003/02/19
! Programmer  : Hidehiro Fujio
!--------------------------------------------------
  use numeric
  use femDataType

  implicit none

  include 'mpif.h'

  integer                               :: myrank,nprocs

  type(numdat),pointer                  :: numData
  type(matDat),pointer                  :: matData

  integer                               :: nnum
  integer                               :: regions


  integer                               :: i
  integer                               :: onflag
  integer,dimension(:),pointer          :: ibuf
  real(kind=REAL8),dimension(:),pointer :: dbuf

  integer                               :: ierr

!--------------- 
! for numDat
!--------------- 
  onflag = 0

  if(myrank .eq. 0) then
     if(associated(numData)) then
        onflag = 1
     end if
  end if
  
  call MPI_BCAST(onflag,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
  
  if(onflag .eq. 1) then   ! numData exists
     
     if(myrank .eq. 0) then
        nnum = numData%numbers
     end if

     call MPI_BCAST(nnum,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)

     if(myrank .eq. 0) then
        dbuf =>numData%dat
     else
        allocate(numData,dbuf(nnum))
        numData%numbers = nnum
        numData%dat     =>dbuf
     end if

     call MPI_BCAST(dbuf,nnum,MPI_DOUBLE_PRECISION,0,MPI_COMM_WORLD,ierr)
     
  end if

!--------------- 
! for matDat
!--------------- 
  onflag = 0

  if(myrank .eq. 0) then
     if(associated(matData)) then
        onflag = 1
     end if
  end if
  
  call MPI_BCAST(onflag,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
  
  if(onflag .eq. 1) then   ! matData exists
     
     if(myrank .eq. 0) then
        regions = matData%regions
     end if

     call MPI_BCAST(regions,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)

     if(myrank .eq. 0) then 
        ibuf =>matData%regmat
     else
        allocate(matData,ibuf(regions))
        matData%regions = regions
        matData%regmat  =>ibuf
     end if

     call MPI_BCAST(ibuf,regions,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
     
  end if

end subroutine matInitDistribute

subroutine probInfoDistribute(myrank,nprocs,meshDat,solveLst)

!--------------------------------------------------
! Distribute meshDat and solveLst information
! 
! Date        : 2003/02/17,18
! Programmer  : Hidehiro Fujio
!--------------------------------------------------
  
  use femDataType

  implicit none

  include 'mpif.h'

  integer                        :: myrank,nprocs

  type(meshInformation)          :: meshDat
  type(solveList)                :: solveLst

  ! Informations to transfer

  type(solveInformation),pointer :: solveInfoPtr
  type(solveInformation), &
       dimension(:),pointer      :: solveDataList

  integer                        :: medtNo       ! meshDat%medtNo
  integer                        :: mainEdatNo   ! meshDat%mainEdatNo
  integer                        :: regionEdats  ! mesh
  integer                        :: nredat
  integer                        :: nbedat
  integer                        :: solves
  integer                        :: solveNo,edatno,solveEdatNo,dconds,nconds
  integer                        :: condNo,datasets
  
  type(boundaryDataSet),dimension(:),pointer :: dlst 
  type(boundaryDataSet),dimension(:),pointer :: nlst
  type(boundaryDataSet),pointer              :: bdsetPtr

  ! auto variables

  integer                        :: i,j
  integer                        :: ierr
  integer,dimension(:),pointer   :: ibuf
  integer,dimension(:),pointer   :: isendbuf
  integer,dimension(:),pointer   :: irecvbuf
  
  !==========================================================
  ! meshData scatter distribution
  !==========================================================

  if(myrank .EQ. 0) then
     medtNo     = meshDat%medtNo
     mainEdatNo = meshDat%mainEdatNo
     nredat     = meshDat%regionEdats
     nbedat     = meshDat%boundaryEdats
  end if

  call MPI_BCAST(medtNo,     1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
  call MPI_BCAST(mainEdatNo, 1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
  call MPI_BCAST(nredat    , 1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
  call MPI_BCAST(nbedat    , 1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
  
  if(myrank .NE. 0) then
     meshDat%medtNo        = medtNo    
     meshDat%mainEdatNo    = mainEdatNo 
     meshDat%regionEdats   = nredat     
     meshDat%boundaryEdats = nbedat     
  end if

  if(nredat .NE. 0) then
     
     if(myrank .EQ. 0) then
        ibuf => meshDat%redatlist
     else
        allocate( ibuf(nredat) )
     end if

     call MPI_BCAST(ibuf,nredat,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)

     if(myrank .NE. 0) then
        meshDat%redatlist => ibuf
     end if

  end if


  if(nbedat .NE. 0) then
     
     if(myrank .EQ. 0) then
        ibuf => meshDat%bedatlist
     else
        allocate( ibuf(nredat) )
     end if

     call MPI_BCAST(ibuf,nredat,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
     
     if(myrank .NE. 0) then
        meshDat%bedatlist => ibuf
     end if

  end if
  

  !==========================================================
  ! solve Data scatter distribution
  !==========================================================  
  if(myrank .EQ. 0) then
     solves = solveLst%solves
  end if

  call MPI_BCAST(solves , 1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)

  if(myrank .EQ. 0) then
     solveDataList => solveLst%solveDataList    ! myrank has already
  else
     solveLst%solves = solves
     allocate(solveDataList(solves))            ! others allocate
     solveLst%solveDataList => solveDataList
  end if

  ! scatter each solves
  
  do i=1,solves
     
     if(myrank .EQ. 0) then
        
        solveInfoPtr =>solveDataList(i)

        solveNo = solveInfoPtr%solveNo
        edatno  = solveInfoPtr%edatNo
        dconds  = solveInfoPtr%dconds
        nconds  = solveInfoPtr%nconds

     end if

     call MPI_BCAST(solveNo,     1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
     call MPI_BCAST(edatno,      1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
     call MPI_BCAST(dconds,      1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
     call MPI_BCAST(nconds,      1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)

     if(myrank .NE. 0) then
        solveInfoPtr =>solveDataList(i)

        solveInfoPtr%solveNo =solveNo 
        solveInfoPtr%edatNo = edatno
        solveInfoPtr%dconds = dconds
        solveInfoPtr%nconds = nconds
     end if

     !------------------------
     ! dirichlet condition
     !------------------------
     if(dconds > 0) then

        ! dlst is type(boundaryDataSet),dimension(:),pointer
        if(myrank .EQ. 0) then
           dlst => solveInfoPtr%dlst
        else 
           allocate(dlst(dconds))
           solveInfoPtr%dlst =>dlst
        end if

        do j=1,dconds
           
           bdsetPtr => dlst(j)   ! bdsetPtr
           
           if(myrank .EQ. 0) then
              condNo   =  bdsetPtr%condNo
              datasets =  bdsetPtr%nofsets
           endif

           call MPI_BCAST(condNo,   1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
           call MPI_BCAST(datasets, 1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
           
           if(myrank .EQ. 0) then
              ibuf     => bdsetPtr%datlist   ! size is datasets
           else
              allocate(ibuf(datasets))       ! size is datasets
           end if
              
           call MPI_BCAST(ibuf,datasets,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
           

           if(myrank .NE. 0) then
              bdsetPtr%solveNo  = solveNo
              bdsetPtr%condNo   = condNo
              bdsetPtr%condType = 1          ! dcond = 1 , ncond = 2
              bdsetPtr%nofsets  = datasets
              bdsetPtr%datlist  =>ibuf
           end if

        end do  ! do j=1,dconds

     end if  ! if(dconds > 0)


     !------------------------
     ! neumann condition
     !------------------------
     if(nconds > 0) then

        ! dlst is type(boundaryDataSet),dimension(:),pointer
        if(myrank .EQ. 0) then
           nlst => solveInfoPtr%nlst
        else 
           allocate(nlst(nconds))
           solveInfoPtr%nlst =>nlst
        end if

        do j=1,nconds
           
           bdsetPtr => nlst(j)   ! bdsetPtr
           
           if(myrank .EQ. 0) then
              condNo   =  bdsetPtr%condNo
              datasets =  bdsetPtr%nofsets
           endif

           call MPI_BCAST(condNo,   1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
           call MPI_BCAST(datasets, 1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
           
           if(myrank .EQ. 0) then
              ibuf     => bdsetPtr%datlist   ! size is datasets
           else
              allocate(ibuf(datasets))       ! size is datasets
           end if
              
           call MPI_BCAST(ibuf,datasets,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
           

           if(myrank .NE. 0) then
              bdsetPtr%solveNo  = solveNo
              bdsetPtr%condNo   = condNo
              bdsetPtr%condType = 2          ! dcond = 1 , ncond = 2
              bdsetPtr%nofsets  = datasets
              bdsetPtr%datlist  =>ibuf
           end if

        end do  ! do j=1,nconds

     end if  ! if(nconds > 0)

  end do  ! do i=1,solves

end subroutine probInfoDistribute
end module mod_probInfoDistribute
           
           
        
