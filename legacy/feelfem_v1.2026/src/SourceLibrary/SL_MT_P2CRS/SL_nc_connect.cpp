/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_nc_connect.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
 *
 */
#include "SL_MT_P2CRS.hpp"

static int come_yet_nc_connect = 0;


void SL_MT_P2CRS::SL_nc_connect(int makeFlag)
{
  char *sourceName;

  if(come_yet_nc_connect == 1)  return;
  else                  come_yet_nc_connect = 1;

  sourceName = GetSourceName("nc_connect");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("      subroutine NC_connect(nc,ipf,npmax,ielem,nelem,np,ncmax,ndf)");
  writeSource("*------------------------------------------------------------------");
  writeSource("*     Calculate the maximum number of connecting elements");
  writeSource("*     This routines used for CRS type matrix topology");
  com();
  writeSource("*     ndf is also calculated in this");
  com();
  com();
  writeSource("*     nc(*)    : work array");
  writeSource("*     ipf(*)   : freedom array for each node");
  writeSource("*     npmax    : number of nodes");
  writeSource("*     ielem(np,nelem)  : element-node array  nelem,np elements,node per E resp.");
  com();
  com();
  writeSource("*     OUTPUT");
  com();
  writeSource("*     ncmax  : number of maximum connecting elements");
  writeSource("*     ndf    : number of degree of freedom in one element");
  writeSource("*------------------------------------------------------------------");
  writeSource("      dimension nc(npmax)");
  writeSource("      dimension ipf(npmax)");
  writeSource("      dimension ielem(np,nelem)");
  com();
  writeSource("      do 100 i=1,npmax");
  writeSource("      nc(i)=0");
  writeSource("100   continue");
  com();
  writeSource("      do 200 i=1,nelem");
  writeSource("      do 210 j=1,np");
  writeSource("      nc(ielem(j,i))=nc(ielem(j,i))+1");
  writeSource("210   continue");
  writeSource("200   continue");
  com();
  writeSource("      ncmax = nc(1)");
  writeSource("      nptr  =    1");
  writeSource("      do 300 i=2,npmax");
  writeSource("      if(ncmax .LT. nc(i)) then");
  writeSource("        ncmax = nc(i)");
  writeSource("	nptr  = i");
  writeSource("      endif");
  writeSource("300   continue");
  com();
  writeSource("      ndf = 0");
  writeSource("      do 400 i=1,np");
  writeSource("      ndf = ndf + ipf(ielem(i,1))");
  writeSource("400   continue");
  com();
  writeSource("      return");
  writeSource("      end");
  com();
  com();

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
