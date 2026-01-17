module femDataType

use numeric

!-------------------------------------------------------------------------
! EDAT
!-------------------------------------------------------------------------
type edat  

   integer                          :: no      ! EDAT no 
   integer                          :: np      ! number of nodes in one element
   integer                          :: nelem   ! number of elements 
   integer                          :: netype  ! Element type

   integer,dimension(:,:),pointer   :: ielem   ! elem-node correspondance
   integer,dimension(:)  ,pointer   :: matno   ! matrerial number

end type edat 

type edatList
   integer                :: no
   integer                :: isRegion ! region EDAT flag
   type(edat),pointer     :: edatData 
   type(edatList),pointer :: next
end type edatList

!-------------------------------------------------------------------------
! NSET (node set)
!-------------------------------------------------------------------------
type nset
 
   integer                          :: no       ! NSET no
   integer                          :: np       ! Number of data in one node
   integer                          :: nodes    ! Number of nodes in NSET

   integer,dimension(:,:),pointer   :: inset    ! NSET data
end type nset

type nsetList
   integer                :: no
   type(nset),pointer     :: nsetData 
   type(nsetList),pointer :: next
end type nsetList

!-------------------------------------------------------------------------
! Number data
!-------------------------------------------------------------------------
type numdat
   integer                                :: numbers  ! Number of number data
   real(kind=REAL8),dimension(:),pointer  :: dat      ! dat array
end type numdat

!-------------------------------------------------------------------------
! IP
!-------------------------------------------------------------------------
type ipdat
   integer                          :: nodes    ! Number of IP nodes
   integer,dimension(:),pointer     :: ipno     ! Node number
end type ipdat


!-------------------------------------------------------------------------
! REGN  (Region-Matno correspondance)
!-------------------------------------------------------------------------
type matdat
   integer                          :: regions  ! n.o.regions in PDE file
   integer,dimension(:),pointer     :: regmat   ! region->matno(-1 unassign)
end type matdat



!-------------------------------------------------------------------------
! Problem Definition
!-------------------------------------------------------------------------
type meshInformation
   integer                          :: mainEdatNo    ! main edat no.
   integer                          :: medtNo        ! main EDAT data number
   integer                          :: regionEdats   ! n of region EDATs
   integer                          :: boundaryEdats ! n of boundary EDATs
   integer,dimension(:),pointer     :: redatlist     ! region edat No. list
   integer,dimension(:),pointer     :: bedatlist     ! boundary edat No. list
end type meshInformation

type boundaryDataSet
   integer                          :: solveNo       ! solve number
   integer                          :: condType      ! =1 dcond =2 ncond
   integer                          :: condNo        ! Nth condition 
   integer                          :: nofsets       ! number of sets
   integer,dimension(:),pointer     :: datlist       ! number list of data set
end type boundaryDataSet


type solveInformation
   integer                          :: solveNo       ! solve number
   integer                          :: edatno        ! main EDAT data number
   integer                          :: dconds        ! number of dconds
   integer                          :: nconds        ! number of nconds

   type(boundaryDataSet),dimension(:),pointer :: dlst  ! dirichlet data list
   type(boundaryDataSet),dimension(:),pointer :: nlst  ! neumann data list
end type solveInformation

type solveList
   integer                          :: solves        ! number of solve 
   type(solveInformation), &
             dimension(:),pointer   :: solveDataList ! solveData list
end type solveList
   
   

!-------------------------------------------------------------------------
! DRAMA/Double index format
!-------------------------------------------------------------------------
type dramaEdat
   integer                          :: no       ! Number of EDAT set
   integer                          :: nelem
   integer,dimension(:,:),pointer   :: enptr
   integer,dimension(:,:),pointer   :: con
   integer,dimension(:)  ,pointer   :: matno
end type dramaEdat

type dramaEdatList
   integer                          :: no
   integer                          :: isRegion       ! region EDAT flag
   type(dramaEdat),pointer          :: dramaEdatData
   type(dramaEdatList),pointer      :: next
end type dramaEdatList

type dramaNset
   integer                          :: no
   integer                          :: nodes
   integer                          :: np
   integer,dimension(:,:),pointer   :: con    ! double index
   integer,dimension(:,:),pointer   :: info   ! additional information
end type dramaNset

type dramaNsetList
   integer                          :: no
   type(dramaNset),pointer          :: dramaNsetData
   type(dramaNsetList),pointer      :: next
end type dramaNsetList

type dramaIP
   integer                          :: nodes
   integer,dimension(:,:),pointer   :: con
   integer,dimension(:)  ,pointer   :: original
end type dramaIP

!------------------------------------------------------------------------

   

end module femDataType
