module dramaDataModel

!-------------------------------------------------------------
! subroutine lonumerate
! subroutine mkloccoor
! subroutine mkdramaedats
! subroutine mkdramansets
! subroutine setdramaedat
! subroutine setdramanset
!
! Date     2000/09/25
! Modified 2000/10/11
!-------------------------------------------------------------

contains

subroutine lonumerate(mypeid,nprocs,loc,npmax_g,metis,nelem_g, &
                      firstEdatPtr,mynode,myelem               )
!
! Purpose: Make a index list array for local enumeration
!   
!
!
!
!
!
use femDataType
use abortmodule

implicit none


integer,parameter           :: notYetFlag = -1
integer,parameter           :: NID_PLUS   =  1  ! mypeid and ID in array


integer,intent(in)          :: mypeid,nprocs
integer,intent(in)          :: npmax_g,nelem_g   ! total number of nodes,
                                             ! region elements
integer,dimension(2,npmax_g):: loc
integer,dimension(nelem_g)  :: metis
integer,intent(out)         :: mynode,myelem

type(edatList),pointer      :: firstEdatPtr

! auto variables

type(edatList),pointer         :: edatPtr
type(edat)    ,pointer         :: edatData
integer,dimension(:,:),pointer :: ielem
integer                        :: no,nelem,np

integer                        :: netype        ! P2 limitation

! 

integer,dimension(nprocs)      :: icount        ! count nodes for each PE region

integer                        :: i,j
integer                        :: id,ipt



!----
! initialization
!----
myelem    = 0
mynode    = 0 

do i=1,nprocs
  icount(i) = 0
end do

do i=1,npmax_g
  loc(1,i) = notYetFlag
  loc(2,i) = 0
end do

edatPtr => firstEdatPtr

make_loc_loop: do
  edatData => edatPtr%edatData
  
  if(edatData%nelem .eq. nelem_g) then  ! feel_dat data limitation
    ielem => edatData%ielem
    np    =  edatData%np
    nelem =  edatData%nelem 

    netype = edatData%netype            ! P2 limitation (one element)

    if(myelem .eq. 0) then
      do i=1,nelem
        if(metis(i) .eq. mypeid) then
          myelem = myelem + 1
        endif
      end do
    endif

    do i=1,nelem
      id = metis(i)
      do j=1,np

        ipt = ielem(j,i)

        if(loc(1,ipt) .eq. notYetFlag ) then
          loc(1,ipt) = id
        else
          if(loc(1,ipt) .GT. id ) then
             loc(1,ipt) = id
          endif
        endif
      end do
    end do
  end if

  if( .not. associated(edatPtr%next)) exit make_loc_loop
  edatPtr => edatPtr%next

end do make_loc_loop

! generate loc(2,*) 

  do i=1,npmax_g
    id = loc(1,i)
    if(id .eq. notYetFlag) then
      write(*,*) 'Error in lonumerate:001'
      call abortexit(mypeid)
    endif
    ipt = id + NID_PLUS
    
    icount(ipt) = icount(ipt)+1
    loc(2,i)    = icount(ipt)
  end do
  
  mynode = icount(mypeid + NID_PLUS)


end subroutine lonumerate
!----------------------------------------------------------------------
! for 2 dimension
!----------------------------------------------------------------------
subroutine mkloccoor(mypeid,nprocs,x,y,loc,npmax_g,xloc,yloc,mynode)
use numeric
use abortmodule
implicit none

integer                             :: mypeid
integer                             :: nprocs
integer                             :: npmax_g
integer                             :: mynode
integer,dimension(2,npmax_g)        :: loc
real(kind=REAL8),dimension(npmax_g) :: x,y 
real(kind=REAL8),dimension(mynode)  :: xloc,yloc

! auto variables
integer                             :: i,iptr

  iptr = 0
  do i=1,npmax_g
    if(loc(1,i) .eq. mypeid) then
      iptr       = iptr + 1
      xloc(iptr) = x(i)
      yloc(iptr) = y(i)
    end if
  end do  
  if(iptr .ne. mynode) then
    write(*,*) 'mkloccoor error'
    call abortexit(mypeid)
  end if

