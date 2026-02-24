/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90DRAMA_main.cpp
 *  Date     : 2000/04/03
 *  Modified : 2000/04/03
 *  Modified : 2003/02/17
 *  
 *  Purpose  : temporary file for generating main routine
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
#include "PM_feelfem90DRAMA.hpp"
#include "feelfuncs.hpp"              // getSpaceDimension()

#include "Object.hpp"
#include "Main.hpp"


const char* PM_feelfem90DRAMA::GetMainSourceName(void)
{
  return(FNAME_FEELFEM90DRAMA_MAIN);
}


void PM_feelfem90DRAMA::DoMainRoutineHeaderPM( Main *mainPtr)
{
  DoMainRoutineArgumentSequencePM( mainPtr );

  SourceStarters();
  F90useMainPM();
  fortImplicit();

}

void PM_feelfem90DRAMA::DoMainRoutineArgumentSequencePM( Main *mainPtr)
{
  writeSource("program feelfem");
  
  return;
}

void PM_feelfem90DRAMA::F90useMainPM()
{
  F90useAlways();

  writeSource("use fileread");
  writeSource("use femDataType");
  com();

  writeSource("use mod_probInfoDistribute    ! for solv_dat distribute");
  com();

  writeSource("use dramaDataModel            ! for feel_dat distribute");
  writeSource("use datatrans");
  com();

  writeSource("use preport90");


  com();

  // use solves
  for(int i=0;i<feelfemobj.HowManySolves();i++) {
    pushSource("use mod_solve");
    pushSourceInt(i+1);
    flushSource();
  }
  if( feelfemobj.HowManySolves()) com();
  
  // use assigns
  for(int i=0;i<feelfemobj.HowManyAssigns();i++) {
    pushSource("use mod_let");
    pushSourceInt(i+1);
    flushSource();
  }
  if( feelfemobj.HowManyAssigns()) com();


  // material var
  if( feelfemobj.HowManyMaterialVars()) {
    writeSource("use mod_initmatvar");
    com();
  }

  // use outputs
  for(int i=0;i<feelfemobj.HowManyOutputs();i++) {
    pushSource("use mod_output");
    pushSourceInt(i+1);
    flushSource();
  }
  if( feelfemobj.HowManyOutputs()) com();


  return;
}  


void PM_feelfem90DRAMA::DoMainRoutineParameters( Main *mainPtr)
{
  writeSource("include 'mpif.h'");
  com();

  writeSource("! Output level");
  writeSource("integer(kind=INT4 ),parameter  :: outlevel = 3          ! output level");
  com();

  return;
}

