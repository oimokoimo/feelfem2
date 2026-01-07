/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_dat_num.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelP2.hpp"

static int come_yet_dat_num = 0;


void SL_feelP2::SL_dat_num(int makeFlag)
{
  char *sourceName;

  if(come_yet_dat_num == 1)  return;
  else                  come_yet_dat_num = 1;

  sourceName = GetSourceName("dat_num");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine dat_num(dat)");
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
  writeSource("      dimension dat(*)");
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
  writeSource("      read(io_in,9001) no,nsetno");
  com();
  writeSource("c  no     Nodeset number");
  writeSource("c  nsetno Number of nodes");
  com();
  writeSource(" 9001 format(2i8)");
  com();
  writeSource("      if(no .gt. MAX_NODESET .or. no .le. 0) goto 8901");
  writeSource("      ns = n_nset(no,1)");
  writeSource("      if(ns .eq. 0) goto 8902");
  com();
  writeSource("      if(ns*2 + np_work_get_falloc() .gt. np_heap) goto 8900");
  com();
  writeSource("      n_num(no) = nsetno");
  com();
  writeSource("      iunit = io_num + no - 1");
  writeSource("      open(unit=iunit,status='scratch',form='unformatted')");
  writeSource("      call closefil(iunit)");
  com();
  writeSource("      read(io_in,9010,end=8903) (dat(i),i=1,ns)");
  writeSource(" 9010 format((5e14.5))");
  com();
  writeSource("      write(iunit) ns,(dat(i),i=1,ns)");
  com();
  writeSource("      return");
  writeSource("c---------------------------------------------------------");
  writeSource(" 8900 write(io_stderr,*) 'no space left(inp_nset)'");
  writeSource("      write(io_stderr,*) ns*2+np_work_get_falloc()-np_heap");
  writeSource("      stop 'inp_nset'");
  writeSource("c----------------------");
  writeSource(" 8901 write(io_stderr,*) 'node set no error(数値データ入力時)'");
  writeSource("      stop 'inp_nset'");
  writeSource("c----------------------");
  writeSource(" 8902 write(io_stderr,*) '指定した節点集合データが定義されない'");
  writeSource("      stop 'inp_nset'");
  writeSource("c----------------------");
  writeSource(" 8903 write(io_stderr,*) 'node set data error'");
  writeSource("      stop 'inp_nset'");
  writeSource("c---------------------------------------------------------");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
