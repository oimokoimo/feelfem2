/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SL_femDataType.cpp
 *  Date     : 2000/11/21
 *  Modified : 2000/11/21
 *  
 *  Purpose  : femDataType module
 *  
 */

#include "SL_feelfem90DRAMA.hpp"

void SL_feelfem90DRAMA::SL_femDataType(int makeFlag)
{
  char *sourceName;
  
  sourceName = GetSourceName("femDataType");
  OpenSource(sourceName);
  StoreSource(sourceName,makeFlag);


  writeSource("module femDataType");
  com();
  writeSource("!-------------------------------------------------------------------------");
  writeSource("! EDAT");
  writeSource("!-------------------------------------------------------------------------");
  writeSource("type edat  ");
  com();
  writeSource("   integer                          :: no       ! EDAT no ");
  writeSource("   integer                          :: np       ! number of nodes in one element");
  writeSource("   integer                          :: nelem    ! number of elements ");
  writeSource("   integer                          :: netype   ! Element type");
  com();
  writeSource("   integer,dimension(:,:),pointer   :: ielem    ! elem-node correspondance");
  writeSource("   integer,dimension(:)  ,pointer   :: matno    ! matrerial number");
  com();
  writeSource("end type edat ");
  com();
  writeSource("type edatList");
  writeSource("   integer                :: no");
  writeSource("   integer                :: isRegion ! region EDAT flag");
  writeSource("   type(edat),pointer     :: edatData ");
  writeSource("   type(edatList),pointer :: next");
  writeSource("end type edatList");
  com();
  writeSource("!-------------------------------------------------------------------------");
  writeSource("! NSET");
  writeSource("!-------------------------------------------------------------------------");
  writeSource("type nset");
  writeSource(" ");
  writeSource("   integer                          :: no       ! NSET no");
  writeSource("   integer                          :: np       ! Number of data in one node");
  writeSource("   integer                          :: nodes    ! Number of nodes in NSET");
  com();
  writeSource("   integer,dimension(:,:),pointer   :: inset    ! NSET data");
  writeSource("end type nset");
  com();
  writeSource("type nsetList");
  writeSource("   integer                :: no");
  writeSource("   type(nset),pointer     :: nsetData ");
  writeSource("   type(nsetList),pointer :: next");
  writeSource("end type nsetList");
  com();
  writeSource("!-------------------------------------------------------------------------");
  writeSource("! IP");
  writeSource("!-------------------------------------------------------------------------");
  writeSource("type ipdat");
  writeSource("   integer                          :: nodes    ! Number of IP nodes");
  writeSource("   integer,dimension(:),pointer     :: ipno     ! Node number");
  writeSource("end type ipdat");
  com();
  com();
  com();
  writeSource("!-------------------------------------------------------------------------");
  writeSource("! Problem Definition");
  writeSource("!-------------------------------------------------------------------------");
  writeSource("type meshInformation");
  writeSource("   integer                          :: mainEdatNo    ! main edat no.");
  writeSource("   integer                          :: medtNo        ! main EDAT data number");
  writeSource("   integer                          :: regionEdats   ! n of region EDATs");
  writeSource("   integer                          :: boundaryEdats ! n of boundary EDATs");
  writeSource("   integer,dimension(:),pointer     :: redatlist     ! region edat number list");
  writeSource("   integer,dimension(:),pointer     :: bedatlist     ! boundary edat number list");
  writeSource("end type meshInformation");
  com();
  writeSource("type solveInformation");
  writeSource("   integer                          :: solveNo       ! solve number");
  writeSource("   integer                          :: edatno        ! main EDAT data number");
  writeSource("   integer                          :: nofbedats     ! number of boundary edats");
  writeSource("   integer                          :: nofbnsets     ! number of boundary nsets");
  writeSource("   integer,dimension(:),pointer     :: bedatlist     ! boundary edat number list");
  writeSource("   integer,dimension(:),pointer     :: bnsetlist     ! boundary nset number list");
  writeSource("end type solveInformation");
  com();
  writeSource("type solveList");
  writeSource("   integer                          :: solves        ! number of solve ");
  writeSource("   type(solveInformation), &");
  writeSource("             dimension(:),pointer   :: solveDataList ! solveData list");
  writeSource("end type solveList");
  writeSource("   ");
  writeSource("   ");
  com();
  writeSource("!-------------------------------------------------------------------------");
  writeSource("! DRAMA/Double index format");
  writeSource("!-------------------------------------------------------------------------");
  writeSource("type dramaEdat");
  writeSource("   integer                          :: no       ! Number of EDAT set");
  writeSource("   integer                          :: nelem");
  writeSource("   integer,dimension(:,:),pointer   :: enptr");
  writeSource("   integer,dimension(:,:),pointer   :: con");
  writeSource("   integer,dimension(:)  ,pointer   :: matno");
  writeSource("end type dramaEdat");
  com();
  writeSource("type dramaEdatList");
  writeSource("   integer                          :: no");
  writeSource("   integer                          :: isRegion       ! region EDAT flag");
  writeSource("   type(dramaEdat),pointer          :: dramaEdatData");
  writeSource("   type(dramaEdatList),pointer      :: next");
  writeSource("end type dramaEdatList");
  com();
  writeSource("type dramaNset");
  writeSource("   integer                          :: no");
  writeSource("   integer                          :: nodes");
  writeSource("   integer                          :: np");
  writeSource("   integer,dimension(:,:),pointer   :: con    ! double index");
  writeSource("   integer,dimension(:,:),pointer   :: info   ! additional information");
  writeSource("end type dramaNset");
  com();
  writeSource("type dramaNsetList");
  writeSource("   integer                          :: no");
  writeSource("   type(dramaNset),pointer          :: dramaNsetData");
  writeSource("   type(dramaNsetList),pointer      :: next");
  writeSource("end type dramaNsetList");
  com();
  writeSource("type dramaIP");
  writeSource("   integer                          :: nodes");
  writeSource("   integer,dimension(:,:),pointer   :: con");
  writeSource("   integer,dimension(:)  ,pointer   :: original");
  writeSource("end type dramaIP");
  com();
  writeSource("!------------------------------------------------------------------------");
  com();
  writeSource("   ");
  com();
  writeSource("end module femDataType");

  CloseSource();
  
  return;
}