void PM_feelfem90DRAMA::DoMainRoutineVariableDefinitions( Main *mainPtr)
{

  writeSource("real(kind=REAL8),dimension(:),pointer :: x,y,z          ! global coordinates");
  writeSource("real(kind=REAL8),dimension(:),pointer :: xloc,yloc,zloc ! local coordinates");
	     

  writeSource("integer(kind=INT4 )            :: ierror                ! for MPI");
  writeSource("integer(kind=INT4 )            :: nprocs,myrank,mypeid  ! MPI parameters");
  writeSource("integer(kind=INT4 )            :: nprocs_check");
  com();

  writeSource("!-----------------------------------------------------------------");
  writeSource("! feel_dat fundamental parameters");
  writeSource("!-----------------------------------------------------------------");
  writeSource("integer(kind=INT4 )            :: ndim        ! space dimension");
  writeSource("integer(kind=INT4 )            :: npmax       ! nodes(global/local)");
  writeSource("integer(kind=INT4 )            :: npmax_g     ! set in initbcast");
  writeSource("integer(kind=INT4 )            :: nelem_g     ! number of region element");
  writeSource("integer(kind=INT4 )            :: nedat");
  writeSource("integer(kind=INT4 )            :: nnset");
  writeSource("integer(kind=INT4 )            :: nnum");
  writeSource("integer(kind=INT4 )            :: nip");
  writeSource("!");
  writeSource("integer(kind=INT4 )            :: mode_ex");
  writeSource("integer(kind=INT4 )            :: mode_output");
  writeSource("integer(kind=INT4 )            :: nvars_fem,nvars_ewise");
  com();

  writeSource("! ------------");
  writeSource("! Problem data");
  writeSource("! ------------");
  writeSource("type(meshInformation)          :: meshDat");
  writeSource("type(solveInformation)         :: solveDat");
  writeSource("type(solveList)                :: solveLst        ");
  writeSource("! ----");
  writeSource("! EDAT");
  writeSource("! ----");
  writeSource("type(edat), pointer            :: edatData");
  writeSource("type(edatList),pointer         :: firstEdatPtr,currentEdatPtr,edatPtr");
  com();

  writeSource("! ----");
  writeSource("! NSET");
  writeSource("! ----");
  writeSource("type(nset), pointer            :: nsetData");
  writeSource("type(nsetList),pointer         :: firstNsetPtr,currentNsetPtr,nsetPtr");
  com();

  writeSource("! ----");
  writeSource("! NUM");
  writeSource("! ----");
  writeSource("type(numdat),pointer           :: numData");
  com();

  writeSource("! ----");
  writeSource("! IP");
  writeSource("! ----");
  writeSource("type(ipdat),pointer            :: ipData");
  com();

  writeSource("! ----");                                  // add 030217
  writeSource("! REGN  (region matno correspondance)"); 
  writeSource("! ----");
  writeSource("type(matDat),pointer           :: matData");
  com();

  writeSource("! -----------------------");
  writeSource("! for metis data");
  writeSource("! -----------------------");
  writeSource("integer,dimension(:),pointer   :: metis");
  com();

  writeSource("! -----------------------");
  writeSource("! DRAMA double index data");
  writeSource("! -----------------------");
  writeSource("type (dramaEdat), pointer      :: dramaEdatData");
  writeSource("type (dramaEdatList),pointer   :: dramaEdatPtr,firstDramaEdatPtr, &");
  writeSource("                                  currentDramaEdatPtr");
  writeSource("type (dramaNsetList),pointer   :: firstDramaNsetPtr");
  writeSource("type (dramaIP),pointer         :: dramaIPData");
  com();

  writeSource("! ------------------------------");
  writeSource("! for Making DRAMA/double index");
  writeSource("! ------------------------------       ");
  writeSource("integer,dimension(:,:),pointer :: loc");
  writeSource("integer                        :: mynode,myelem");
  com();

  writeSource("! ------------------------------");
  writeSource("! FEM,EWISE variables");
  writeSource("! ------------------------------                             ");

  listIterator <Variable *>itrV(mainPtr->GetVarPtrList());
  for(itrV.init(); !itrV ; ++ itrV ) {
    MainVariableDeclaration( itrV() );
  }
  com(); // oimo

  return;
}


void PM_feelfem90DRAMA::DoMainRoutineInitializer( Main *mainPtr)
  //
  //  This Routine contains the data distribution
  //
  //
  //
{

  COMMENTlong("MPI initialization");
  F90_MPI_Initialize();
  com();
  writeSource("mypeid = myrank");
  com();

  return;
}
  
void PM_feelfem90DRAMA::DoMainRoutineReportInitializer( Main *mainPtr)
{
  writeSource("if(myrank == 0) call preport90init(outlevel)");
  writeSource("if(myrank == 0) call preport('Start')");
  com();
  return;
}

