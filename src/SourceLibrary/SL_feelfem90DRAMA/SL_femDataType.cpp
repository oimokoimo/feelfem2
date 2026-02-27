/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_femDataType.cpp
 *  Date     : 2003/03/02 20:50
 *  Purpose  : Library module generator
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *
 */
#include "SL_feelfem90DRAMA.hpp"

static int come_yet_femDataType = 0;


void SL_feelfem90DRAMA::SL_femDataType(int makeFlag)
{
  const char *sourceName;

  if(come_yet_femDataType == 1)  return;
  else                  come_yet_femDataType = 1;

  sourceName = GetSourceName("femDataType");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("module femDataType");
  com();
  writeSource("!  Modified (03/02/21) dramaEdat    +netype, this is not good, but P2 limit");
  com();
  com();
  com();
  writeSource("use numeric");
  com();
  writeSource("!-------------------------------------------------------------------------");
  writeSource("! EDAT");
  writeSource("!-------------------------------------------------------------------------");
  writeSource("type edat");
  com();
  writeSource("   integer                          :: no      ! EDAT no");
  writeSource("   integer                          :: np      ! number of nodes in one element");
  writeSource("   integer                          :: nelem   ! number of elements");
  writeSource("   integer                          :: netype  ! Element type");
  com();
  writeSource("   integer,dimension(:,:),pointer   :: ielem   ! elem-node correspondance");
  writeSource("   integer,dimension(:)  ,pointer   :: matno   ! matrerial number");
  com();
  writeSource("end type edat");
  com();
  writeSource("type edatList");
  writeSource("   integer                :: no");
  writeSource("   integer                :: isRegion ! region EDAT flag");
  writeSource("   type(edat),pointer     :: edatData");
  writeSource("   type(edatList),pointer :: next");
  writeSource("end type edatList");
  com();
  writeSource("!-------------------------------------------------------------------------");
  writeSource("! NSET (node set)");
  writeSource("!-------------------------------------------------------------------------");
  writeSource("type nset");
  com();
  writeSource("   integer                          :: no       ! NSET no");
  writeSource("   integer                          :: np       ! Number of data in one node");
  writeSource("   integer                          :: nodes    ! Number of nodes in NSET");
  com();
  writeSource("   integer,dimension(:,:),pointer   :: inset    ! NSET data");
  writeSource("end type nset");
  com();
  writeSource("type nsetList");
  writeSource("   integer                :: no");
  writeSource("   type(nset),pointer     :: nsetData");
  writeSource("   type(nsetList),pointer :: next");
  writeSource("end type nsetList");
  com();
  writeSource("!-------------------------------------------------------------------------");
  writeSource("! Number data");
  writeSource("!-------------------------------------------------------------------------");
  writeSource("type numdat");
  writeSource("   integer                                :: numbers  ! Number of number data");
  writeSource("   real(kind=REAL8),dimension(:),pointer  :: dat      ! dat array");
  writeSource("end type numdat");
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
  writeSource("!-------------------------------------------------------------------------");
  writeSource("! REGN  (Region-Matno correspondance)");
  writeSource("!-------------------------------------------------------------------------");
  writeSource("type matdat");
  writeSource("   integer                          :: regions  ! n.o.regions in PDE file");
  writeSource("   integer,dimension(:),pointer     :: regmat   ! region->matno(-1 unassign)");
  writeSource("end type matdat");
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
  writeSource("   integer,dimension(:),pointer     :: redatlist     ! region edat No. list");
  writeSource("   integer,dimension(:),pointer     :: bedatlist     ! boundary edat No. list");
  writeSource("end type meshInformation");
  com();
  writeSource("type boundaryDataSet");
  writeSource("   integer                          :: solveNo       ! solve number");
  writeSource("   integer                          :: condType      ! =1 dcond =2 ncond");
  writeSource("   integer                          :: condNo        ! Nth condition");
  writeSource("   integer                          :: nofsets       ! number of sets");
  writeSource("   integer,dimension(:),pointer     :: datlist       ! number list of data set");
  writeSource("end type boundaryDataSet");
  com();
  com();
  writeSource("type solveInformation");
  writeSource("   integer                          :: solveNo       ! solve number");
  writeSource("   integer                          :: edatno        ! main EDAT data number");
  writeSource("   integer                          :: dconds        ! number of dconds");
  writeSource("   integer                          :: nconds        ! number of nconds");
  com();
  writeSource("   type(boundaryDataSet),dimension(:),pointer :: dlst  ! dirichlet data list");
  writeSource("   type(boundaryDataSet),dimension(:),pointer :: nlst  ! neumann data list");
  writeSource("end type solveInformation");
  com();
  writeSource("type solveList");
  writeSource("   integer                          :: solves        ! number of solve");
  writeSource("   type(solveInformation), &");
  writeSource("             dimension(:),pointer   :: solveDataList ! solveData list");
  writeSource("end type solveList");
  com();
  com();
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
  writeSource("   integer                          :: netype   ! This is DRAMA conflict var,");
  writeSource("                                                ! P2 limitation");
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
  com();
  com();
  writeSource("end module femDataType");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
