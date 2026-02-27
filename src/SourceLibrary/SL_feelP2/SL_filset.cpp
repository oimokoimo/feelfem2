/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_filset.cpp
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

static int come_yet_filset = 0;


void SL_feelP2::SL_filset(int makeFlag)
{
  const char *sourceName;

  if(come_yet_filset == 1)  return;
  else                  come_yet_filset = 1;

  sourceName = GetSourceName("filset");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine filset");
  writeSource("c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  writeSource("c     feel p2 fort77 program");
  writeSource("c     Copyright(C) NEC Corporation 1993");
  writeSource("c ======================================");
  writeSource("c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  writeSource("c Date: Tue Jan 30 16:56:32 CET 2001");
  writeSource("c User: Hidehiro FUJIO");
  writeSource("c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  writeSource("      implicit real*8 (a-h,o-z)");
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
  writeSource("      io_in     = 10");
  writeSource("      io_out    = 12");
  writeSource("      io_stderr =  7");
  writeSource("      open(unit=io_stderr,file='/dev/tty',status='UNKNOWN')");
  writeSource("      call closefil(io_stderr)");
  com();
  writeSource("      open(unit=io_in,status='old',file='feel_dat')");
  writeSource("      call closefil(io_in)");
  writeSource("      open(unit=io_out,file='feel_out',status='UNKNOWN')");
  writeSource("      call closefil(io_out)");
  com();
  writeSource("      io_edat = io_out  + 1");
  writeSource("      io_node = io_edat + MAX_EDATSET");
  writeSource("      io_num  = io_node + MAX_NODESET");
  writeSource("      io_fem  = io_num  + MAX_NUMSET*0 +1");
  writeSource("      io_tmp  = io_fem  + MAX_SOLVE *0 +1");
  com();
  writeSource("      call rep_head");
  writeSource("c---------------------------------------");
  writeSource("      return");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
