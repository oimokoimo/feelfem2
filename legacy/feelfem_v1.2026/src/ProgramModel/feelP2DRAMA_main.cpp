/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelP2DRAMA_main.cpp
 *  Date     : 2000/04/03
 *  Modified : 2000/04/03
 *  
 *  Purpose  : temporary file for generating main routine
 *  
 */
#include "PM_feelP2DRAMA.hpp"


char* PM_feelP2DRAMA::GetMainSourceName(void)
{
  return(FNAME_FEELP2DRAMA_MAIN);
}


void PM_feelP2DRAMA::DoMainRoutineHeaderPM( Main *mainPtr)
{
  DoMainRoutineArgumentSequencePM( mainPtr );
  SourceStarters();

}

void PM_feelP2DRAMA::DoMainRoutineArgumentSequencePM( Main *mainPtr)
{
  writeSource("      program feelfem");
  
  //  SourceStarters();

  return;
}

void PM_feelP2DRAMA::DoMainRoutineParameters( Main *mainPtr)
{
  writeSource("      include'mpif.h'");
  comment();

  pushSource("      parameter (MAX_FEEL = ");
  pushSource(FEEL_MAX_P2);
  pushSource(")");
  flushSource();

  pushSource("      parameter (MAX_PROC = ");
  pushSource(FEEL_MAX_PROCS);
  pushSource(")");
  flushSource();
  comment();

  return;
}

void PM_feelP2DRAMA::DoMainRoutineVariableDefinitions( Main *mainPtr)
{
  writeSource("      real*4     feel(MAX_FEEL)");
  writeSource("      real*8    dfeel");
  writeSource("      integer*4  myrank,nprocs");
  writeSource("      integer*4  ndim");
  writeSource("      integer*4  npmax_g,nelem_g,nedat_g,nnset_g,nnum_g,nip_g");
  com();
  writeSource("      equivalence (feel,dfeel)");
  comment();

  return;
}

void PM_feelP2DRAMA::DoMainRoutineInitializer( Main *mainPtr)
  //
  //  This Routine contains the data distribution
  //
  //
  //
{
  writeSource("      call f_alloc_init(MAX_FEEL)");
  com();
  
  F77_MPI_Initialize();
  comment();

  return;
}
  
void PM_feelP2DRAMA::DoMainRoutineReportInitializer( Main *mainPtr)
{
  writeSource("      if(myrank.eq.0) call preportinit(1)");
  com();
  return;
}

