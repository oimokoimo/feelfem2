/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_dat_nodeset.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelP2.hpp"

static int come_yet_dat_nodeset = 0;


void SL_feelP2::SL_dat_nodeset(int makeFlag)
{
  char *sourceName;

  if(come_yet_dat_nodeset == 1)  return;
  else                  come_yet_dat_nodeset = 1;

  sourceName = GetSourceName("dat_nodeset");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine dat_nodeset(no,nodes,np,inset)");
  writeSource("c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  writeSource("c     feel p2 fort77 program");
  writeSource("c     Copyright(C) NEC Corporation 1993");
  writeSource("c ======================================");
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
  writeSource("      dimension inset(np,nodes)");
  writeSource("      character fmt*10");
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
  com();
  writeSource("c----------------------------");
  writeSource("c  no     nodeset number");
  writeSource("c  nodes  number of nodes");
  writeSource("c  np     data par each node");
  writeSource("c----------------------------");
  writeSource("      if(no .gt. MAX_NODESET .or. no .lt. 1) then");
  writeSource("        write(io_stderr,*) 'node set No. ERROR ',no");
  writeSource("        stop 'nodeset read routine'");
  writeSource("      endif");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      write(fmt,90) np");
  writeSource("  90  format('(',I2,'I8)')");
  com();
  writeSource("      do 100 i=1,nodes");
  writeSource("        read(io_in,fmt) (inset(j,i),j=1,np)");
  writeSource(" 100  continue");
  com();
  writeSource("      iunit = io_node + no - 1");
  writeSource("      open(unit=iunit,status='scratch',form='unformatted')");
  writeSource("      call closefil(iunit)");
  com();
  writeSource("      write(iunit) nodes,np");
  writeSource("      write(iunit) ((inset(j,i),j=1,np),i=1,nodes)");
  com();
  writeSource("      return");
  writeSource("c --------------------------------------------------------------------");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
