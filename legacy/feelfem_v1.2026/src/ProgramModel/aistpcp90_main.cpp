/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : aistpcp90_main.cpp
 *  Date     : 2002/06/28  (copy from feelfem90)
 *  Modified : 2002/09/30
 *  
 *  Purpose  : temporary file for generating main routine
 *  
 */
#include "PM_aistpcp90.hpp"
#include "feelfuncs.hpp"              // getSpaceDimension()

#include "Object.hpp"
#include "Main.hpp"

char* PM_aistpcp90::GetMainSourceName(void)
{
  return(FNAME_FEELFEM90DRAMA_MAIN);
}

void PM_aistpcp90::DoMainRoutineHeaderPM( Main *mainPtr)
{
  DoMainRoutineArgumentSequencePM( mainPtr );

  SourceStarters();
  F90useMainPM();
  fortImplicit();
  
  writeSource("include 'mpif.h'");
  
  return;
}

void PM_aistpcp90::DoMainRoutineArgumentSequencePM( Main *mainPtr)
{
  writeSource("program feelfem");

  return;
}

void PM_aistpcp90::F90useMainPM()
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

void PM_aistpcp90::DoMainRoutineParameters( Main *mainPtr)
{
  com();
  writeSource("! Output level");
  writeInteger4pm("outlevel = 3   ! output level");       
  com();

  return;
}

void PM_aistpcp90::DoMainRoutineVariableDefinitions( Main *mainPtr)
{

  writeReal8Ptr1 ("x,y,z          ! global coordinates");
  com();

  writeInteger4Ptr1("iedom          ! METIS partition info.");
  writeInteger4sc  ("myrank,nprocs  ! for MPI");
  writeInteger4sc  ("ierror         ! for MPI");

  com();

  writeSource("!-----------------------------------------------------------------");
  writeSource("! feel_dat fundamental parameters");
  writeSource("!-----------------------------------------------------------------");

  writeInteger4sc("ndim           ! space dimension");
  writeInteger4sc("npmax          ! nodes(global/local)");
  writeInteger4sc("nelem_g        ! number of region element");
  writeInteger4sc("nedat");
  writeInteger4sc("nnset");
  writeInteger4sc("nnum");
  writeInteger4sc("nip");
  com();

  writeInteger4sc("mode_ex");
  writeInteger4sc("mode_output");
  writeInteger4sc("nvars_fem,nvars_ewise");
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


void PM_aistpcp90::DoMainRoutineInitializer( Main *mainPtr)
  //
  //  This Routine contains the data distribution
  //
{
  
  COMMENTlong("MPI initialize");
  writeSource("call mpi_init(ierror)");
  writeSource("call mpi_comm_rank(mpi_comm_world,myrank,ierror)");
  writeSource("call mpi_comm_size(mpi_comm_world,nprocs,ierror)");
  com();

  return;
}
  
void PM_aistpcp90::DoMainRoutineReportInitializer( Main *mainPtr)
{
  writeSource("if(myrank == 0) then");
  writeSource("  call report90init(outlevel)");
  writeSource("  call report('Start')");
  writeSource("end if");
  com();
  return;
}

void PM_aistpcp90::DoMainRoutineDataInput( Main *mainPtr)
{
  writeSource("!----------------");
  writeSource("! MESH DATA READ ");
  writeSource("!----------------");
  com();
  writeSource("!---------");
  writeSource("! solv_dat");
  writeSource("!---------");
  writeSource("call ctrlinp(meshDat,solveLst, ierror)");

  writeSource("if(ierror .eq. Oui) then");
  writeSource("  call abortexit('Error return from ctrlinp')");
  writeSource("endif");
  com();com();

  writeSource("!---------");
  writeSource("! feel_dat");
  writeSource("!---------");
  writeSource("call datinp(ndim,npmax,nelem_g,nedat,nnset,nnum,nip, &");
  writeSource("              mode_ex,mode_output,nvars_fem,nvars_ewise,       &");
  writeSource("              x,y,z,                                           &");
  writeSource("              firstEdatPtr,firstNsetPtr,numData,ipData,matData,&");
  writeSource("              ierror   )");
  com();

  writeSource("if(ierror .eq. Oui) then");
  writeSource("  call abortexit('datinp error')");
  writeSource("endif");
  com();

  writeSource("!---------");
  writeSource("! METIS");
  writeSource("!---------");
  writeSource("allocate(iedom(nelem_g))");
  com();
  writeSource("call readmetis(myrank,nprocs,nelem_g,iedom)");
  com();



  writeSource("if(myrank == 0) then");
  writeSource("  call report('File READ')");
  writeSource("  call report90FundamentalVars(ndim,npmax,nedat,nnset,nnum,nip)");
  writeSource("end if");
  com();

  return;
}


void PM_aistpcp90::DoMainRoutineSchemeStart( Main *mainPtr)
{
  // Memory allocation for Variables
  COMMENTlong("Variable allocation");
  listIterator <Variable *>itrV(mainPtr->GetVarPtrList());
  for(itrV.init(); !itrV ; ++ itrV ) {
    MainVariableAllocation( itrV() );
  }
  com(); // oimo  

  return;
}

void PM_aistpcp90::DoMainRoutineInitialValue( Main *mainPtr )
{
  // consts and doubles
  COMMENTlong("Initial Values");
  listIterator <Variable *>itrV(mainPtr->GetVarPtrList());
  for(itrV.init(); !itrV ; ++ itrV ) {
    doMainVariableInitialValue( itrV() );
  }
  com();


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

  COMMENTlong("Scheme start");
  return;
}

void PM_aistpcp90::DoMainRoutineSchemeFinish( Main *mainPtr)
{
  //writeSource("//********************************************************");
  //writeSource("//*** This is temporary func for DoMainRoutineSchemeFinish");
  //writeSource("//********************************************************");


  return;
}


void PM_aistpcp90::DoMainRoutineTerminationSequence( Main *mainPtr)
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
