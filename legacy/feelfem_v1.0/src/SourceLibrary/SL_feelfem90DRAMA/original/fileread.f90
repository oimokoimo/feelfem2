module fileread
!
! For aistpcp90 ProgramModel  2002/07/02
!
! METIS epart data read  
! readmetis
!
!
integer,parameter,private   :: ioin  = 10            ! Read open unit number

contains

subroutine readmetis(myrank,nprocs,nelem_g,iedom)
use numeric
implicit none

integer,intent(in)           :: myrank
integer,intent(in)           :: nprocs
integer,intent(in)           :: nelem_g      ! total number of element
integer,dimension(:),pointer :: iedom        ! metis elementwise partition data
 
integer                      :: nelem        ! read element data
character(len=50)            :: filename

integer                      :: i
!------------------------------------------------------------------
  if(nprocs < 10) then
     write(filename,7801) nprocs
7801 format('feel.metis.epart.',i1)
  else if(nprocs < 100) then
     write(filename,7802) nprocs
7802 format('feel.metis.epart.',i2)
  else if(nprocs < 1000) then
     write(filename,7803) nprocs
7803 format('feel.metis.epart.',i3)
  else
     write(*,*) 'too many partitions.'
     stop
  endif

  
  open(file=filename,unit=ioin,status='old',err=9999)
  do i=1,nelem_g
     read(ioin,*) iedom(i)
  end do
  
  close(ioin)
  return

9999 continue

  write(*,*) '***************************************************'
  write(*,9998) nprocs
9998 format( '*  Number of Processors =',i4,'                      *')
  write(*,*) '*  Cannot open METIS partition file.              *'
  write(*,*) '*                                                 *'
  write(*,*) '*                                                 *'
  write(*,*) '*  Appropriate METIS partition file must be made. *'
  write(*,*) '*                                                 *'
  write(*,*) '***************************************************'

  stop 'reading metis partition data(readmetis routine)'
  

end subroutine readmetis

subroutine ctrlinp(meshDat, solveLst,ierror)
use femDataType
use numeric
implicit none

type(meshInformation)        :: meshDat
type(solveList)              :: solveLst
integer                      :: ierror


!-------------------------------------------
! Auto variables
!-------------------------------------------
integer                        :: i,j,k

character(len = 4)             :: word

! Input buffer pointer

integer,dimension(:),pointer   :: inpbuf

! for Mesh information
integer                        :: nredat,nbedat

! for Solve information
integer                        :: solves
type(solveInformation),pointer :: solveInfoPtr
type(solveInformation), &
    dimension(:),pointer       :: solveDataList

integer                        :: solveNo
integer                        :: solveEdatNo
integer                        :: dconds
integer                        :: nconds

integer                        :: condNo
integer                        :: condFlag
integer                        :: datasets

type(boundaryDataSet),dimension(:),pointer :: dlst
type(boundaryDataSet),dimension(:),pointer :: nlst

type(boundaryDataSet),pointer  :: bdsetPtr
!-------------------------------
ierror = Non

open(ioin,file='solv_dat',status='old',action='read')

!----------------
! PROB Keyword 
!----------------
read(ioin,'(a4)') word
if(word .ne. 'PROB') then
  ierror = Oui
  close(ioin)
  write(*,*) 'solve_dat DATA ERR(KEYWORD PROB NOT FOUND)'
  return
endif

!----------------
! MEDT  Main edat
!----------------
read(ioin,'(a4)') word
if(word .ne. 'MEDT') then
  ierror = Oui
  close(ioin)
  write(*,*) 'solve_dat DATA ERR(KEYWORD MEDT NOT FOUND)'
  return
endif


read(ioin,'(i8)')    meshDat%medtNo     ! medtNo     is main EDAT for GiD
meshDat%mainEdatNo = meshDat%medtNo     ! mainEdatNo is used in let sentences

!-----------------
! REDT Region edat
!-----------------
read(ioin,'(a4)') word
if(word .ne. 'REDT') then
  ierror = Oui
  close(ioin)
  write(*,*) 'solve_dat DATA ERR(KEYWORD REDT NOT FOUND)'
  return