end subroutine mkloccoor
!----------------------------------------------------------------------
! for 3 dimension
!----------------------------------------------------------------------
subroutine mkloccoor3(mypeid,nprocs,x,y,Z,loc,npmax_g, &
                      xloc,yloc,zloc,mynode)
use numeric
use abortmodule
implicit none

integer                             :: mypeid
integer                             :: nprocs
integer                             :: npmax_g
integer                             :: mynode
integer,dimension(2,npmax_g)        :: loc
real(kind=REAL8),dimension(npmax_g) :: x,y,z
real(kind=REAL8),dimension(mynode)  :: xloc,yloc,zloc

! auto variables
integer                             :: i,iptr

  iptr = 0
  do i=1,npmax_g
    if(loc(1,i) .eq. mypeid) then
      iptr       = iptr + 1
      xloc(iptr) = x(i)
      yloc(iptr) = y(i)
      zloc(iptr) = z(i)
    end if
  end do  
  if(iptr .ne. mynode) then
    write(*,*) 'mkloccoor error'
    call abortexit(mypeid)
  end if

end subroutine mkloccoor3

subroutine mkdramaedats(mypeid,nprocs,loc,npmax_g,metis,nelem_g, &
                        mynode,myelem,firstEdatPtr,firstDramaEdatPtr)
use numeric
use femDataType
use abortmodule
implicit none

integer,intent(in)            :: mypeid,nprocs
integer,intent(in)            :: npmax_g
integer,dimension(2,npmax_g)  :: loc
integer,intent(in)            :: nelem_g
integer,dimension(nelem_g)    :: metis
integer,intent(in)            :: mynode,myelem
type(edatList),pointer        :: firstEdatPtr
type(dramaEdatList),pointer   :: firstDramaEdatPtr

! auto variables
integer                       :: isFirstDramaEdat   ! check the first edat
integer                       :: i,j
type(edatList),pointer        :: edatPtr
type(edat),pointer            :: edatData
type(dramaEdat),pointer       :: dramaEdatData
type(dramaEdatList),pointer   :: currentDramaEdatPtr,dramaEdatPtr

integer,dimension(:,:),pointer:: ielem
integer,dimension(:)  ,pointer:: matno,matno_new
integer,dimension(:,:),pointer:: enptr,con

integer                       :: no,np,nelem
integer                       :: netype              ! P2 limit
integer                       :: ieptr,ipos


edatPtr           => firstEdatPtr
isFirstDramaEdat  =  Oui

