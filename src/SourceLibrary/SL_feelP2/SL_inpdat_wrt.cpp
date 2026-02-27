/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_inpdat_wrt.cpp
 *  Date     : 2002/04/19 01:54
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
#include "SL_feelP2.hpp"

static int come_yet_inpdat_wrt = 0;


void SL_feelP2::SL_inpdat_wrt(int makeFlag)
{
  const char *sourceName;

  if(come_yet_inpdat_wrt == 1)  return;
  else                  come_yet_inpdat_wrt = 1;

  sourceName = GetSourceName("inpdat_wrt");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine inpdat_wrt");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  FEEL P2 System Subroutine");
  writeSource("*-------------------------------------------------------------------");
  writeSource("*  Purpose: show input data");
  com();
  writeSource("*  Caution:");
  com();
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
  writeSource("      write(*,*) 'READ feel_dat FILE'");
  com();
  writeSource("*      write(*,*) 'ndim  = ',ndim");
  writeSource("*      write(*,*) 'npmax = ',npmax");
  writeSource("*      write(*,*) 'nedat = ',nedat");
  writeSource("*      write(*,*) 'nnodeset =',nnodeset");
  writeSource("*      write(*,*) 'nnumdat = ',nnumdat");
  writeSource("*      write(*,*) 'io_edat = ',io_edat");
  writeSource("*      write(*,*) 'np_work=',np_work_get_falloc()");
  com();
  writeSource("      return");
  writeSource("      end");
  com();

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