void PM_feelfem90DRAMA::DoMainRoutineDataInput( Main *mainPtr)
{
  writeSource("!----------------");
  writeSource("! MESH DATA READ ");
  writeSource("!----------------");
  writeSource("if(myrank.eq.0) then");
  com();
  writeSource("  !---------");
  writeSource("  ! solv_dat");
  writeSource("  !---------");
  writeSource("  call ctrlinp(meshDat,solveLst, ierror)");

  writeSource("  if(ierror .eq. Oui) then");
  writeSource("    call abortexit(mypeid)");
  writeSource("  endif");
  com();com();

  writeSource("  !---------");
  writeSource("  ! feel_dat");
  writeSource("  !---------");
  writeSource("  call datinp(ndim,npmax,nelem_g, nedat,nnset,nnum,nip,  &");
  writeSource("              mode_ex,mode_output,nvars_fem,nvars_ewise, &");
  writeSource("              x,y,z, firstEdatPtr,firstNsetPtr,numData,  &");
  writeSource("              ipData, matData,   ierror                   )");
  com();

  writeSource("  if(ierror .eq. Oui) then");
  writeSource("    call abortexit(mypeid)");
  writeSource("  endif");
  com();

  //  writeSource("  !-----------");
  //  writeSource("  ! metis.bamg");
  //  writeSource("  ! metis.feel");
  //  writeSource("  !-----------");
  
  writeSource("  !----------------------------------");
  writeSource("  ! read METIS partition information ");
  writeSource("  !----------------------------------");

  writeSource("  allocate(metis(nelem_g))");
  writeSource("  call readmetis(myrank,nprocs,nelem_g,metis) ! new version");
  com();

  writeSource("  call preport('File READ')");
  writeSource("  call preport90FundamentalVars(ndim,npmax,nedat,nnset,nnum,nip)");
  writeSource("!");
  writeSource("end if  ! end of myrank=0(root PE) data read block");

  //////////////////////////////
  //  DATA DISTRIBUTION CODE  //
  //////////////////////////////
  writeSource("!-----------------------------------");
  writeSource("! Message passing for data transfer");
  writeSource("!-----------------------------------");
  com();


  writeSource("! num data, material region No. data distribute");
  writeSource("call matInitDistribute(myrank,nprocs,numData,matData)");
  com();

  writeSource("! solv_dat data transfer");
  writeSource("call probInfoDistribute(myrank,nprocs,meshDat,solveLst)");
  com();
  com();

  writeSource("call initbcast(myrank,nprocs,                                     &");
  writeSource("               ndim,npmax,npmax_g,nelem_g,nedat,nnset,nnum,nip,   &");
  writeSource("               mode_ex,mode_output,nvars_fem,nvars_ewise,         &");
  writeSource("               x,y,                                               &");
  writeSource("               firstEdatPtr,firstNsetPtr,ipData,                  &");
  writeSource("               metis                                               )");
  com();

  writeSource(" if(myrank .eq. 0) call preport('End of TRANSFER,NODE,EDAT')");
  com();
  

  //////////////////////////////
  //  DRAMA/Double index      //
  //////////////////////////////
  writeSource("!---------------------------------");
  writeSource("! Make DRAMA double index data");
  writeSource("! step 1 LONUMERATE");
  writeSource("!---------------------------------");
  writeSource(" allocate(loc(2,npmax_g))");
  writeSource(" call lonumerate(mypeid,nprocs,  loc,npmax_g, metis,nelem_g,  &");
  writeSource("                 firstEdatPtr,   mynode,myelem                )");
  writeSource("  if(myrank .eq. 0) call preport('MODULE:lonumerate')");
  com();

  writeSource("!-----------------------------------");
  writeSource("! Make DRAMA double index data");
  writeSource("! step 2 Make local coordinate array");
  writeSource("!-----------------------------------");
  switch(getSpaceDimension()){
  case 1:
    writeSource(" allocate(xloc(mynode))");
    break;

  case 2:
    writeSource(" allocate(xloc(mynode),yloc(mynode))");
    break;

  case 3:
    writeSource(" allocate(xloc(mynode),yloc(mynode),zloc(mynode))");
    break;

  default:
    assert(1==0);
  }

  switch(getSpaceDimension()){
  case 2:
    writeSource(" call mkloccoor(mypeid,nprocs,x,y,loc,npmax_g,xloc,yloc,mynode)");
    break;

  case 3:
    writeSource(" call mkloccoor3(mypeid,nprocs,x,y,z,loc,npmax_g,xloc,yloc,zloc,mynode)");
    break;
    
  default:
    assert(1==0);
  }

  writeSource("  if(myrank .eq. 0) call preport('MODULE:mkloccoor')");
  com();

  writeSource("!-------------------------------------------");
  writeSource("! Make DRAMA double index data");
  writeSource("! step 3 Make local & global enptr/con/matno");
  writeSource("!-------------------------------------------");
  com();

  writeSource("! first, mark isRegion in type edatList");
  com();

  writeSource("  edatPtr => firstEdatPtr");
  writeSource("  region_edat_mark_loop: do");
  writeSource("    edatData => edatPtr%edatData");
  writeSource("    if(edatData%nelem == nelem_g) then");
  writeSource("      edatPtr%isRegion = Oui");
  writeSource("    else");
  writeSource("      edatPtr%isRegion = Non");
  writeSource("    endif");
  writeSource("    if(.not.associated(edatPtr%next)) exit region_edat_mark_loop");
  writeSource("    edatPtr => edatPtr%next");
  writeSource("  end do region_edat_mark_loop");
  com();

  writeSource("  call mkdramaedats(mypeid,nprocs,loc,npmax_g,metis,nelem_g, &");
  writeSource("                    mynode,myelem, firstEdatPtr,firstDramaEdatPtr)");
  com();

  writeSource("  if(myrank == 0) call preport('MODULE:mkdramaedats')");
  com();

  writeSource("!-------------------------------------------");
  writeSource("! Make DRAMA double index data for NSET");
  writeSource("! step 4 Make local & global nset");
  writeSource("!-------------------------------------------");
  writeSource("  if(associated(firstNsetPtr) ) then");
  writeSource("    call mkdramansets(mypeid,nprocs,loc,npmax_g, &");
  writeSource("                      firstNsetPtr,firstDramaNsetPtr)");
  writeSource("    if(myrank == 0) call preport('MODULE:mkdramansets')");
  writeSource("  else");
  writeSource("    if(myrank == 0) call preport('      :(No nset data sets)')");
  writeSource("  endif");
  com();
  
  writeSource("!-------------------------------------------");
  writeSource("! Make DRAMA double index data");
  writeSource("! step 5 conver ip information");
  writeSource("!-------------------------------------------");
  writeSource("if(nip > 0) then");
  writeSource("  call mkdramaip(mypeid,nprocs,loc,npmax_g, &");
  writeSource("                 ipData,dramaIPData         )");
  writeSource("else");
  writeSource("  nullify(dramaIPData)");
  writeSource("endif");
  com();

  writeSource("!-------------------------------------------");
  writeSource("! Make DRAMA double index data");
  writeSource("! step 6 deallocation");
  writeSource("!-------------------------------------------");
  com();
  writeSource("deallocate(metis)");
  writeSource("deallocate(x,y)");
  writeSource("deallocate(loc)");
  com();

  writeSource("edatPtr => firstEdatPtr");
  writeSource("deallocate_edat : do");
  writeSource("  edatData => edatPtr%edatData");
  writeSource("  deallocate(edatData%ielem)");
  writeSource("  deallocate(edatData%matno)");
  writeSource("!  deallocate(edatData)");
  writeSource("  if(.not.associated(edatPtr%next)) exit deallocate_edat");
  writeSource("  edatPtr => edatPtr%next");
  writeSource("end do deallocate_edat");
  com();

  writeSource("if(associated(firstNsetPtr)) then");
  writeSource("  nsetPtr => firstNsetPtr");
  writeSource("  deallocate_nset : do");
  writeSource("    nsetData => nsetPtr%nsetData");
  writeSource("    deallocate(nsetData%inset)");
  writeSource("!         deallocate(nsetData)");
  writeSource("    if(.not.associated(nsetPtr%next)) exit deallocate_nset");
  writeSource("    nsetPtr => nsetPtr%next");
  writeSource("  end do deallocate_nset");
  writeSource("endif");
  com();

  writeSource("if(myrank == 0) call preport('Deallocation complete')");
  com();

  writeSource("npmax =  mynode");
  switch(getSpaceDimension()){
  case 1:
    writeSource("x     => xloc");
    break;

  case 2:
    writeSource("x     => xloc");
    writeSource("y     => yloc");
    break;

  case 3:
    writeSource("x     => xloc");
    writeSource("y     => yloc");
    writeSource("z     => zloc");
    break;
  }
  com();

  return;
}


