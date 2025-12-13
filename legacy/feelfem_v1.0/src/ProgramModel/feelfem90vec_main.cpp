/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90vec_main.cpp
 *  Date     : 2001/11/29 (Copy from feelfem90_main.cpp)
 *  Modified : 
 *  
 *  Purpose  : temporary file for generating main routine
 *  
 */
#include "PM_feelfem90vec.hpp"
#include "feelfuncs.hpp"              // getSpaceDimension()


char* PM_feelfem90vec::GetMainSourceName(void)
{
  return(FNAME_FEELFEM90DRAMA_MAIN);  // defined feeldef.hpp (feelfem.f90)
}


void PM_feelfem90vec::DoMainRoutineHeaderPM( Main *mainPtr)
{
  DoMainRoutineArgumentSequencePM( mainPtr );

  SourceStarters();
  F90useMainPM();
  fortImplicit();

}

void PM_feelfem90vec::DoMainRoutineArgumentSequencePM( Main *mainPtr)
{
  writeSource("program feelfem");
  
  return;
}

void PM_feelfem90vec::F90useMainPM()
{
  F90useAlways();

  writeSource("use fileread");
  writeSource("use femDataType");
  writeSource("use report90");

  return;
}  


void PM_feelfem90vec::DoMainRoutineParameters( Main *mainPtr)
{

  writeSource("! Output level");
  writeSource("integer(kind=INT4 ),parameter  :: outlevel = 3          ! output level");
  com();

  return;
}

void PM_feelfem90vec::DoMainRoutineVariableDefinitions( Main *mainPtr)
{

  writeSource("real(kind=REAL8),dimension(:),pointer :: x,y,z          ! global coordinates");
  writeSource("real(kind=REAL8),dimension(:),pointer :: xloc,yloc,zloc ! local coordinates");
	     

  writeSource("integer(kind=INT4 )            :: ierror                ! for MPI");
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
  writeSource("! IP");
  writeSource("! ----");
  writeSource("type(ipdat),pointer            :: ipData");
  com();

  writeSource("! ------------------------------");
  writeSource("! FEM,EWISE variables");
  writeSource("! ------------------------------                             ");

  return;
}


void PM_feelfem90vec::DoMainRoutineInitializer( Main *mainPtr)
  //
  //  This Routine contains the data distribution
  //
  //
  //
{
  // no initializer in scalar model
  return;
}
  
void PM_feelfem90vec::DoMainRoutineReportInitializer( Main *mainPtr)
{
  writeSource("call report90init(outlevel)");
  writeSource("call report('Start')");
  com();
  return;
}

void PM_feelfem90vec::DoMainRoutineDataInput( Main *mainPtr)
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
  writeSource("              firstEdatPtr,firstNsetPtr,ipData, ierror           )");
  com();

  writeSource("if(ierror .eq. Oui) then");
  writeSource("  call abortexit('datinp error')");
  writeSource("endif");
  com();

  writeSource("call report('File READ')");
  writeSource("call report90FundamentalVars(ndim,npmax,nedat,nnset,nnum,nip)");

  return;
}


void PM_feelfem90vec::DoMainRoutineSchemeStart( Main *mainPtr)
{
  writeSource("*******************************************************");
  writeSource("*** This is temporary func for DoMainRoutineSchemeStart");
  writeSource("*******************************************************");

  return;
}

void PM_feelfem90vec::DoMainRoutineSchemeFinish( Main *mainPtr)
{
  writeSource("********************************************************");
  writeSource("*** This is temporary func for DoMainRoutineSchemeFinish");
  writeSource("********************************************************");

  return;
}


void PM_feelfem90vec::DoMainRoutineTerminationSequence( Main *mainPtr)
{
  comment();
  writeSource("!call reportallmem(0)");
  writeSource("!call reportfini");
  com();

  writeSource("end program feelfem");
  return;
}