endif

read(ioin,'(i8)') nredat
allocate(inpbuf(nredat))
meshDat%regionEdats =  nredat
meshDat%redatlist   => inpbuf

read(ioin,'((8i8))') (inpbuf(i),i=1,nredat)

!-------------------
! BEDT Boundary edat
!-------------------
read(ioin,'(a4)') word
if(word .ne. 'BEDT') then
  ierror = Oui
  close(ioin)
  write(*,*) 'solve_dat DATA ERR(KEYWORD BEDT NOT FOUND)'
  return
endif

read(ioin,'(i8)') nbedat
meshDat%boundaryEdats =  nbedat

if(nbedat .ne. 0) then
  allocate(inpbuf(nbedat))
  meshDat%bedatlist     => inpbuf
  read(ioin,'((8i8))') (inpbuf(i),i=1,nbedat)
else
  nullify(meshDat%bedatlist)
endif

!-------------------------
! Solve information
!-------------------------
read(ioin,'(a4)') word
if(word .ne. 'SLVS') then
  ierror = Oui
  close(ioin)
  write(*,*) 'solve_dat DATA ERR(KEYWORD SLVS NOT FOUND)'
  return
endif

read(ioin,'(i8)') solves
solveLst%solves = solves

if(solves == 0) then
   close(ioin)
   return
end if

!----------------------
! Solve DATA repetition
!----------------------

allocate(solveDataList(solves))
solveLst%solveDataList => solveDataList

do i=1,solves


   ! SOLV
   read(ioin,'(a4)') word
   if(word .ne. 'SOLV') then
      ierror = Oui
      close(ioin)
      write(*,*) 'solve_dat DATA ERR. KEYWORD SOLV NOT FOUND for No.',i
      stop
   endif
   
   ! solveNo
   read(ioin,'(i8)') solveNo
   read(ioin,'(i8)') solveEdatNo
   read(ioin,'(i8)') dconds
   read(ioin,'(i8)') nconds

   solveInfoPtr => solveDataList(i)   ! memory is allocated

   solveInfoPtr%solveNo = solveNo
   solveInfoPtr%edatno  = solveEdatNo
   solveInfoPtr%dconds  = dconds
   solveInfoPtr%nconds  = nconds

   ! Dirichlet conds
   if(dconds > 0) then

      allocate(dlst(dconds))
      solveInfoPtr%dlst => dlst
      
      do j=1,dconds

         ! j-th DCND 
         read(ioin,'(a4)') word
         if(word .ne. 'DCND') then
            write(*,*) 'Data error DCND, solve No.',solveNo,' dcond No.',j
            stop
         endif

         bdsetPtr => dlst(j)

         read(ioin,'(2i8)') condNo,datasets
         
         allocate(inpbuf(datasets))
         bdsetPtr%solveNo   =  solveNo
         bdsetPtr%condType  =  1            ! dcond = 1  ncond = 2
         bdsetPtr%condNo    =  condNo
         bdsetPtr%nofsets   =  datasets
         bdsetPtr%datlist   => inpbuf
         
         read(ioin,'((8i8))') (inpbuf(k),k=1,datasets)

      end do  ! end of dconds loop

   end if  ! end of if(dcond >0)


   ! Neumann conds
   if(nconds > 0) then

      allocate(nlst(nconds))
      solveInfoPtr%nlst => nlst
      
      do j=1,nconds

         ! j-th NCND
         read(ioin,'(a4)') word
         if(word .ne. 'NCND') then
            write(*,*) 'Data error NCND, solve No.',solveNo,' ncond No.',j
            stop
         endif

         bdsetPtr => nlst(j)  

         read(ioin,'(2i8)') condNo,datasets
         
         allocate(inpbuf(datasets))
         bdsetPtr%solveNo   =  solveNo
         bdsetPtr%condType  =  2            ! dcond = 1  ncond = 2
         bdsetPtr%condNo    =  condNo
         bdsetPtr%nofsets   =  datasets
         bdsetPtr%datlist   => inpbuf
         
         read(ioin,'((8i8))') (inpbuf(k),k=1,datasets)

      end do  ! end of nconds loop

   end if  ! end of if(ncond >0)
   