edat_convert_loop: do

  edatData =>edatPtr%edatData
  no     = edatData%no
  np     = edatData%np
  nelem  = edatData%nelem
  netype = edatData%netype
  
  allocate(dramaEdatData,dramaEdatPtr)

  ! the edat no is the same for global/local edat
  dramaEdatPtr%no            =  no
  dramaEdatData%no           =  no
                

  dramaEdatPtr%dramaEdatData => dramaEdatData
  nullify(dramaEdatPtr%next)

  if(isFirstDramaEdat .eq. Oui) then
    firstDramaEdatPtr   => dramaEdatPtr
    currentDramaEdatPtr => dramaEdatPtr
    isFirstDramaEdat = Non
  else
    currentDramaEdatPtr%next => dramaEdatPtr
    currentDramaEdatPtr      => dramaEdatPtr
  endif

  if(edatPtr%isRegion .eq. Oui) then    

    ! local EDAT
    allocate(matno_new(myelem),enptr(2,myelem+1),con(2,myelem*np))

    ! local edat = myelem
    dramaEdatData%nelem = myelem

    dramaEdatData%enptr =>enptr
    dramaEdatData%con   =>con
    dramaEdatData%matno =>matno_new

    dramaEdatData%netype = netype         ! P2 limit
  
    ielem => edatData%ielem
    matno => edatData%matno

    ieptr = 0
    ipos  = 1
    do i=1,nelem
      if(metis(i) .eq. mypeid) then
        ieptr            = ieptr + 1
        enptr(1,ieptr)   = ipos
        enptr(2,ieptr)   = NUR_ONE_ETYPE
        matno_new(ieptr) = matno(i)
  
        do j=1,np
          con(1,ipos+j-1) = loc(2,ielem(j,i))
          con(2,ipos+j-1) = loc(1,ielem(j,i))
        end do
        ipos = ipos + np
      end if
    end do



    if(myelem .ne. ieptr) then
      write(*,*) 'error in making local enptr '
      call abortexit(mypeid)
    endif

    ieptr          = ieptr + 1
    enptr(1,ieptr) = ipos


  else


    ! global EDAT
    allocate(matno_new(nelem) ,enptr(2,nelem+1) ,con(2,nelem*np))

    dramaEdatData%enptr =>enptr
    dramaEdatData%con   =>con
    dramaEdatData%matno =>matno_new
    dramaEdatData%nelem = nelem               ! Global edat
  
    ielem => edatData%ielem
    matno => edatData%matno

    ieptr = 0
    ipos  = 1
    do i=1,nelem
      ieptr            = ieptr + 1
      enptr(1,ieptr)   = ipos
      enptr(2,ieptr)   = NUR_ONE_ETYPE
      matno_new(ieptr) = matno(i)
  
      do j=1,np
        con(1,ipos+j-1) = loc(2,ielem(j,i))
        con(2,ipos+j-1) = loc(1,ielem(j,i))
      end do
      ipos = ipos + np
   
    end do

    ieptr          = ieptr + 1
    enptr(1,ieptr) = ipos

  endif

  if(.not. associated(edatPtr%next)) exit edat_convert_loop
  edatPtr => edatPtr%next

end do edat_convert_loop

end subroutine mkdramaedats

subroutine mkdramansets(mypeid,nprocs,loc,npmax_g,       &
                        firstNsetPtr,firstDramaNsetPtr )
use numeric
use femDataType
use abortmodule 
implicit none

integer                      :: mypeid,nprocs
integer                      :: npmax_g
integer,dimension(2,npmax_g) :: loc

type(nsetList),pointer       :: firstNsetPtr
type(dramaNsetList),pointer  :: firstDramaNsetPtr

! auto variables

integer                        :: i,j
integer                        :: no,nodes,np
integer,dimension(:,:),pointer :: inset
integer,dimension(:,:),pointer :: con,info
integer                        :: isFirstDramaNset
integer                        :: ipt

type(nsetList),pointer         :: nsetPtr
type(nset)    ,pointer         :: nsetData
type(dramaNsetList),pointer    :: dramaNsetPtr,currentDramaNsetPtr
type(dramaNset),pointer        :: dramaNsetData

!------------------------
nsetPtr          => firstNsetPtr
isFirstDramaNset =  Oui

nset_convert_loop: do
  nsetData => nsetPtr%nsetData
  no       =  nsetData%no
  np       =  nsetData%np
  nodes    =  nsetData%nodes


  allocate(dramaNsetData,dramaNsetPtr)
  dramaNsetPtr%dramaNsetData => dramaNsetData
  dramaNsetPtr%no            =  no

  nullify(dramaNsetPtr%next)

  if(isFirstDramaNset .eq. Oui) then
    firstDramaNsetPtr   => dramaNsetPtr
    currentDramaNsetPtr => dramaNsetPtr
    isFirstDramaNset    =  Non
  else
    currentDramaNsetPtr%next  => dramaNsetPtr
    currentDramaNsetPtr       => dramaNsetPtr
  endif

  allocate( con(2,nodes) )
  dramaNsetData%con    => con

  if(np > 1) then
    allocate( info(np-1,nodes) )
    dramaNsetData%info => info
  else
    nullify(dramaNsetData%info)
  endif

  dramaNsetData%no     =  no
  dramaNsetData%np     =  np-1             ! CAUTION!   np-1 
  dramaNsetData%nodes  =  nodes

  dramaNsetPtr%no      =  no

  inset => nsetData%inset

  do i=1,nodes
   ipt = inset(1,i)
   con(1,i) = loc(2,ipt)
   con(2,i) = loc(1,ipt)
  end do
  
  if( np > 1) then
    do i=1,nodes
     do j=2,np
       info(j-1,i) = inset(j,i)
     end do
    end do
  endif

  if( .not. associated(nsetPtr%next)) exit nset_convert_loop
  nsetPtr => nsetPtr%next
