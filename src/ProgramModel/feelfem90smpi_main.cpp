/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90smpi_main.cpp
 *  Date     : 2003/01/03 (copied from feelfem90)
 *  Modified : 
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
#include "PM_feelfem90smpi.hpp"
#include "feelfuncs.hpp"              // getSpaceDimension()

#include "Object.hpp"
#include "Main.hpp"

const char* PM_feelfem90smpi::GetMainSourceName(void)
{
  return(FNAME_FEELFEM90DRAMA_MAIN);
}

void PM_feelfem90smpi::DoMainRoutineHeaderPM( Main *mainPtr)
{
  DoMainRoutineArgumentSequencePM( mainPtr );

  SourceStarters();
  F90useMainPM();
  fortImplicit();
  com();

  writeSource("include 'mpif.h'");
  com();

}

void PM_feelfem90smpi::DoMainRoutineArgumentSequencePM( Main *mainPtr)
{
  writeSource("program feelfem");

  return;
}

void PM_feelfem90smpi::F90useMainPM()
{
  F90useAlways();

  writeSource("use fileread");
  writeSource("use femDataType");
  writeSource("use report90");

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

void PM_feelfem90smpi::DoMainRoutineParameters( Main *mainPtr)
{

  writeSource("! Output level");
  writeSource("integer(kind=INT4 ),parameter  :: outlevel = 3          ! output level");
  com();

  return;
}

void PM_feelfem90smpi::DoMainRoutineVariableDefinitions( Main *mainPtr)
{

  writeReal8Ptr1("x,y,z          ! global coordinates");
  com();

  writeInteger4sc  ("myrank,nprocs  ! for MPI");
  writeInteger4sc  ("ierror         ! for MPI"); 
  com();

  writeSource("!-----------------------------------------------------------------");
  writeSource("! feel_dat fundamental parameters");
  writeSource("!-----------------------------------------------------------------");
  writeSource("integer(kind=INT4 )            :: ndim        ! space dimension");
  writeSource("integer(kind=INT4 )            :: npmax       ! nodes(global/local)");
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
  writeSource("! IP    (Node number information)");
  writeSource("! ----");
  writeSource("type(ipdat),pointer            :: ipData");
  com();

  writeSource("! ----");
  writeSource("! REGN  (region matno correspondance)"); 
  writeSource("! ----");
  writeSource("type(matDat),pointer           :: matData");
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


void PM_feelfem90smpi::DoMainRoutineInitializer( Main *mainPtr)
  // data distribution, etc.
{
  COMMENTlong("MPI initialize");
  writeSource("call mpi_init(ierror)");
  writeSource("call mpi_comm_rank(mpi_comm_world,myrank,ierror)");
  writeSource("call mpi_comm_size(mpi_comm_world,nprocs,ierror)");
  com();
  
  return;
}
  
void PM_feelfem90smpi::DoMainRoutineReportInitializer( Main *mainPtr)
{
  writeSource("if(myrank .eq. 0) then");
  writeSource("  call report90init(outlevel)");
  writeSource("  call report('Start')");
  writeSource("end if ! myrank == 0");
  com();
  return;
}

void PM_feelfem90smpi::DoMainRoutineDataInput( Main *mainPtr)
{
  writeSource("!---------------------------------------------");
  writeSource("! MESH DATA READ ");
  writeSource("!");
  writeSource("! In feelfem90smpi ProgramModel, only the host");
  writeSource("! processor has the data, and the other processors");
  writeSource("! work just for solver process. (etc. MUMPSCA)");
  writeSource("!----------------------------------------------");
  com();
  writeSource("if(myrank .eq. 0) then");
  com();
  writeSource("!---------");
  writeSource("! solv_dat");
  writeSource("!---------");
  writeSource(" call ctrlinp(meshDat,solveLst, ierror)");

  writeSource(" if(ierror .eq. Oui) then");
  writeSource("   call abortexit('Error return from ctrlinp')");
  writeSource(" endif");
  com();com();

  writeSource("!---------");
  writeSource("! feel_dat");
  writeSource("!---------");
  writeSource(" call datinp(ndim,npmax,nelem_g,nedat,nnset,nnum,nip, &");
  writeSource("               mode_ex,mode_output,nvars_fem,nvars_ewise,       &");
  writeSource("               x,y,z,                                           &");
  writeSource("               firstEdatPtr,firstNsetPtr,numData,ipData,matData,&");
  writeSource("               ierror   )");
  com();

  writeSource(" if(ierror .eq. Oui) then");
  writeSource("   call abortexit('datinp error')");
  writeSource(" endif");
  com();

  writeSource("call report('File READ')");
  writeSource("call report90FundamentalVars(ndim,npmax,nedat,nnset,nnum,nip)");
  com();

  writeSource("end if    ! if(myrank == 0)");
  com();

  return;
}


void PM_feelfem90smpi::DoMainRoutineSchemeStart( Main *mainPtr)
{
  // Memory allocation for Variables

  
  writeSource("!-----------------------------------------");
  writeSource("! only for the host allocate vector arrays");
  writeSource("!-----------------------------------------");
  writeSource("if(myrank .eq. 0) then");

  COMMENTlong("Variable allocation");
  listIterator <Variable *>itrV(mainPtr->GetVarPtrList());
  for(itrV.init(); !itrV ; ++ itrV ) {
    MainVariableAllocation( itrV() );
  }
  com(); // oimo  

  writeSource("end if   ! myrank == 0");
  com();

  return;
}

void PM_feelfem90smpi::DoMainRoutineInitialValue( Main *mainPtr )
{
  writeSource("!----------------------------------------");
  writeSource("! only for the host to set initial values");
  writeSource("!----------------------------------------");
  writeSource("if(myrank .eq. 0) then");

  // consts and doubles
  COMMENTlong("Initial Values");

  listIterator <Variable *>itrV(mainPtr->GetVarPtrList());
  for(itrV.init(); !itrV ; ++ itrV ) {
    doMainVariableInitialValue( itrV() );
  }

  // Initialize material vars
  int matvars = feelfemobj.HowManyMaterialVars();

  if(matvars >0) {
    pushSource("call initmatvar(meshDat,firstEdatPtr,matData");
    listIterator <Variable *>itrMatV(feelfemobj.GetMaterialVarList());
    for(itrMatV.init(); !itrMatV ; ++itrMatV ){
      pushSource(",");
      pushVariableNameInMain( itrMatV() );
    }
    pushSource(")");
    flushSource();
  }
  com();

  writeSource("end if   ! myrank == 0");
  com();

  COMMENTlong("Scheme start");
  return;
}

void PM_feelfem90smpi::DoMainRoutineSchemeFinish( Main *mainPtr)
{
  //writeSource("//********************************************************");
  //writeSource("//*** This is temporary func for DoMainRoutineSchemeFinish");
  //writeSource("//********************************************************");

  com();

  return;
}


void PM_feelfem90smpi::DoMainRoutineTerminationSequence( Main *mainPtr)
{
  comment();
  writeSource("if(myrank == 0) then");
  writeSource("!  call reportallmem(0)");
  writeSource("!  call reportfini");
  writeSource("end if");
  com();
 
  // MPI termination
  writeSource("call mpi_finalize(ierror)");
  com();

  writeSource("end program feelfem");
  return;
}