void PM_feelP2DRAMA::DoMainRoutineDataInput( Main *mainPtr)
{
  writeSource("*----------------");
  writeSource("* MESH DATA READ ");
  writeSource("*----------------");
  writeSource("      if(myrank.eq.0) then");
  writeSource("       call preport('INITIALIZATION')");
  com();

  writeSource("*---");
  writeSource("       call datinp(feel,");
  writeSource("     $      ndim,npmax_g,nelem_g,nedat_g,nnset_g,nnum_g,nip_g,");
  writeSource("     $      np_x_g,np_y_g,np_z_g,np_ip_g,");
  writeSource("     $      nvars_fem,nvars_ewise,netype,20000412)");
  com();
  writeSource("       call preportmodule('DATINP ')");
  com();

  /* read solv_dat */
  writeSource("*---");
  writeSource("       call read_solv(feel,medatno,nredat,nbedat,nsolvs,");
  writeSource("     $                np_redatlst,np_bedatlst          )");
  com();
  writeSource("       call preportmodule('READ solv_dat')");
  com();

  /* read metis data */
  writeSource("*---");
  writeSource("       call f_alloc(np_metis,'element group array',nelem_g,0,0)");
  com();
  writeSource("       call f_alloc_push");
  writeSource("       call f_alloc(np_tmp,'tmp array',nelem_g,0,0)");
  writeSource("       call read_metis(feel(np_metis),feel(np_tmp),nelem_g,ndiv)");
  writeSource("       call f_alloc_pop");
  com();

  writeSource("       call preportmodule('READ_METIS')");
  com();

  
  //////////////////////////
  //  MESH DATA STORE     //
  //////////////////////////
  writeSource("*---");
  writeSource("       call f_alloc(np_redatctr,'redatctr',nredat*5,0,0)");
  writeSource("       call get_edat_lst(feel,nredat,feel(np_redatlst),");
  writeSource("     $                               feel(np_redatctr) )");
  com();

  writeSource("*---");
  writeSource("       if(nbedat .ne. 0) then");
  writeSource("         call f_alloc(np_inbctr,'inbctr',nbedat*5,0,0)");
  writeSource("         call get_edat_lst(feel,nbedat,feel(np_bedatlst),");
  writeSource("     $                     feel(np_inbctr)               )");
  writeSource("       else");
  writeSource("         np_inbctr = 1");
  writeSource("       endif");
  com();

  writeSource("*---");
  writeSource("       nbnset = nnset_g");
  writeSource("       if(nbnset .NE. 0) then");
  writeSource("        call f_alloc(np_idbctr,'idbctr',nbnset*4,0,0)");
  writeSource("        call get_bnset(feel,nbnset,feel(np_idbctr))");
  writeSource("       else");
  writeSource("        np_idbctr = 1");
  writeSource("       endif");
  com();

  //////////////////////////////
  //  DATA DISTRIBUTION CODE  //
  //////////////////////////////
  writeSource("*---");
  writeSource("       nwords = np_work_get_falloc()");
  com();

  writeSource("      endif");

  writeSource("*--------------------------------------");
  writeSource("* Fundamental data syncronization");
  writeSource("*--------------------------------------");
  com();
  writeSource("      call pgetparam30(myrank,nprocs,");
  writeSource("     $ 27,");
  writeSource("     $ ndim       ,npmax_g    ,nelem_g ,nedat_g,nnset_g ,nnum_g   ,");
  writeSource("     $ nip_g      ,np_x_g     ,np_y_g  ,np_z_g ,np_ip_g ,nvars_fem,");
  writeSource("     $ nvars_ewise,netype     ,medatno ,nredat ,nbedat  ,nsolvs   ,");
  writeSource("     $ np_redatlst,np_bedatlst,np_metis,ndiv,np_redatctr,np_inbctr,");
  writeSource("     $ nbnset     ,np_idbctr  ,nwords  ,idum1  ,idum2   ,idum3     )");

  com();
  writeSource("      if(ndiv .NE. nprocs) then");
  writeSource("        call abortexit(myrank,'NPROC .NE. METIS division')");
  writeSource("      endif");
  com();

  writeSource("*----------------------");
  writeSource("* Syncronize the memory");
  writeSource("*----------------------");
  writeSource("      call feelbcast(myrank,nprocs,feel,1,nwords-1)");
  writeSource("      if(myrank.ne.0) then");
  writeSource("       call np_work_set_falloc(nwords)");
  writeSource("      endif");
  com();
  writeSource("      if(myrank.eq.0) call preportmodule('INITIAL DISTRIBUTE')");
  com();

  writeSource("*---------------------------------------------------");
  writeSource("*  MAKE DRAMA double index data in every PE");
  writeSource("*  STEP 1: LONUMERATE   Local node number generation");
  writeSource("*          mynode,myelem,loc(2,*) array calculated");
  writeSource("*---------------------------------------------------");  
  writeSource("      call f_alloc(np_loc,'local indices',npmax_g*2,0,0)");
  writeSource("      call lonumerate_lst(feel,myrank   ,nprocs ,");
  writeSource("     $                    feel(np_loc)  ,npmax_g,");
  writeSource("     $                    feel(np_metis),nelem_g,");
  writeSource("     $                    nredat,feel(np_redatctr),");
  writeSource("     $                    mynode,myelem            )");
  com();
  writeSource("      if(myrank.eq.0) call preportmodule('LONUMERATE_LST')");
  com();
  
  /* Make local node array */
  writeSource("*-------------------------------------------------------");
  writeSource("*  MAKE DRAMA double index data in every PE");
  writeSource("*  STEP 2: MKLOCCOOR    Make local node coordinate array");
  writeSource("*          xloc(*),yloc(*) Generated");
  writeSource("*-------------------------------------------------------");  
  writeSource("      call f_alloc(np_xloc,    'local x coordinate',mynode,1,0)");
  writeSource("      call f_alloc(np_yloc,    'local y coordinate',mynode,1,0)");
  writeSource("      call mkloccoor(myrank,nprocs,");
  writeSource("     $               feel(np_x_g),feel(np_y_g),feel(np_loc),npmax_g,");
  writeSource("     $               feel(np_xloc),feel(np_yloc)       ,mynode  )");
  com();
  writeSource("      if(myrank.eq.0) call preportmodule('MKLOCCOOR')");
  com();


  writeSource("*-------------------------------------------------------");
  writeSource("*  MAKE DRAMA double index data in every PE");
  writeSource("*  STEP 3: Make REGIONAL LOCAL EDAT SET(ENPTR,CON)");
  writeSource("*          myelem is fixed");
  writeSource("*          enptrlst(*),matnolst(*),conlst(*) generated");
  writeSource("*-------------------------------------------------------");  

  writeSource("      call f_alloc(np_redatinfo,'(redatinfo)',nredat*3,0,0)");
  writeSource("      call f_alloc(np_enptrlst,'(Enptr lst)',nredat,0,0)");
  writeSource("      call f_alloc(np_matnolst,'(Matno lst)',nredat,0,0)");
  writeSource("      call f_alloc(np_conlst,  '(Con   lst)',nredat,0,0)");
  com();
  writeSource("      call mklocredats(feel,myrank,nprocs,");
  writeSource("     $                 feel(np_loc),npmax_g,");
  writeSource("     $                 feel(np_metis),nelem_g,");
  writeSource("     $                 myelem,");
  writeSource("     $                 nredat,feel(np_redatctr),");
  writeSource("     $                 feel(np_redatinfo),");
  writeSource("     $                 feel(np_enptrlst),feel(np_matnolst),");
  writeSource("     $                 feel(np_conlst))");
  com();
  writeSource("      if(myrank.eq.0) call preportmodule('MKLOCREDATS')");
  com();

  writeSource("*-------------------------------------------------------");
  writeSource("*  MAKE DRAMA double index data in every PE");
  writeSource("*  STEP 4: Make BOUNDARY EDAT SET(ENPTR,CON)");
  writeSource("*          This is GLOBALLY gather/scattered data");
  writeSource("*          inbctr2(5,*) Generated");
  writeSource("*-------------------------------------------------------");
  writeSource("      if(nbedat .NE. 0) then");
  com();
  writeSource("       call f_alloc(np_inbctr2,'inbctr2',nbedat*5,0,0)");
  writeSource("       call mkglobalbedats(feel,myrank,nprocs,");
  writeSource("     $                     feel(np_loc),npmax_g,");
  writeSource("     $             nbedat, feel(np_inbctr),feel(np_inbctr2))");
  com();
  writeSource("      else");
  writeSource("       np_inbctr2 = 1");
  writeSource("      endif");
  com();
  writeSource("      if(myrank.eq.0) call preportmodule('MKGLOBALBEDATS')");
  com();

  writeSource("*-------------------------------------------------------");
  writeSource("*  MAKE DRAMA double index data in every PE");
  writeSource("*  STEP 5: Make BOUNDARY NSET SET");
  writeSource("*          This is GLOBALLY gather/scattered data");
  writeSource("*          idbctr2(5,*) generated");
  writeSource("*-------------------------------------------------------");
  writeSource("      if(nbnset .NE. 0) then");
  writeSource("        call f_alloc(np_idbctr2,'idbctr2',nbnset*5,0,0)");
  writeSource("        call mkglobalbnsets(feel,myrank,nprocs,");
  writeSource("     $                      feel(np_loc),npmax_g,");
  writeSource("     $              nbnset, feel(np_idbctr),feel(np_idbctr2))");
  com();
  writeSource("      else");
  writeSource("        np_idbctr2 = 1");
  writeSource("      endif");
  com();
  writeSource("      if(myrank.eq.0) call preportmodule('MKGLOBALBNSETS')");
  com();

  writeSource("*-------------------------------------------------------");
  writeSource("*  MAKE DRAMA double index data in every PE");
  writeSource("*  STEP 6: Memory Move");
  writeSource("*-------------------------------------------------------");
  writeSource("      call pmeminitloc(feel,myrank,nprocs,");
  writeSource("     $ mynode,np_xloc,np_yloc,feel(np_xloc),feel(np_yloc),");
  writeSource("     $ nredat,myelem,");
  writeSource("     $ np_redatinfo,np_enptrlst,np_matnolst,np_conlst,");
  writeSource("     $ feel(np_redatinfo),");
  writeSource("     $ feel(np_enptrlst),feel(np_matnolst),feel(np_conlst),");
  writeSource("     $ nbedat,np_inbctr2,feel(np_inbctr2),");
  writeSource("     $ nbnset,np_idbctr2,feel(np_idbctr2) )");
  com();
  writeSource("      if(myrank.eq.0) call preportmodule('PMEMINITLOC')");

  return;
}


void PM_feelP2DRAMA::DoMainRoutineSchemeStart( Main *mainPtr)
{
  writeSource("*******************************************************");
  writeSource("*** This is temporary func for DoMainRoutineSchemeStart");
  writeSource("*******************************************************");

  return;
}


void PM_feelP2DRAMA::DoMainRoutineInitialValue( Main *mainPtr)
{
  writeSource("********************************************************");
  writeSource("*** This is temporary func for DoMainRoutineInitialValue");
  writeSource("********************************************************");

  return;
}

void PM_feelP2DRAMA::DoMainRoutineSchemeFinish( Main *mainPtr)
{
  writeSource("********************************************************");
  writeSource("*** This is temporary func for DoMainRoutineSchemeFinish");
  writeSource("********************************************************");

  return;
}


void PM_feelP2DRAMA::DoMainRoutineTerminationSequence( Main *mainPtr)
{
  comment();
  writeSource("      call preportallmem(myrank,nprocs)");
  writeSource("      if(myrank.eq.0) call preportfini");
  com();

  writeSource("      call mpi_finalize(ierr)");
  com();
  
  writeSource("      end");


  return;
}
