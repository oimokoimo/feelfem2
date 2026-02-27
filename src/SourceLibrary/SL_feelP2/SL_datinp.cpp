/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_datinp.cpp
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

static int come_yet_datinp = 0;


void SL_feelP2::SL_datinp(int makeFlag)
{
  const char *sourceName;

  if(come_yet_datinp == 1)  return;
  else                  come_yet_datinp = 1;

  sourceName = GetSourceName("datinp");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine datinp(feel)");
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
  writeSource("      real*4 feel(*)");
  writeSource("      character*4 word");
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
  writeSource("      read(io_in,9000) word");
  writeSource(" 9000 format(a4)");
  writeSource("      if(word .ne. 'FEEL') then");
  writeSource("        write(io_stderr,*) 'FEEL DATA ERROR'");
  writeSource("        stop 'NOT FEEL DATA FILE'");
  writeSource("      endif");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      read(io_in,9001) ndim,npmax,nedat,nodeset,numset,nip");
  writeSource(" 9001 format(6i8)");
  com();
  writeSource("      read(io_in,9002) mode_ex,mode_output");
  writeSource(" 9002 format(2i8)");
  com();
  writeSource("      read(io_in,9003) nvars_fem,nvars_ewise");
  writeSource(" 9003 format(2i8)");
  writeSource("      if(ndim .ne. 1 .and. ndim .ne. 2 .and. ndim .ne.3 ) then");
  writeSource("        stop 'ndim error'");
  writeSource("      endif");
  com();
  writeSource("      if(nedat .gt. MAX_EDATSET) then");
  writeSource("       stop 'nedat error'");
  writeSource("      endif");
  com();
  writeSource("      if(nodeset .gt. MAX_NODESET) then");
  writeSource("        stop 'nodeset error'");
  writeSource("      endif");
  com();
  writeSource("      if(numset .gt. MAX_NUMSET) then");
  writeSource("        stop 'numset error'");
  writeSource("      endif");
  com();
  writeSource("      do 100 i = 1,nedat");
  writeSource("        n_edat(i,1) = 0");
  writeSource(" 100  continue");
  com();
  writeSource("      do 101 i = 1,nodeset");
  writeSource("        n_nset(i,1) = 0");
  writeSource("        n_nset(i,2) = 0");
  writeSource(" 101  continue");
  com();
  writeSource("      do 102 i = 1,numset");
  writeSource("        n_num(i) = 0");
  writeSource(" 102  continue");
  com();
  writeSource("      if(nvars_ewise.eq.0) goto 200");
  writeSource("      do 150 i=1,nvars_ewise");
  writeSource("        read(io_in,9005) n_ewise(i,1),n_ewise(i,2)");
  writeSource(" 9005   format(2i8)");
  writeSource("  150 continue");
  writeSource("  200 continue");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      call f_alloc(np_x,'x coordinate',npmax,1,0)");
  writeSource("      if(ndim .gt. 1) then");
  writeSource("        call f_alloc(np_y,'y coordinate',npmax,1,0)");
  writeSource("      endif");
  writeSource("      if(ndim .gt. 2) then");
  writeSource("        call f_alloc(np_z,'z coordinate',npmax,1,0)");
  writeSource("      endif");
  writeSource("c --------------------------------------------------------------------");
  writeSource(" 8001 continue");
  com();
  writeSource("      read(io_in,9010,end=8900) word");
  writeSource(" 9010 format(a4)");
  com();
  writeSource("      if(word .eq. 'END ') goto 8010");
  writeSource("      if(word .eq. 'NODE') then");
  com();
  writeSource("        if(ndim .eq. 1) call dat_node1(feel(np_x))");
  com();
  writeSource("        if(ndim .eq. 2) call dat_node2(feel(np_x),feel(np_y))");
  com();
  writeSource("        if(ndim .eq. 3) call dat_node3(feel(np_x),feel(np_y),");
  writeSource("     &                                 feel(np_z))");
  com();
  writeSource("      endif");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      if(word .eq. 'EDAT') then");
  writeSource("        read(io_in,'(3i8)') no,nelem,np");
  com();
  writeSource("        call f_alloc_push");
  writeSource("        call f_alloc(np_ielem,'EDAT READ(ielem)',nelem*np,0,0)");
  writeSource("        call f_alloc(np_matno,'EDAT READ(matno)',nelem   ,0,0)");
  writeSource("        n_edat(no,1) = nelem");
  writeSource("        n_edat(no,2) = np");
  writeSource("        call dat_edat(no,nelem,np,feel(np_ielem),feel(np_matno))");
  writeSource("        call f_alloc_pop");
  writeSource("      endif");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      if(word .eq. 'NSET') then");
  writeSource("        read(io_in,'(3i8)') no,nodes,np");
  com();
  writeSource("        if(no .lt. 1 .or. no .gt.nodeset) then");
  writeSource("          write(*,*) 'nodeset no = ',no");
  writeSource("          stop 'nodeset error'");
  writeSource("        endif");
  com();
  writeSource("        n_nset(no,1) = nodes");
  writeSource("        n_nset(no,2) = np");
  writeSource("        call f_alloc_push");
  writeSource("        call f_alloc(np_inset,'NSET READ(inset)',nodes*np,0,0)");
  writeSource("        call dat_nodeset(no,nodes,np,feel(np_inset))");
  writeSource("        call f_alloc_pop");
  writeSource("      endif");
  writeSource("c --------------------------------------------------------------------");
  writeSource("c      if(word .eq. 'NUM ') call dat_num");
  writeSource("      if(word .eq. 'NUM ') stop 'future function NUM'");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      if(word .eq. 'IP  ') call dat_ip");
  writeSource("c --------------------------------------------------------------------");
  writeSource("c --------------------------------------------------------------------");
  writeSource("       goto 8001");
  writeSource("c --------------------------------------------------------------------");
  writeSource(" 8900 continue");
  writeSource("      write(io_stderr,9901)");
  writeSource(" 9901 format(' no end key word')");
  writeSource("c --------------------------------------------------------------------");
  writeSource(" 8010 continue");
  writeSource("      if(mode_output .eq. 0) call inpdat_wrt");
  writeSource("      if(mode_output .eq. 1) call inpdat_wrt");
  com();
  writeSource("      return");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