end do
   
close(ioin) 
return

end subroutine ctrlinp
  

subroutine datinp(ndim,npmax,nelem_g,nedat,nnset,nnum,nip,           &
                  mode_ex,mode_output,nvars_fem,nvars_ewise,         &
                  x,y,z,                                             &
                  firstEdatPtr,firstNsetPtr,numData,ipData ,matData, &
                  ierror  )

use numeric
use femDataType
implicit none

! feel_dat fundamental parameters

integer(kind=INT4 )            :: ndim             ! space dimension 
integer(kind=INT4 )            :: npmax            ! nodes(global/local)
integer(kind=INT4 )            :: nelem_g          ! number of region element
integer(kind=INT4 )            :: nedat
integer(kind=INT4 )            :: nnset
integer(kind=INT4 )            :: nnum
integer(kind=INT4 )            :: nip
!
integer(kind=INT4 )            :: mode_ex
integer(kind=INT4 )            :: mode_output
integer(kind=INT4 )            :: nvars_fem,nvars_ewise

real   (kind=REAL8),dimension(:),pointer :: x,y,z

type(edatList),pointer         :: firstEdatPtr
type(nsetList),pointer         :: firstNsetPtr
type(numdat)  ,pointer         :: numData
type(ipdat)   ,pointer         :: ipData
type(matdat)  ,pointer         :: matData

integer(kind=INT4 )            :: ierror

!---------------------------------------------------------------
! Auto variable
!---------------------------------------------------------------

integer                        :: i,j

! --------
! feel_dat
! --------
character(len = 4 )            :: word                       ! feel_dat keyword
integer                        :: nodeFlag,edatFlag,nsetFlag

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
! NODE
! ----
integer                                  :: inp
real   (kind=REAL8)                      :: xx,yy,zz          ! for reading


! ----
! NUM
! ----
real(kind=REAL8) ,dimension(:),pointer   :: ndat


! ----
! IP
! ----
integer,dimension(:),pointer             :: ipno

! ----
! REGN
! ----
integer                                  :: regions
integer,dimension(:),pointer             :: regmat


!-----------------------
! Read feel_dat datafile
!-----------------------
  ierror = Non

  open(ioin,file='feel_dat',status ='old',action='read')

  read(ioin,'(a4)') word
  if(word .ne. 'FEEL') then
    write(*,*) 'First keyword is not FEEL'
    ierror = Oui
    close(ioin)
    return
  endif
!
  read(ioin,'(6i8)') ndim,npmax,nedat,nnset,nnum,nip
  read(ioin,'(2i8)') mode_ex,mode_output
  read(ioin,'(2i8)') nvars_fem,nvars_ewise

  nodeFlag = notYet
  edatFlag = notYet
  nsetFlag = notYet
!
  nullify(firstNsetPtr,firstEdatPtr,ipData)

!

1000 read(ioin,'(a4)') word

  select case(word)
   case('END ') 
     goto 1999

   case('NODE') 
     if(nodeFlag == already) then
       write(*,*)'NODE section duplicate'
       ierror = Oui
       close(ioin)
       return
     endif
     nodeFlag = already

     if( ndim == 1 ) then
        allocate(x(npmax))
1001    read(ioin,'(i8,E12.5)') inp,xx
        if(inp .ne. 0) then
           x(inp) = xx; goto 1001
        endif
     endif
     
     if( ndim == 2 ) then
        allocate(x(npmax),y(npmax))
1002    read(ioin,'(i8,E12.5,E12.5)') inp,xx,yy
        if(inp .ne. 0) then
           x(inp)=xx; y(inp)=yy; goto 1002
        endif
     endif

     if( ndim == 3 ) then
        allocate(x(npmax),y(npmax),z(npmax))