end do nset_convert_loop

end subroutine mkdramansets

subroutine mkdramaip(mypeid,nprocs,loc,npmax_g, &
                     ipData,dramaIPData          )
use femDataType
use numeric
implicit none

integer                       :: mypeid,nprocs
integer                       :: npmax_g
integer,dimension(2,npmax_g)  :: loc
type(ipdat),pointer           :: ipData
type(dramaIP),pointer         :: dramaIPData

! auto variables
integer                       :: i
integer                       :: nodes
integer,dimension(:,:),pointer:: con
integer,dimension(:),pointer  :: original

nodes = ipData%nodes

allocate(dramaIPData,con(2,nodes),original(nodes))

dramaIPData%nodes    =  nodes
dramaIPData%con      => con
dramaIPData%original => original

do i=1,nodes
  original(i) = ipData%ipno(i)
  con(1,i)    = loc(2,original(i))
  con(2,i)    = loc(1,original(i))
end do
end subroutine mkdramaip  

subroutine setdramaedat(edatno,firstDramaEdatPtr,nelem,enptr,con,matno,netype)

use femDataType
use numeric
use abortmodule
implicit none

integer,intent(in)                        :: edatno
type(dramaEdatList),pointer               :: firstDramaEdatPtr
integer                                   :: nelem
integer,dimension(:,:),pointer            :: enptr,con
integer,dimension(:)  ,pointer            :: matno
integer                                   :: netype

! auto variable
type(dramaEdatList),pointer    :: dramaEdatPtr
type(dramaEdat),pointer        :: dramaEdatData

!-----------------------------------------------------------

nullify(enptr,con,matno)

dramaEdatPtr => firstDramaEdatPtr

search_loop: do


 if(edatno .eq. dramaEdatPtr%no) then
   dramaEdatData => dramaEdatPtr%dramaEdatData 
   enptr => dramaEdatData%enptr
   con   => dramaEdatData%con
   matno => dramaEdatData%matno
   nelem =  dramaEdatData%nelem

   netype=  dramaEdatData%netype   ! P2 limit
  
   exit search_loop
 endif

 if( .not. associated(dramaEdatPtr%next)) exit search_loop
 dramaEdatPtr => dramaEdatPtr%next

end do search_loop

if( .not. associated(enptr)) then
  write(*,*) 'edatno=',edatno , ' not found(dramaEdatModel)'
  call abortexit(999)
endif

end subroutine setdramaedat

subroutine setdramanset(nsetno,firstDramaNsetPtr,nodes,np,con,info)

use femDataType
use numeric
use abortmodule
implicit none

integer,intent(in)                        :: nsetno
type(dramaNsetList),pointer               :: firstDramaNsetPtr
integer                                   :: nodes,np
integer,dimension(:,:),pointer            :: con,info

! auto variable
type(dramaNsetList),pointer    :: dramaNsetPtr
type(dramaNset),pointer        :: dramaNsetData

!-----------------------------------------------------------

nullify(con,info)

dramaNsetPtr => firstDramaNsetPtr

search_loop: do

 if(nsetno .eq. dramaNsetPtr%no) then
   dramaNsetData => dramaNsetPtr%dramaNsetData 
   con   => dramaNsetData%con
   info  => dramaNsetData%info
   nodes =  dramaNsetData%nodes
   np    =  dramaNsetData%np
  
   exit search_loop
 endif

 if( .not. associated(dramaNsetPtr%next)) exit search_loop
 dramaNsetPtr => dramaNsetPtr%next

end do search_loop

if( .not. associated(con)) then
  write(*,*) 'no=',nsetno , ' not found(setdramanset)'
  call abortexit(999)
endif

end subroutine setdramanset

!=================================
end module dramaDataModel