void PM_feelfem90DRAMA::DoMainRoutineSchemeStart( Main *mainPtr)
{
  // Memory allocation for variables (03/01/26)
  COMMENTlong("Variable allocation");
  listIterator <Variable *>itrV(mainPtr->GetVarPtrList());
  for(itrV.init(); !itrV ; ++ itrV ) {
    MainVariableAllocation( itrV() );
  }
  com(); // oimo  

  return;
}

void PM_feelfem90DRAMA::DoMainRoutineSchemeFinish( Main *mainPtr)
{
  writeSource("!********************************************************");
  writeSource("!*** This is temporary func for DoMainRoutineSchemeFinish");
  writeSource("!********************************************************");
  com();

  return;
}


void PM_feelfem90DRAMA::DoMainRoutineTerminationSequence( Main *mainPtr)
{
  comment();
  writeSource("!call preportallmem(myrank,nprocs)");
  writeSource("!if(myrank.eq.0) call preportfini");
  com();

  F90_MPI_Finalize();
  com();
  
  writeSource("end program feelfem");

  return;
}

void PM_feelfem90DRAMA::DoMainRoutineInitialValue( Main *mainPtr )
{
  // consts and doubles
  COMMENTlong("Initial Values");
  listIterator <Variable *>itrV(mainPtr->GetVarPtrList());
  for(itrV.init(); !itrV ; ++ itrV ) {
    doMainVariableInitialValue( itrV() );
  }
  com();

  COMMENTlong("Scheme start");
  return;
}
