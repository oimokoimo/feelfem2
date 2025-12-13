/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90_main.cpp
 *  Date     : 2000/04/03
 *  Modified : 2000/04/03
 *  
 *  Purpose  : temporary file for generating main routine
 *  
 */
#include "PM_feelfem90.hpp"
#include "feelfuncs.hpp"              // getSpaceDimension()

#include "Object.hpp"
#include "Main.hpp"

char* PM_feelfem90::GetMainSourceName(void)
{
  return(FNAME_FEELFEM90DRAMA_MAIN);
}

void PM_feelfem90::DoMainRoutineHeaderPM( Main *mainPtr)
{
  DoMainRoutineArgumentSequencePM( mainPtr );

  SourceStarters();
  F90useMainPM();
  fortImplicit();
}

void PM_feelfem90::DoMainRoutineArgumentSequencePM( Main *mainPtr)
{
  writeSource("program feelfem");

  return;
}

void PM_feelfem90::F90useMainPM()
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

void PM_feelfem90::DoMainRoutineParameters( Main *mainPtr)
{

  writeSource("! Output level");
  writeSource("integer(kind=INT4 ),parameter  :: outlevel = 3          ! output level");
  com();

  return;
}

void PM_feelfem90::DoMainRoutineVariableDefinitions( Main *mainPtr)
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


void PM_feelfem90::DoMainRoutineInitializer( Main *mainPtr)
  //
  //  This Routine contains the data distribution
  //
{

  return;
}
  
void PM_feelfem90::DoMainRoutineReportInitializer( Main *mainPtr)
{
  writeSource("call report90init(outlevel)");
  writeSource("call report('Start')");
  com();
  return;
}

void PM_feelfem90::DoMainRoutineDataInput( Main *mainPtr)
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

  writeSource("call report('File READ')");
  writeSource("call report90FundamentalVars(ndim,npmax,nedat,nnset,nnum,nip)");
  com();

  return;
}


void PM_feelfem90::DoMainRoutineSchemeStart( Main *mainPtr)
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

void PM_feelfem90::DoMainRoutineInitialValue( Main *mainPtr )
{
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

  COMMENTlong("Scheme start");
  return;
}

void PM_feelfem90::DoMainRoutineSchemeFinish( Main *mainPtr)
{
  //writeSource("//********************************************************");
  //writeSource("//*** This is temporary func for DoMainRoutineSchemeFinish");
  //writeSource("//********************************************************");

  com();

  return;
}


void PM_feelfem90::DoMainRoutineTerminationSequence( Main *mainPtr)
{
  comment();
  writeSource("!call reportallmem(0)");
  writeSource("!call reportfini");
  com();

  writeSource("end program feelfem");
  return;
}
