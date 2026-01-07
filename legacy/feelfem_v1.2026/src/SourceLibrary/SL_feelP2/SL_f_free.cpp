/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_f_free.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelP2.hpp"

static int come_yet_f_free = 0;


void SL_feelP2::SL_f_free(int makeFlag)
{
  char *sourceName;

  if(come_yet_f_free == 1)  return;
  else                  come_yet_f_free = 1;

  sourceName = GetSourceName("f_free");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine f_free(cha , n , itype)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine f_free");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose: free allocated memory");
  writeSource("*-------------------------------------------------------------------");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      parameter (MAX_FEEL = 10000000)");
  writeSource("      parameter (MAX_DOMAIN = 10)");
  writeSource("      parameter (MAX_EDATSET = 38)");
  writeSource("      parameter (MAX_NODESET = 20)");
  writeSource("      parameter (MAX_NUMSET = 10)");
  writeSource("      parameter (MAX_EWISE  = 20)");
  writeSource("      parameter (MAX_IP    = 5)");
  writeSource("      parameter (MAX_SOLVE = 1)");
  writeSource("c --------------------------------------------------------------------");
  com();
  writeSource("c --------------------------------------------------------------------");
  writeSource("      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip");
  writeSource("      common /feel_ctl/mode_ex,mode_output,max_heap");
  writeSource("      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,");
  writeSource("     &                 np_fem,np_ewise,np_heap");
  writeSource("      common /feel_fil/io_in,io_tmp,io_out,io_stderr,");
  writeSource("     &                 io_edat,io_node,io_num,io_fem");
  writeSource("      common /feel_dat/n_edat(MAX_EDATSET,3),");
  writeSource("     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),");
  writeSource("     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)");
  writeSource("      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)");
  writeSource("c --------------------------------------------------------------------");
  com();
  writeSource("      write(*,*) 'changement 2001/01/27 f_alloc modify'");
  writeSource("      write(*,*) 'f_free is not used, I suppose.'");
  writeSource("      stop 'f_free'");
  com();
  writeSource("      nn = 0");
  writeSource("      if(itype.eq. 0) then");
  writeSource("	nn = n");
  writeSource("      endif");
  writeSource("      if(itype .eq. 1) then");
  writeSource("	nn = n * 2");
  writeSource("      endif");
  writeSource("      if(nn.eq.0) then");
  writeSource("	write(io_stderr,*) 'f_free: itype error'");
  writeSource("	stop 'f_free'");
  writeSource("      endif");
  com();
  writeSource("      np_work = np_work - nn");
  writeSource("      if(np_work .lt. 1) then");
  writeSource("	write(io_stderr,*) 'f_free <1 error for ',cha");
  writeSource("	stop 'f_free'");
  writeSource("      endif");
  writeSource("      return");
  writeSource("      end");
  com();

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