1003    read(ioin,'(i8,E12.5,E12.5,E12.5)') inp,xx,yy,zz
        if(inp .ne. 0) then
           x(inp)=xx; y(inp)=yy; z(inp)=zz; goto 1003
        endif
     endif

   case('EDAT') 
     read(ioin,'(4i8)') no,nelem,np,netype

     if(no .eq. 1) then
       nelem_g = nelem         ! feel_dat limitation
     endif
     if(netype == 0) then
        write(*,*) 'Warning: netype(element type) for EDAT ',no,' is 0'
     end if

     allocate(edatData,edatPtr,ielem(np,nelem),matno(nelem))
     edatData%ielem => ielem
     edatData%matno => matno
     edatData%no    =  no
     edatData%nelem =  nelem
     edatData%np    =  np
     edatData%netype=  netype

     edatPtr%no       =  no             ! List pointer has also no. data
     edatPtr%edatData => edatData
     nullify(edatPtr%next)
     
   
     if(edatFlag == notYet) then
       firstEdatPtr=>edatPtr
       currentEdatPtr=>edatPtr
       edatFlag  = already 
     else
       currentEdatPtr%next =>edatPtr
       currentEdatPtr=>edatPtr
     endif
    

     do i=1,nelem
      read(ioin,*) (ielem(j,i),j=1,np),matno(i)
     end do



   case('NSET') 
     read(ioin,'(3i8)') no,nodes,np

     allocate(nsetData,nsetPtr,inset(np,nodes))
     nsetData%inset   =>inset
     nsetData%no      = no
     nsetData%np      = np
     nsetData%nodes   = nodes

     nsetPtr%no       = no
     nsetPtr%nsetData => nsetData
     nullify(nsetPtr%next)

     if(nsetFlag == notYet) then
       firstNsetPtr   => nsetPtr
       currentNsetPtr => nsetPtr
       nsetFlag       =  already
     else
       currentNsetPtr%next => nsetPtr
       currentNsetPtr      => nsetPtr
     endif

     do i=1,nodes
       read(ioin,*) (inset(j,i),j=1,np)
     end do



   case('NUM ') 
     allocate(numData,ndat(nnum))
     
     numData%dat     => ndat
     numData%numbers =  nnum

     read(ioin,'((E15.5))') (ndat(i),i=1,nnum)

  case('IP  ') 
     allocate(ipData,ipno(nip))

     ipData%ipno     => ipno
     ipData%nodes    =  nip

     read(ioin,'((8i8))') (ipno(i),i=1,nip)

  case('REGN') 

     read(ioin,'(i8)') regions
     allocate(matData,regmat(regions))

     matData%regions =  regions
     matData%regmat  => regmat

     read(ioin,'((i8))') (regmat(i),i=1,regions)


  end select

  goto 1000 
   

1999 close(ioin)

end subroutine datinp

subroutine read_metis(nprocs,nelem_g,metis,ierror)
!---
use numeric
implicit none

integer                    :: nprocs
integer                    :: nelem_g
integer,dimension(nelem_g) :: metis
integer                    :: ierror

!auto variable
integer                    :: i
integer                    :: inp
integer                    :: nprocs_check
integer                    :: metis2feel(nelem_g)
!---

  ierror = Non

  open(ioin,file='metis.bamg',status='old',action='read')
  do i=1,nelem_g
    read(ioin,*) metis2feel(i)
  end do
  close(ioin)

  open(ioin,file='metis.feel',status='old',action='read')
  do i=1,nelem_g
    read(ioin,*) inp
    metis(inp) = metis2feel(i)
  end do
  close(ioin)

  nprocs_check = -1
  do i=1,nelem_g
    if(nprocs_check < metis(i)) then
      nprocs_check = metis(i)
    end if
  end do
  nprocs_check = nprocs_check + 1

  if(nprocs .ne. nprocs_check) then
    write(*,*) 'Number of processor is mismatch'
    ierror = Oui
    return
  endif

end subroutine read_metis

end module fileread
