module feelP2data

!------------------------------------------
! handling scalar feelP2 data for feelfem90

!------------------------------------------
contains

subroutine setP2edat(edatno,firstEdatPtr,nelem,np,netype,ielem,matno)
use femDataType
use numeric
use abortmodule

implicit none

integer,intent(in)                    :: edatno
type(edatList),pointer                :: firstEdatPtr
integer                               :: nelem
integer                               :: np
integer                               :: netype
integer,dimension(:,:),pointer        :: ielem
integer,dimension(:),pointer          :: matno

! auto variable
type(edatList),pointer                :: edatPtr
type(edat),pointer                    :: edatData
!-------------------------------------------
nullify(ielem,matno)

edatPtr => firstEdatPtr

search_loop: do

 if(edatno == edatPtr%no) then

   edatData => edatPtr%edatData
   nelem    =  edatData%nelem
   np       =  edatData%np
   netype   =  edatData%netype

   ielem    => edatData%ielem
   matno    => edatData%matno

   exit search_loop

 endif

 if( .not. associated(edatPtr%next)) exit search_loop
 edatPtr => edatPtr%next

end do search_loop

if( .not. associated(ielem)) then
  write(*,*) 'edatno=',edatno, 'not found(feelP2data)'
  call abortexit('setP2edat error')
endif

end subroutine setP2edat


subroutine setP2nset(nsetno,firstNsetPtr,nodes,np,inset)

use femDataType
use numeric
use abortmodule

implicit none

integer                          :: nsetno
type(nsetList),pointer           :: firstNsetPtr
integer                          :: nodes,np
integer,dimension(:,:),pointer   :: inset

! auto variable
type(nsetList),pointer           :: nsetPtr
type(nset),pointer               :: nsetData

!---

nullify(inset)

nsetPtr => firstNsetPtr

search_loop: do

 if(nsetno .eq. nsetPtr%no) then
   nsetData => nsetPtr%nsetData
   nodes    =  nsetData%nodes
   np       =  nsetData%np
   inset    => nsetData%inset

   exit search_loop
 endif

 if( .not. associated(nsetPtr%next)) exit search_loop
 nsetPtr => nsetPtr%next

end do search_loop

if( .not. associated(inset)) then
  write(*,*) 'nsetno=',nsetno , ' not found(setP2nset)'
  call abortexit('setP2nset error')
endif

end subroutine setP2nset

integer function getipno( n ,ipData)
use femDataType
use abortmodule
implicit none

integer,intent(in)            :: n
type(ipdat),pointer           :: ipData

! auto
integer,dimension(:),pointer  :: ipno

ipno => ipData%ipno

if(n < 1  .or. n > ipData%nodes) then
  write(*,*) 'try to get ipdat no ',n
  call abortexit('getipno error')
endif

getipno = ipno(n)

return
end function getipno



end module feelP2data
