/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_feelP2data.cpp
 *  Date     : 2002/09/12 17:25
 *  Purpose  : Library module generator
 *
 */
#include "SL_feelfem90.hpp"

static int come_yet_feelP2data = 0;


void SL_feelfem90::SL_feelP2data(int makeFlag)
{
  char *sourceName;

  if(come_yet_feelP2data == 1)  return;
  else                  come_yet_feelP2data = 1;

  sourceName = GetSourceName("feelP2data");
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSource("module feelP2data");
  com();
  writeSource("!------------------------------------------");
  writeSource("! handling scalar feelP2 data for feelfem90");
  com();
  writeSource("!------------------------------------------");
  writeSource("contains");
  com();
  writeSource("subroutine setP2edat(edatno,firstEdatPtr,nelem,np,netype,ielem,matno)");
  writeSource("use femDataType");
  writeSource("use numeric");
  writeSource("use abortmodule");
  com();
  writeSource("implicit none");
  com();
  writeSource("integer,intent(in)                    :: edatno");
  writeSource("type(edatList),pointer                :: firstEdatPtr");
  writeSource("integer                               :: nelem");
  writeSource("integer                               :: np");
  writeSource("integer                               :: netype");
  writeSource("integer,dimension(:,:),pointer        :: ielem");
  writeSource("integer,dimension(:),pointer          :: matno");
  com();
  writeSource("! auto variable");
  writeSource("type(edatList),pointer                :: edatPtr");
  writeSource("type(edat),pointer                    :: edatData");
  writeSource("!-------------------------------------------");
  writeSource("nullify(ielem,matno)");
  com();
  writeSource("edatPtr => firstEdatPtr");
  com();
  writeSource("search_loop: do");
  com();
  writeSource(" if(edatno == edatPtr\%no) then");
  com();
  writeSource("   edatData => edatPtr\%edatData");
  writeSource("   nelem    =  edatData\%nelem");
  writeSource("   np       =  edatData\%np");
  writeSource("   netype   =  edatData\%netype");
  com();
  writeSource("   ielem    => edatData\%ielem");
  writeSource("   matno    => edatData\%matno");
  com();
  writeSource("   exit search_loop");
  com();
  writeSource(" endif");
  com();
  writeSource(" if( .not. associated(edatPtr\%next)) exit search_loop");
  writeSource(" edatPtr => edatPtr\%next");
  com();
  writeSource("end do search_loop");
  com();
  writeSource("if( .not. associated(ielem)) then");
  writeSource("  write(*,*) 'edatno=',edatno, 'not found(feelP2data)'");
  writeSource("  call abortexit('setP2edat error')");
  writeSource("endif");
  com();
  writeSource("end subroutine setP2edat");
  com();
  com();
  writeSource("subroutine setP2nset(nsetno,firstNsetPtr,nodes,np,inset)");
  com();
  writeSource("use femDataType");
  writeSource("use numeric");
  writeSource("use abortmodule");
  com();
  writeSource("implicit none");
  com();
  writeSource("integer                          :: nsetno");
  writeSource("type(nsetList),pointer           :: firstNsetPtr");
  writeSource("integer                          :: nodes,np");
  writeSource("integer,dimension(:,:),pointer   :: inset");
  com();
  writeSource("! auto variable");
  writeSource("type(nsetList),pointer           :: nsetPtr");
  writeSource("type(nset),pointer               :: nsetData");
  com();
  writeSource("!---");
  com();
  writeSource("nullify(inset)");
  com();
  writeSource("nsetPtr => firstNsetPtr");
  com();
  writeSource("search_loop: do");
  com();
  writeSource(" if(nsetno .eq. nsetPtr\%no) then");
  writeSource("   nsetData => nsetPtr\%nsetData");
  writeSource("   nodes    =  nsetData\%nodes");
  writeSource("   np       =  nsetData\%np");
  writeSource("   inset    => nsetData\%inset");
  com();
  writeSource("   exit search_loop");
  writeSource(" endif");
  com();
  writeSource(" if( .not. associated(nsetPtr\%next)) exit search_loop");
  writeSource(" nsetPtr => nsetPtr\%next");
  com();
  writeSource("end do search_loop");
  com();
  writeSource("if( .not. associated(inset)) then");
  writeSource("  write(*,*) 'nsetno=',nsetno , ' not found(setP2nset)'");
  writeSource("  call abortexit('setP2nset error')");
  writeSource("endif");
  com();
  writeSource("end subroutine setP2nset");
  com();
  writeSource("integer function getipno( n ,ipData)");
  writeSource("use femDataType");
  writeSource("use abortmodule");
  writeSource("implicit none");
  com();
  writeSource("integer,intent(in)            :: n");
  writeSource("type(ipdat),pointer           :: ipData");
  com();
  writeSource("! auto");
  writeSource("integer,dimension(:),pointer  :: ipno");
  com();
  writeSource("ipno => ipData\%ipno");
  com();
  writeSource("if(n < 1  .or. n > ipData\%nodes) then");
  writeSource("  write(*,*) 'try to get ipdat no ',n");
  writeSource("  call abortexit('getipno error')");
  writeSource("endif");
  com();
  writeSource("getipno = ipno(n)");
  com();
  writeSource("return");
  writeSource("end function getipno");
  com();
  com();
  com();
  writeSource("end module feelP2data");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
