/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_dat_ip.cpp
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

static int come_yet_dat_ip = 0;


void SL_feelP2::SL_dat_ip(int makeFlag)
{
  const char *sourceName;

  if(come_yet_dat_ip == 1)  return;
  else                  come_yet_dat_ip = 1;

  sourceName = GetSourceName("dat_ip");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine dat_ip");
  writeSource("c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  writeSource("c     feel p2 fort77 program");
  writeSource("c     Copyright(C) NEC Corporation 1993");
  writeSource("c ======================================");
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
  writeSource("c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  writeSource(" 8001 read(io_in,9001,end=8900) (n_nodeno(i),i=1,nip)");
  writeSource(" 9001 format((8i8))");
  writeSource("      return");
  writeSource("c --------------------------------------------------------------------");
  writeSource(" 8900 write(io_stderr,*) 'IP DATA ERROR'");
  writeSource("      stop 'inp_ip'");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
