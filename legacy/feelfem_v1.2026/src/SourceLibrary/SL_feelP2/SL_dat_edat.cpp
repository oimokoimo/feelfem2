/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_dat_edat.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelP2.hpp"

static int come_yet_dat_edat = 0;


void SL_feelP2::SL_dat_edat(int makeFlag)
{
  char *sourceName;

  if(come_yet_dat_edat == 1)  return;
  else                  come_yet_dat_edat = 1;

  sourceName = GetSourceName("dat_edat");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine dat_edat(no,nelem,np,ielem,matno)");
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
  writeSource("      dimension ielem(np,nelem),matno(nelem)");
  writeSource("      character*20 fmt");
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
  writeSource("      iunit = io_edat + no - 1");
  writeSource("      open(unit=iunit,status='scratch',form='unformatted')");
  writeSource("      call closefil(iunit)");
  com();
  writeSource("      write(fmt,9003) np+1");
  writeSource(" 9003 format('(',I2,'I8)')");
  com();
  writeSource("      do 100 i=1,nelem");
  writeSource("        read(io_in,fmt,end=8902) (ielem(j,i),j=1,np),matno(i)");
  writeSource("  100 continue");
  com();
  writeSource("      write(iunit) nelem,np");
  writeSource("      write(iunit) ((ielem(i,j),i=1,np),j=1,nelem)");
  writeSource("      write(iunit) (matno(i),i=1,nelem)");
  com();
  writeSource("      return");
  writeSource("*----------------------------------------------------------------------");
  writeSource(" 8902 write(io_stderr,*) 'edat data error'");
  writeSource("      stop 'inp_edat'");
  writeSource("*----------------------------------------------------------------------");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
