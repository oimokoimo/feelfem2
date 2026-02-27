/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_mkcrsindex.cpp
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
#include "SL_MT_P2CRS.hpp"

static int come_yet_mkcrsindex = 0;


void SL_MT_P2CRS::SL_mkcrsindex(int makeFlag)
{
  const char *sourceName;

  if(come_yet_mkcrsindex == 1)  return;
  else                  come_yet_mkcrsindex = 1;

  sourceName = GetSourceName("mkcrsindex");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine mkcrsindex(ic,ic2,ip,ncon,neq,ndf,");
  writeSource("     $                      ielem,nelem,np,");
  writeSource("     $                      ipf,ipd,npmax,ncof,maxnzpr)");
  writeSource("*-------------------------------------------------------------------");
  writeSource("* Make CRS index array");
  com();
  writeSource("* Input   ielem(np,nelem)  /element-node correspondance array");
  writeSource("*         ipf(npmax)        freedom per each node");
  writeSource("*         ipd(npmax)        count-up degree of freedom");
  com();
  writeSource("*         ndf               total degree of freedom in one element");
  writeSource("*                          (This is valid for only one element type)");
  writeSource("* -------");
  com();
  writeSource("* Work    IPT(*)");
  writeSource("*         IC(ncon=maximum connection, neq)");
  writeSource("* -------");
  writeSource("* Output  IC or IC2  INDROW  (row pointer  size=ncof)");
  writeSource("*         IP(neq+1)  IPTRCOL");
  com();
  writeSource("*         IC2(*)     Same address of ic:   used to make final ic");
  writeSource("*         ncof       Total nonzero number");
  writeSource("*         maxnzpr    Maximum number of nonzeros per row");
  writeSource("*-------------------------------------------------------------------");
  writeSource("      parameter (MAX = 100)");
  com();
  writeSource("      dimension ic(ncon,neq),ip(neq+1)");
  writeSource("      dimension ic2(*)");
  writeSource("      dimension ielem(np,nelem)");
  writeSource("      dimension ipf(npmax),ipd(npmax)");
  com();
  writeSource("      dimension ipt(MAX)");
  writeSource("*--------------------------------------------------------------");
  writeSource("      if(ndf .gt. MAX) stop 'element matrix arraysize too huge'");
  com();
  writeSource("      maxnzpr = 0");
  com();
  writeSource("      do 100 i=1,neq");
  writeSource("        ip(i)=0");
  writeSource("100   continue");
  writeSource("*--------------------------------------------------------------");
  writeSource("* Make IC array");
  writeSource("*--------------------------------------------------------------");
  writeSource("* i: element loop");
  writeSource("*----------------");
  writeSource("      do 200 i=1,nelem");
  writeSource("*--------------------------------------");
  writeSource("* make ipt(*) array for each element");
  writeSource("*      ipt(*) contains the equation no.");
  writeSource("*      iptr is its counter");
  writeSource("*--------------------------------------");
  writeSource("       iptr = 0");
  writeSource("*-------------------");
  writeSource("* j: node loop");
  writeSource("*-------------------");
  writeSource("       do 201 j=1,np");
  writeSource("*-------------------");
  writeSource("* nno = node number");
  writeSource("*-------------------");
  writeSource("       nno = ielem(j,i)");
  writeSource("*---------------------");
  writeSource("* k: node freedom loop");
  writeSource("*---------------------");
  writeSource("        do 202 k=1,ipf(nno)");
  writeSource("*	write(*,*) 'loop k=',k,' ipf(nno)= ',ipf(nno)");
  writeSource("	iptr = iptr+1");
  writeSource("	ipt(iptr)=ipd(nno)+k-1");
  writeSource("***     write(*,*) 'iptr=',iptr,'  ipt(iptr)=',ipt(iptr)");
  writeSource("202     continue");
  writeSource("201    continue");
  writeSource("*---------------------------------");
  writeSource("* finish to make ipt(*) array");
  writeSource("* then make ic(*,neq) array");
  writeSource("*---------------------------------");
  writeSource("       if(ndf .ne. iptr) stop 'mkcrsindex ndf,iptr mismatch'");
  writeSource("       do 210 j=1,ndf");
  com();
  writeSource("* for Row nj");
  com();
  writeSource("        nj = ipt(j)");
  com();
  writeSource("        do 215 k=1,ndf");
  com();
  writeSource("* store (nj,nk) index");
  com();
  writeSource("	 nk = ipt(k)");
  writeSource("	 do 216 l=1,ip(nj)");
  writeSource("	 if(ic(l,nj) .eq. nk) goto 215");
  writeSource("216      continue");
  writeSource("         ip(nj)=ip(nj)+1");
  writeSource("	 ic(ip(nj),nj) = nk");
  writeSource("215     continue");
  writeSource("210    continue");
  writeSource("*----------------");
  writeSource("* element loop");
  writeSource("*----------------");
  writeSource("200   continue");
  com();
  writeSource("*--------------------------");
  writeSource("* Make indrow array in IC2 *** NOT FOR VECTOR PROCESSING***");
  writeSource("*--------------------------");
  writeSource("      maxnzpr = ip(1)");
  writeSource("      irptr   = 1");
  com();
  writeSource("      do 300 i=2,neq");
  com();
  writeSource("       if(maxnzpr .LT. ip(i)) maxnzpr = ip(i)");
  com();
  writeSource("       irptrsv = irptr");
  writeSource("       irptr   = irptr+ip(i-1)");
  writeSource("       ip(i-1) = irptrsv");
  com();
  writeSource("       do 310 j=0,ip(i)-1");
  writeSource("         ic2(j+irptr)=ic(j+1,i)");
  writeSource("310    continue");
  com();
  writeSource("300   continue");
  com();
  writeSource("      irptrsv = irptr");
  writeSource("      irptr   = irptr + ip(neq)");
  writeSource("      ip(neq) = irptrsv");
  com();
  writeSource("      ncof = irptr-1");
  writeSource("*new");
  writeSource("      ip(neq+1) = ncof + 1");
  com();
  writeSource("      return");
  writeSource("      end");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
